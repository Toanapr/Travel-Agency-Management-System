#ifndef USER_H
#define USER_H

#include <string>

/**
 * @class User
 * @brief Represents a user in the travel agency system
 *
 * The User class stores information about customers that use the travel agency
 * services, including personal information and contact details.
 */
class User
{
private:
    int _id;              ///< Unique identifier for the user
    std::string _name;    ///< Full name of the user
    std::string _address; ///< Postal address of the user
    std::string _phone;   ///< Contact phone number
    std::string _email;   ///< Email address

public:
    /**
     * @brief Constructor for creating a new user
     * @param id Unique identifier for the user
     * @param name Full name of the user
     * @param address Postal address of the user
     * @param phone Contact phone number
     * @param email Email address
     */
    User(int id, const std::string &name, const std::string &address,
         const std::string &phone, const std::string &email);

    // Getters
    /**
     * @brief Get the user's ID
     * @return The unique identifier for the user
     */
    int getId() const;

    /**
     * @brief Get the user's name
     * @return The full name of the user
     */
    std::string getName() const;

    /**
     * @brief Get the user's address
     * @return The postal address of the user
     */
    std::string getAddress() const;

    /**
     * @brief Get the user's phone number
     * @return The contact phone number
     */
    std::string getPhone() const;

    /**
     * @brief Get the user's email
     * @return The email address
     */
    std::string getEmail() const; // Setters
    /**
     * @brief Set the user's ID
     * @param id The new ID for the user
     */
    void setId(int id);

    /**
     * @brief Set the user's name
     * @param name The new name for the user
     */
    void setName(const std::string &name);

    /**
     * @brief Set the user's address
     * @param address The new address for the user
     */
    void setAddress(const std::string &address);

    /**
     * @brief Set the user's phone number
     * @param phone The new phone number for the user
     */
    void setPhone(const std::string &phone);

    /**
     * @brief Set the user's email
     * @param email The new email for the user
     */
    void setEmail(const std::string &email);

    /**
     * @brief Equality operator for comparing User objects
     * @param other The other User object to compare with
     * @return true if all fields are equal, false otherwise
     */
    bool operator==(const User &other) const;
};

#endif // USER_H