#include "UserMenu.h"
#include <iostream>

UserMenu::UserMenu(std::shared_ptr<InputHandler> inputHandler,
                   std::shared_ptr<OutputFormatter> outputFormatter,
                   std::shared_ptr<UserService> userService,
                   std::shared_ptr<UserView> userView)
    : _inputHandler(inputHandler),
      _outputFormatter(outputFormatter),
      _userService(userService),
      _userView(userView)
{
}

void UserMenu::show()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMenu("User Management", _menuOptions);
    int choice = _inputHandler->getIntInput("", 1, _menuOptions.size());
    processMenuChoice(choice);
}

void UserMenu::processMenuChoice(int choice)
{
    switch (choice)
    {
    case 1: // View All Users
        viewAllUsers();
        break;
    case 2: // Find User
        findUser();
        break;
    case 3: // Add New User
        addUser();
        break;
    case 4: // Edit User
        editUser();
        break;
    case 5: // Delete User
        deleteUser();
        break;
    case 6: // Return to Main Menu
        return;
    default:
        _outputFormatter->displayErrorMessage("Invalid choice. Please try again.");
        break;
    }

    // Wait for user input before returning to menu
    _inputHandler->getStringInput("\nPress Enter to return to User Management menu...", true);
    show(); // Show the menu again (recursive)
}

void UserMenu::viewAllUsers() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== VIEW ALL USERS ===\n");

    try
    {
        auto users = _userService->getAllUsers();
        if (users.empty())
        {
            _outputFormatter->displayMessage("No users found in the system.");
        }
        else
        {
            _userView->displayAllUsers(users);
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Failed to retrieve users: ") + e.what());
    }
}

void UserMenu::findUser() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND USER ===\n");

    std::vector<std::string> searchOptions = {
        "Find by ID",
        "Find by Name",
        "Return to User Menu"};

    _outputFormatter->displayMenu("Search Options", searchOptions);
    int choice = _inputHandler->getIntInput("", 1, searchOptions.size());

    try
    {
        switch (choice)
        {
        case 1:
        { // Find by ID
            int id = _inputHandler->getIntInput("Enter user ID: ", 1);
            auto userOpt = _userService->getUserById(id);
            if (userOpt)
            {
                _userView->displayUserDetails(*userOpt);
            }
            else
            {
                _outputFormatter->displayMessage("No user found with that ID.");
            }
            break;
        }
        case 2:
        { // Find by Name
            std::string name = _inputHandler->getStringInput("Enter user name (or part of name): ");
            auto users = _userService->findUsersByName(name);
            if (users.empty())
            {
                _outputFormatter->displayMessage("No users found matching the search criteria.");
            }
            else
            {
                _userView->displayAllUsers(users);
            }
            break;
        }
        case 3: // Return to User Menu
            return;
        default:
            _outputFormatter->displayErrorMessage("Invalid choice.");
            break;
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error during search: ") + e.what());
    }
}

void UserMenu::addUser()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== ADD NEW USER ===\n");

    try
    {
        // Get user information
        std::string name = _inputHandler->getStringInput("Enter user name: ");
        std::string address = _inputHandler->getStringInput("Enter user address: ");
        std::string phone = _inputHandler->getPhoneInput("Enter user phone number: ");
        std::string email = _inputHandler->getEmailInput("Enter user email: ");

        // Create a new User (ID will be set by the service)
        User newUser(0, name, address, phone, email);

        // Add the user to the system
        if (_userService->addUser(newUser))
        {
            _outputFormatter->displaySuccessMessage("User added successfully!");
        }
        else
        {
            _outputFormatter->displayErrorMessage("Failed to add user.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error adding user: ") + e.what());
    }
}

void UserMenu::editUser()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== EDIT USER ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter the ID of the user to edit: ", 1);
        auto userOpt = _userService->getUserById(id);

        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("No user found with that ID.");
            return;
        }

        User user = *userOpt;
        _userView->displayUserDetails(user);

        // Get updated information
        _outputFormatter->displayMessage("\nEnter new information (leave empty to keep current value):");

        std::string name = _inputHandler->getStringInput("Name [" + user.getName() + "]: ", true);
        if (!name.empty())
            user.setName(name);

        std::string address = _inputHandler->getStringInput("Address [" + user.getAddress() + "]: ", true);
        if (!address.empty())
            user.setAddress(address);

        std::string phone = _inputHandler->getStringInput("Phone [" + user.getPhone() + "]: ", true);
        if (!phone.empty())
        {
            if (_inputHandler->validatePhone(phone))
            {
                user.setPhone(phone);
            }
            else
            {
                _outputFormatter->displayErrorMessage("Invalid phone format. Keeping original value.");
            }
        }

        std::string email = _inputHandler->getStringInput("Email [" + user.getEmail() + "]: ", true);
        if (!email.empty())
        {
            if (_inputHandler->validateEmail(email))
            {
                user.setEmail(email);
            }
            else
            {
                _outputFormatter->displayErrorMessage("Invalid email format. Keeping original value.");
            }
        }

        // Update the user
        if (_userService->updateUser(user))
        {
            _outputFormatter->displaySuccessMessage("User information updated successfully!");
        }
        else
        {
            _outputFormatter->displayErrorMessage("Failed to update user information.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error updating user: ") + e.what());
    }
}

void UserMenu::deleteUser()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== DELETE USER ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter the ID of the user to delete: ", 1);
        auto userOpt = _userService->getUserById(id);

        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("No user found with that ID.");
            return;
        }

        User user = *userOpt;
        _userView->displayUserDetails(user);        if (_inputHandler->getYesNoInput("Are you sure you want to delete this user?"))
        {
            // Check if user has bookings first
            if (_userService->hasUserBookings(id))
            {
                _outputFormatter->displayErrorMessage("Cannot delete user: There are bookings associated with this user.");
            }
            else if (_userService->deleteUser(id))
            {
                _outputFormatter->displaySuccessMessage("User deleted successfully!");
            }
            else
            {
                _outputFormatter->displayErrorMessage("Failed to delete user.");
            }
        }
        else
        {
            _outputFormatter->displayMessage("User deletion cancelled.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error deleting user: ") + e.what());
    }
}