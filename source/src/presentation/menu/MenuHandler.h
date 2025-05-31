#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <memory>
#include "../console/InputHandler.h"
#include "../console/OutputFormatter.h"
#include "MainMenu.h"
#include "UserMenu.h"
#include "TripMenu.h"
#include "BookingMenu.h"
#include "../view/UserView.h"
#include "../view/TripView.h"
#include "../view/BookingView.h"
#include "../../business/services/UserService.h"
#include "../../business/services/TripService.h"
#include "../../business/services/BookingService.h"

/**
 * @class MenuHandler
 * @brief Manages the creation and coordination of all menu components
 *
 * This class serves as a facade for the menu system, initializing all components
 * and providing access to the main menu. It follows the Facade design pattern
 * to simplify the interface to the complex menu subsystem.
 */
class MenuHandler
{
private:
    // Console utilities
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;

    // View components
    std::shared_ptr<UserView> _userView;
    std::shared_ptr<TripView> _tripView;
    std::shared_ptr<BookingView> _bookingView;

    // Menu components
    std::shared_ptr<UserMenu> _userMenu;
    std::shared_ptr<TripMenu> _tripMenu;
    std::shared_ptr<BookingMenu> _bookingMenu;
    std::shared_ptr<MainMenu> _mainMenu;

    // Services
    std::shared_ptr<UserService> _userService;
    std::shared_ptr<TripService> _tripService;
    std::shared_ptr<BookingService> _bookingService;

    /**
     * @brief Initialize all menu components
     */
    void initializeComponents();

public:
    /**
     * @brief Constructor that initializes the MenuHandler with service dependencies
     * @param userService Shared pointer to the UserService
     * @param tripService Shared pointer to the TripService
     * @param bookingService Shared pointer to the BookingService
     */
    MenuHandler(std::shared_ptr<UserService> userService,
                std::shared_ptr<TripService> tripService,
                std::shared_ptr<BookingService> bookingService);

    /**
     * @brief Start the menu system by displaying the main menu
     */
    void start();
};

#endif // MENU_HANDLER_H