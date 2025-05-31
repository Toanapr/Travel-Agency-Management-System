#include "UserRepository.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

UserRepository::UserRepository(std::shared_ptr<DatabaseConnection> dbConnection)
    : _dbConnection(dbConnection)
{
}

std::vector<User> UserRepository::getAll()
{
    std::vector<User> users;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line
        std::getline(file, line);

        // Read all data lines
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                User user = parseUserFromCsv(line);
                if (user.getId() > 0)
                { // Only add valid users
                    users.push_back(user);
                }
            }
        }

        file.close();
    }

    return users;
}

std::optional<User> UserRepository::getById(int id)
{
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) == "id")
        {
            // It's a header, do nothing
        }
        else
        {
            // Check if the first line contains the user
            User user = parseUserFromCsv(line);
            if (user.getId() == id)
            {
                file.close();
                return user;
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            User user = parseUserFromCsv(line);
            if (user.getId() == id)
            {
                file.close();
                return user;
            }
        }

        file.close();
    }

    return std::nullopt;
}

std::vector<User> UserRepository::findByName(const std::string &name)
{
    std::vector<User> users;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) == "id")
        {
            // It's a header, do nothing
        }
        else
        {
            // Check if the first line contains the user with matching name
            User user = parseUserFromCsv(line);
            std::string userName = user.getName();
            std::transform(userName.begin(), userName.end(), userName.begin(), ::tolower);

            std::string searchName = name;
            std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

            if (userName.find(searchName) != std::string::npos)
            {
                users.push_back(user);
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            User user = parseUserFromCsv(line);
            std::string userName = user.getName();
            std::transform(userName.begin(), userName.end(), userName.begin(), ::tolower);

            std::string searchName = name;
            std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

            if (userName.find(searchName) != std::string::npos)
            {
                users.push_back(user);
            }
        }

        file.close();
    }

    return users;
}

bool UserRepository::add(const User &user)
{
    // Generate a new ID for the user (max ID + 1)
    int newId = getNextId();

    // Create a copy of the user with the new ID
    User newUser = user;
    newUser.setId(newId);

    // Open the file for appending
    std::ofstream file = _dbConnection->openFileForWriting(_filename, true);

    if (file.is_open())
    {
        // Only add the data (no header)
        file << convertUserToCsv(newUser) << std::endl;
        file.close();
        return true;
    }

    return false;
}

bool UserRepository::update(const User &user)
{
    std::vector<User> users = getAll();
    bool found = false;

    for (auto &existingUser : users)
    {
        if (existingUser.getId() == user.getId())
        {
            existingUser = user;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return false;
    }

    // Rewrite the entire file
    std::ofstream file = _dbConnection->openFileForWriting(_filename, false);

    if (file.is_open())
    {
        // Add header
        file << "id,name,address,phone,email" << std::endl;

        // Add all users
        for (const auto &u : users)
        {
            file << convertUserToCsv(u) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

bool UserRepository::remove(int id)
{
    std::vector<User> users = getAll();
    auto it = std::find_if(users.begin(), users.end(),
                           [id](const User &user)
                           { return user.getId() == id; });

    if (it == users.end())
    {
        return false;
    }

    users.erase(it);

    // Rewrite the entire file
    std::ofstream file = _dbConnection->openFileForWriting(_filename, false);

    if (file.is_open())
    {
        // Add header
        file << "id,name,address,phone,email" << std::endl;

        // Add all remaining users
        for (const auto &user : users)
        {
            file << convertUserToCsv(user) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

User UserRepository::parseUserFromCsv(const std::string &line)
{
    // Skip empty lines
    if (line.empty())
    {
        return User(0, "", "", "", "");
    }

    // Skip header line
    if (line.substr(0, 2) == "id")
    {
        return User(0, "", "", "", "");
    }

    std::stringstream ss(line);
    std::string idStr, name, address, phone, email;

    // Parse CSV format: id,name,address,phone,email
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, address, ',');
    std::getline(ss, phone, ',');
    std::getline(ss, email);

    try
    {
        int id = std::stoi(idStr);
        return User(id, name, address, phone, email);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing user ID from CSV: " << e.what() << " (line: " << line << ")" << std::endl;
        return User(0, "", "", "", "");
    }
}

std::string UserRepository::convertUserToCsv(const User &user)
{
    return std::to_string(user.getId()) + "," +
           user.getName() + "," +
           user.getAddress() + "," +
           user.getPhone() + "," +
           user.getEmail();
}

int UserRepository::getNextId()
{
    std::vector<User> users = getAll();

    if (users.empty())
    {
        return 1;
    }

    int maxId = 0;
    for (const auto &user : users)
    {
        if (user.getId() > maxId)
        {
            maxId = user.getId();
        }
    }

    return maxId + 1;
}