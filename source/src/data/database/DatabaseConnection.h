#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <string>
#include <fstream>
#include <memory>

/**
 * @class DatabaseConnection
 * @brief Singleton class for managing database connections
 *
 * This class provides a central point for managing database connections
 * in the application. It implements the Singleton pattern to ensure
 * only one database connection exists across the application.
 */
class DatabaseConnection
{
private:
    static std::shared_ptr<DatabaseConnection> _instance; ///< Singleton instance
    std::string _dataPath;                                ///< Path to data storage directory

    /**
     * @brief Private constructor for Singleton pattern
     */
    DatabaseConnection();

public:
    /**
     * @brief Delete copy constructor to enforce Singleton pattern
     */
    DatabaseConnection(const DatabaseConnection &) = delete;

    /**
     * @brief Delete assignment operator to enforce Singleton pattern
     */
    DatabaseConnection &operator=(const DatabaseConnection &) = delete;

    /**
     * @brief Get the singleton instance of DatabaseConnection
     * @return Shared pointer to the DatabaseConnection instance
     */
    static std::shared_ptr<DatabaseConnection> getInstance();

    /**
     * @brief Connect to a database (creates or opens data directory)
     * @param dataPath Path to the data storage directory
     * @return true if connection successful, false otherwise
     */
    bool connect(const std::string &dataPath);

    /**
     * @brief Disconnect from the database
     */
    void disconnect();

    /**
     * @brief Check if connected to a database
     * @return true if connected, false otherwise
     */
    bool isConnected() const;

    /**
     * @brief Open a file for reading
     * @param filename Name of the file to open
     * @return Input file stream for reading
     */
    std::ifstream openFileForReading(const std::string &filename);

    /**
     * @brief Open a file for writing
     * @param filename Name of the file to open
     * @param append true to append to file, false to overwrite
     * @return Output file stream for writing
     */
    std::ofstream openFileForWriting(const std::string &filename, bool append = false);
};

#endif // DATABASE_CONNECTION_H