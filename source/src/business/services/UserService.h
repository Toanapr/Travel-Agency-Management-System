#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <memory>
#include <vector>
#include <optional>
#include <string>
#include "../interfaces/IUserRepository.h"
#include "../models/User.h"

// Forward declaration to avoid circular dependency
class BookingService;

/**
 * @class UserService
 * @brief Service class for user-related business logic
 *
 * This class handles all business logic related to users, including
 * user management and authentication operations. It acts as an intermediary
 * between the presentation layer and the data access layer.
 */
class UserService
{
private:
    std::shared_ptr<IUserRepository> _userRepository; ///< Repository for user data access
    std::shared_ptr<BookingService> _bookingService;  ///< Service for booking operations

public:
    /**
     * @brief Constructor for UserService
     * @param userRepository Repository implementation for user data access
     * @param bookingService Service for booking operations
     */
    UserService(std::shared_ptr<IUserRepository> userRepository,
               std::shared_ptr<BookingService> bookingService = nullptr);

    // User management methods
    /**
     * @brief Get all users in the system
     * @return Vector of all User objects
     */
    std::vector<User> getAllUsers();

    /**
     * @brief Find a user by their ID
     * @param id The unique identifier of the user
     * @return Optional containing the user if found, empty otherwise
     */
    std::optional<User> getUserById(int id);

    /**
     * @brief Search for users by name (partial match)
     * @param name Name or partial name to search for
     * @return Vector of users whose names match the search criteria
     */
    std::vector<User> findUsersByName(const std::string &name);

    /**
     * @brief Add a new user to the system
     * @param user The user object to add
     * @return true if successfully added, false otherwise
     */
    bool addUser(const User &user);

    /**
     * @brief Update an existing user's information
     * @param user The user object with updated information
     * @return true if successfully updated, false otherwise
     */
    bool updateUser(const User &user);    /**
     * @brief Delete a user from the system
     * @param id The unique identifier of the user to delete
     * @return true if successfully deleted, false otherwise
     *         Returns false if the user is referenced in any bookings
     */
    bool deleteUser(int id);
    
    /**
     * @brief Check if a user has any associated bookings
     * @param userId The unique identifier of the user
     * @return true if bookings exist for this user, false otherwise
     */
    bool hasUserBookings(int userId);

    // Authentication methods
};

#endif // USER_SERVICE_H