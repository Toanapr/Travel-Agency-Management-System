#ifndef USER_DTO_H
#define USER_DTO_H

#include <string>

/**
 * @class UserDTO
 * @brief Data Transfer Object for User entities
 *
 * This class represents the data structure used to transfer user data
 * between the data layer and business layer of the application.
 * It is designed to match the CSV structure for user data.
 */
class UserDTO
{
private:
    int _id;              ///< Unique identifier for the user
    std::string _name;    ///< User's full name
    std::string _address; ///< User's address
    std::string _phone;   ///< User's phone number
    std::string _email;   ///< User's email address

public:
    /**
     * @brief Default constructor
     */
    UserDTO();

    /**
     * @brief Parameterized constructor
     * @param id User's unique identifier
     * @param name User's full name
     * @param address User's address
     * @param phone User's phone number
     * @param email User's email address
     */
    UserDTO(int id, const std::string &name, const std::string &address,
            const std::string &phone, const std::string &email);

    /**
     * @brief Get the user's ID
     * @return User's unique identifier
     */
    int getId() const;

    /**
     * @brief Get the user's name
     * @return User's full name
     */
    const std::string &getName() const;

    /**
     * @brief Get the user's address
     * @return User's address
     */
    const std::string &getAddress() const;

    /**
     * @brief Get the user's phone number
     * @return User's phone number
     */
    const std::string &getPhone() const;

    /**
     * @brief Get the user's email
     * @return User's email address
     */
    const std::string &getEmail() const;

    /**
     * @brief Set the user's ID
     * @param id New unique identifier
     */
    void setId(int id);

    /**
     * @brief Set the user's name
     * @param name New name
     */
    void setName(const std::string &name);

    /**
     * @brief Set the user's address
     * @param address New address
     */
    void setAddress(const std::string &address);

    /**
     * @brief Set the user's phone number
     * @param phone New phone number
     */
    void setPhone(const std::string &phone);

    /**
     * @brief Set the user's email
     * @param email New email address
     */
    void setEmail(const std::string &email);
};

#endif // USER_DTO_H