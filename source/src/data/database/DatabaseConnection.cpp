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

    std::cout << "Connected to data directory: " << _dataPath << std::endl;
    return true;
}

void DatabaseConnection::disconnect()
{
    // Nothing to do for file-based storage
    std::cout << "Database disconnected successfully." << std::endl;
}

bool DatabaseConnection::isConnected() const
{
    return !_dataPath.empty() && std::filesystem::exists(_dataPath);
}

std::ifstream DatabaseConnection::openFileForReading(const std::string &filename)
{
    // Remove "#file:source" prefix if present
    std::string cleanFilename = filename;
    std::string prefix = "#file:source";
    if (cleanFilename.substr(0, prefix.length()) == prefix)
    {
        cleanFilename = cleanFilename.substr(prefix.length());
    }

    // Construct the path using filesystem to ensure proper path handling
    std::filesystem::path filePath = std::filesystem::path(_dataPath) / cleanFilename;
    std::string fullPath = filePath.string();

    // std::cout << "Opening file for reading: " << fullPath << std::endl;

    std::ifstream file(fullPath);

    if (!file.is_open())
    {
        std::cout << "File not found: " << fullPath << std::endl;

        // If file doesn't exist, create an empty one
        if (!std::filesystem::exists(fullPath))
        {
            std::cout << "Creating new file: " << fullPath << std::endl;
            std::ofstream newFile(fullPath);
            newFile.close();
            file.open(fullPath);
        }
    }

    return file;
}

std::ofstream DatabaseConnection::openFileForWriting(const std::string &filename, bool append)
{
    // Remove "#file:source" prefix if present
    std::string cleanFilename = filename;
    std::string prefix = "#file:source";
    if (cleanFilename.substr(0, prefix.length()) == prefix)
    {
        cleanFilename = cleanFilename.substr(prefix.length());
    }

    // Construct the path using filesystem to ensure proper path handling
    std::filesystem::path filePath = std::filesystem::path(_dataPath) / cleanFilename;
    std::string fullPath = filePath.string();

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