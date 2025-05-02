#include "UserService.h"

UserService::UserService(std::shared_ptr<IUserRepository> userRepository)
    : _userRepository(userRepository)
{
}

std::vector<User> UserService::getAllUsers()
{
    return _userRepository->getAll();
}

std::optional<User> UserService::getUserById(int id)
{
    return _userRepository->getById(id);
}

std::vector<User> UserService::findUsersByName(const std::string &name)
{
    return _userRepository->findByName(name);
}

bool UserService::addUser(const User &user)
{
    return _userRepository->add(user);
}

bool UserService::updateUser(const User &user)
{
    return _userRepository->update(user);
}

bool UserService::deleteUser(int id)
{
    return _userRepository->remove(id);
}

// In a real application, this would use password hashing and proper authentication
bool UserService::login(const std::string &email, const std::string &password)
{
    // Simplified implementation for demo purposes
    // In a real application, you would check against stored credentials
    auto users = _userRepository->getAll();

    for (const auto &user : users)
    {
        if (user.getEmail() == email)
        {
            // In a real app, we would verify the password here
            return true;
        }
    }

    return false;
}

void UserService::logout()
{
    // In a real application, this would clear session data
}