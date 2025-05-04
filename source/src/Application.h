#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "data/database/DatabaseConnection.h"
#include "data/repositories/UserRepository.h"
#include "data/repositories/TripRepository.h"
#include "data/repositories/BookingRepository.h"
#include "business/services/UserService.h"
#include "business/services/TripService.h"
#include "business/services/BookingService.h"
#include "presentation/menu/MenuHandler.h"
#include "presentation/console/InputHandler.h"
#include "presentation/console/OutputFormatter.h"

/**
 * @class Application
 * @brief Main application class that manages the travel agency system
 *
 * The Application class is the main entry point for the travel agency management system.
 * It initializes all components, manages dependencies, and controls the application lifecycle.
 * This class follows the Singleton pattern to ensure only one instance exists.
 */
class Application
{
private:
    // Database
    std::shared_ptr<DatabaseConnection> _dbConnection;

    // Repositories
    std::shared_ptr<IUserRepository> _userRepository;
    std::shared_ptr<ITripRepository> _tripRepository;
    std::shared_ptr<IBookingRepository> _bookingRepository;

    // Services
    std::shared_ptr<UserService> _userService;
    std::shared_ptr<TripService> _tripService;
    std::shared_ptr<BookingService> _bookingService;

    // UI Components
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;
    std::shared_ptr<MenuHandler> _menuHandler;

    /**
     * @brief Initialize database connection
     */
    void initializeDatabase();

    /**
     * @brief Initialize repository components
     */
    void initializeRepositories();

    /**
     * @brief Initialize service components
     */
    void initializeServices();

    /**
     * @brief Initialize UI components
     */
    void initializeUIComponents();

    /**
     * @brief Private constructor to enforce the Singleton pattern
     */
    Application();

public:
    /**
     * @brief Delete copy constructor to enforce Singleton pattern
     */
    Application(const Application &) = delete;

    /**
     * @brief Delete assignment operator to enforce Singleton pattern
     */
    Application &operator=(const Application &) = delete;

    /**
     * @brief Get the singleton instance of the Application
     * @return Reference to the Application instance
     */
    static Application &getInstance();

    /**
     * @brief Initialize all application components
     */
    void initialize();

    /**
     * @brief Run the application's main loop
     */
    void run();

    /**
     * @brief Clean up resources and shut down the application
     */
    void shutdown();
};

#endif // APPLICATION_H