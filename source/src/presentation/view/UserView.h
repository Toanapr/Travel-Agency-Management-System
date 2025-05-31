#ifndef USER_VIEW_H
#define USER_VIEW_H

#include <memory>
#include <vector>
#include "../../business/models/User.h"
#include "../console/OutputFormatter.h"

/**
 * @class UserView
 * @brief View class for displaying User-related information
 *
 * This class is responsible for presenting User objects in various formats.
 * It uses the OutputFormatter to handle the actual display operations.
 */
class UserView
{
private:
    std::shared_ptr<OutputFormatter> _outputFormatter;

public:
    /**
     * @brief Constructor
     * @param outputFormatter Shared pointer to the OutputFormatter
     */
    explicit UserView(std::shared_ptr<OutputFormatter> outputFormatter);

    /**
     * @brief Display detailed information for a single user
     * @param user The user to display
     */
    void displayUserDetails(const User &user) const;

    /**
     * @brief Display a list of users in a tabular format
     * @param users Vector of users to display
     */
    void displayAllUsers(const std::vector<User> &users) const;
};

#endif // USER_VIEW_H