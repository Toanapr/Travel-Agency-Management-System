#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <memory>
#include <string>
#include <vector>
#include "../console/InputHandler.h"
#include "../console/OutputFormatter.h"
#include "UserMenu.h"
#include "TripMenu.h"
#include "BookingMenu.h"

/**
 * @class MainMenu
 * @brief Main menu handler for the Travel Agency Management System
 *
 * This class manages the main application menu, providing options to navigate
 * to different sub-menus for managing users, trips, and bookings.
 */
class MainMenu
{
private:
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;
    std::shared_ptr<UserMenu> _userMenu;
    std::shared_ptr<TripMenu> _tripMenu;
    std::shared_ptr<BookingMenu> _bookingMenu;
    bool _running;

    // Menu options
    std::vector<std::string> _menuOptions = {
        "User Management",
        "Trip Management",
        "Booking Management",
        "Exit Application"};

    /**
     * @brief Display the welcome message when application starts
     */
    void displayWelcomeMessage() const;

    /**
     * @brief Process the user's menu selection
     * @param choice The menu option chosen by the user
     * @return true if the application should continue running, false otherwise
     */
    bool processMenuChoice(int choice);

public:
    /**
     * @brief Constructor for MainMenu
     * @param inputHandler Shared pointer to the InputHandler
     * @param outputFormatter Shared pointer to the OutputFormatter
     * @param userMenu Shared pointer to the UserMenu
     * @param tripMenu Shared pointer to the TripMenu
     * @param bookingMenu Shared pointer to the BookingMenu
     */
    MainMenu(std::shared_ptr<InputHandler> inputHandler,
             std::shared_ptr<OutputFormatter> outputFormatter,
             std::shared_ptr<UserMenu> userMenu,
             std::shared_ptr<TripMenu> tripMenu,
             std::shared_ptr<BookingMenu> bookingMenu);

    /**
     * @brief Display the main menu and process user input
     * @return true if the application should continue running, false otherwise
     */
    bool show();

    /**
     * @brief Run the main menu loop until exit
     */
    void run();
};

#endif // MAIN_MENU_H