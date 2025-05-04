#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include "../../business/interfaces/IUserRepository.h"
#include "../../business/models/User.h"
#include "../database/DatabaseConnection.h"

/**
 * @class UserRepository
 * @brief Implementation of IUserRepository for CSV file storage
 *
 * This class provides an implementation of the IUserRepository interface
 * that uses CSV files for persistent storage of user data. It handles all
 * CRUD operations for User objects, translating between object and CSV formats.
 */
class UserRepository : public IUserRepository
{
private:
    std::shared_ptr<DatabaseConnection> _dbConnection; ///< Database connection for file access
    const std::string _filename = "users.csv";         ///< Name of the CSV file for user data storage

    /**
     * @brief Convert a CSV line to a User object
     * @param line CSV-formatted string containing user data
     * @return User object created from the CSV data
     */
    User parseUserFromCsv(const std::string &line);

    /**
     * @brief Convert a User object to CSV format
     * @param user User object to convert
     * @return CSV-formatted string representing the user
     */
    std::string convertUserToCsv(const User &user);

    /**
     * @brief Generate the next available ID for a new user
     * @return Next available unique identifier
     */
    int getNextId();

public:
    /**
     * @brief Constructor for UserRepository
     * @param dbConnection Shared pointer to DatabaseConnection for file operations
     */
    UserRepository(std::shared_ptr<DatabaseConnection> dbConnection);

    // IUserRepository implementation
    /**
     * @brief Retrieve all users from storage
     * @return Vector of all User objects
     */
    std::vector<User> getAll() override;

    /**
     * @brief Find a user by their ID
     * @param id The unique identifier of the user to find
     * @return Optional containing the user if found, empty otherwise
     */
    std::optional<User> getById(int id) override;

    /**
     * @brief Find users by name (partial match)
     * @param name The name or part of the name to search for
     * @return Vector of users whose names match the search criteria
     */
    std::vector<User> findByName(const std::string &name) override;

    /**
     * @brief Add a new user to storage
     * @param user The user object to add
     * @return true if the operation was successful, false otherwise
     */
    bool add(const User &user) override;

    /**
     * @brief Update an existing user in storage
     * @param user The user object with updated information
     * @return true if the operation was successful, false otherwise
     */
    bool update(const User &user) override;

    /**
     * @brief Remove a user from storage
     * @param id The unique identifier of the user to remove
     * @return true if the operation was successful, false otherwise
     */
    bool remove(int id) override;
};

#endif // USER_REPOSITORY_H