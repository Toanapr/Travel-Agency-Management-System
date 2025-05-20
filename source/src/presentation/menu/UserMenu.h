#ifndef USER_MENU_H
#define USER_MENU_H

#include <memory>
#include <string>
#include <vector>
#include "../console/InputHandler.h"
#include "../console/OutputFormatter.h"
#include "../../business/services/UserService.h"
#include "../view/UserView.h"

/**
 * @class UserMenu
 * @brief Handles the user management menu functionality
 *
 * This class manages the menu for user operations including viewing all users,
 * finding users, adding, editing, and deleting users.
 */
class UserMenu
{
private:
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;
    std::shared_ptr<UserService> _userService;
    std::shared_ptr<UserView> _userView;

    // Menu options
    std::vector<std::string> _menuOptions = {
        "View All Users",
        "Find User",
        "Add New User",
        "Edit User",
        "Delete User",
        "Return to Main Menu"};

    /**
     * @brief Process user's menu choice
     * @param choice The option selected by the user
     */
    void processMenuChoice(int choice);

    /**
     * @brief Display all users in the system
     */
    void viewAllUsers() const;

    /**
     * @brief Find a user by ID or name
     */
    void findUser() const;

    /**
     * @brief Add a new user to the system
     */
    void addUser();

    /**
     * @brief Edit an existing user
     */
    void editUser();

    /**
     * @brief Delete a user from the system
     */
    void deleteUser();

public:
    /**
     * @brief Constructor for UserMenu
     * @param inputHandler Shared pointer to InputHandler for user input
     * @param outputFormatter Shared pointer to OutputFormatter for display
     * @param userService Shared pointer to UserService for business logic
     * @param userView Shared pointer to UserView for presentation
     */
    UserMenu(std::shared_ptr<InputHandler> inputHandler,
             std::shared_ptr<OutputFormatter> outputFormatter,
             std::shared_ptr<UserService> userService,
             std::shared_ptr<UserView> userView);

    /**
     * @brief Display the user management menu and process selection
     */
    void show();
};

#endif // USER_MENU_H