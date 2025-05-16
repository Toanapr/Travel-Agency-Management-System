#include "MenuHandler.h"

MenuHandler::MenuHandler(std::shared_ptr<UserService> userService,
                         std::shared_ptr<TripService> tripService,
                         std::shared_ptr<BookingService> bookingService)
    : _userService(userService),
      _tripService(tripService),
      _bookingService(bookingService)
{

    // Initialize all components
    initializeComponents();
}

void MenuHandler::initializeComponents()
{
    // Initialize console utilities
    _inputHandler = std::make_shared<InputHandler>();
    _outputFormatter = std::make_shared<OutputFormatter>();

    // Initialize view components
    _userView = std::make_shared<UserView>(_outputFormatter);
    _tripView = std::make_shared<TripView>(_outputFormatter);
    _bookingView = std::make_shared<BookingView>(_outputFormatter);

    // Initialize menu components
    _userMenu = std::make_shared<UserMenu>(_inputHandler, _outputFormatter, _userService, _userView);
    _tripMenu = std::make_shared<TripMenu>(_inputHandler, _outputFormatter, _tripService, _tripView);
    _bookingMenu = std::make_shared<BookingMenu>(_inputHandler, _outputFormatter,
                                                 _bookingService, _userService, _tripService, _bookingView);

    // Initialize main menu
    _mainMenu = std::make_shared<MainMenu>(_inputHandler, _outputFormatter,
                                           _userMenu, _tripMenu, _bookingMenu);
}

void MenuHandler::start()
{
    // Display welcome message and start the main menu
    _mainMenu->run();
}