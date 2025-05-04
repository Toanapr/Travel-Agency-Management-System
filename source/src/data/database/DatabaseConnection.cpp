#include "DatabaseConnection.h"
#include <iostream>
#include <filesystem>

std::shared_ptr<DatabaseConnection> DatabaseConnection::_instance = nullptr;

DatabaseConnection::DatabaseConnection() : _dataPath("")
{
}

std::shared_ptr<DatabaseConnection> DatabaseConnection::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = std::shared_ptr<DatabaseConnection>(new DatabaseConnection());
    }
    return _instance;
}

bool DatabaseConnection::connect(const std::string &dataPath)
{
    _dataPath = dataPath;

    // Create data directory if it doesn't exist
    if (!std::filesystem::exists(_dataPath))
    {
        try
        {
            std::filesystem::create_directories(_dataPath);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error creating data directory: " << e.what() << std::endl;
            return false;
        }
    }

    return true;
}

void DatabaseConnection::disconnect()
{
    // Nothing to do for file-based storage
}

bool DatabaseConnection::isConnected() const
{
    return !_dataPath.empty() && std::filesystem::exists(_dataPath);
}

std::ifstream DatabaseConnection::openFileForReading(const std::string &filename)
{
    std::string fullPath = _dataPath + "/" + filename;
    std::ifstream file(fullPath);

    if (!file.is_open())
    {
        // If file doesn't exist, create an empty one
        if (!std::filesystem::exists(fullPath))
        {
            std::ofstream newFile(fullPath);
            newFile.close();
            file.open(fullPath);
        }
    }

    return file;
}

std::ofstream DatabaseConnection::openFileForWriting(const std::string &filename, bool append)
{
    std::string fullPath = _dataPath + "/" + filename;
    std::ofstream file;

    if (append)
    {
        file.open(fullPath, std::ios::app);
    }
    else
    {
        file.open(fullPath);
    }

    return file;
}