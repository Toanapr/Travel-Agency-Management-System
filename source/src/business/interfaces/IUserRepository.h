#ifndef IUSER_REPOSITORY_H
#define IUSER_REPOSITORY_H

#include <vector>
#include <optional>
#include "../models/User.h"

/**
 * @interface IUserRepository
 * @brief Interface for user data persistence operations
 *
 * This interface defines the contract for classes that handle
 * the persistence of User objects in the data store. It follows
 * the Repository pattern to abstract data access logic.
 */
class IUserRepository
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IUserRepository() = default;

    /**
     * @brief Retrieve all users from the data store
     * @return Vector containing all users
     */
    virtual std::vector<User> getAll() = 0;

    /**
     * @brief Find a user by their ID
     * @param id The unique identifier of the user to find
     * @return Optional containing the user if found, empty otherwise
     */
    virtual std::optional<User> getById(int id) = 0;

    /**
     * @brief Find users by name (partial match)
     * @param name The name or part of the name to search for
     * @return Vector of users whose names match the search criteria
     */
    virtual std::vector<User> findByName(const std::string &name) = 0;

    /**
     * @brief Add a new user to the data store
     * @param user The user object to add
     * @return true if the operation was successful, false otherwise
     */
    virtual bool add(const User &user) = 0;

    /**
     * @brief Update an existing user in the data store
     * @param user The user object with updated information
     * @return true if the operation was successful, false otherwise
     */
    virtual bool update(const User &user) = 0;

    /**
     * @brief Remove a user from the data store
     * @param id The unique identifier of the user to remove
     * @return true if the operation was successful, false otherwise
     */
    virtual bool remove(int id) = 0;
};

#endif // IUSER_REPOSITORY_H