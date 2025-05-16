#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(std::shared_ptr<InputHandler> inputHandler,
                   std::shared_ptr<OutputFormatter> outputFormatter,
                   std::shared_ptr<UserMenu> userMenu,
                   std::shared_ptr<TripMenu> tripMenu,
                   std::shared_ptr<BookingMenu> bookingMenu)
    : _inputHandler(inputHandler),
      _outputFormatter(outputFormatter),
      _userMenu(userMenu),
      _tripMenu(tripMenu),
      _bookingMenu(bookingMenu),
      _running(false)
{
}

void MainMenu::displayWelcomeMessage() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->drawHeader("TRAVEL AGENCY MANAGEMENT SYSTEM", 80, ConsoleColor::CYAN);
    _outputFormatter->center("Your Complete Travel Management Solution", 80, ConsoleColor::YELLOW);
    _outputFormatter->center("Version 1.0", 80);
    _outputFormatter->drawLine(80);
    _outputFormatter->displayMessage("\nWelcome to the Travel Agency Management System. This system allows you to manage\nusers, trips, and bookings efficiently.\n");
    _outputFormatter->displayMessage("Press Enter to continue...");
    std::cin.get();
}

bool MainMenu::processMenuChoice(int choice)
{
    switch (choice)
    {
    case 1: // User Management
        _userMenu->show();
        return true;
    case 2: // Trip Management
        _tripMenu->show();
        return true;
    case 3: // Booking Management
        _bookingMenu->show();
        return true;
    case 4: // Exit Application
        if (_inputHandler->getYesNoInput("Are you sure you want to exit the application?"))
        {
            _outputFormatter->displayMessage("\nThank you for using the Travel Agency Management System. Goodbye!");
            return false; // Signal to exit
        }
        return true;
    default:
        _outputFormatter->displayErrorMessage("Invalid choice. Please try again.");
        return true;
    }
}

bool MainMenu::show()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMenu("Main Menu", _menuOptions);
    int choice = _inputHandler->getIntInput("", 1, _menuOptions.size());
    return processMenuChoice(choice);
}

void MainMenu::run()
{
    displayWelcomeMessage();
    _running = true;

    while (_running)
    {
        _running = show();
    }
}