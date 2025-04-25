#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <string>
#include <vector>
#include <memory>
#include "../../business/services/UserService.h"
#include "../../business/services/TripService.h"
#include "../../business/services/BookingService.h"

// Forward declarations
class InputHandler;
class OutputFormatter;

/**
 * @class MenuHandler
 * @brief Manages the application's console menu system
 *
 * This class is responsible for displaying menus to the user and handling
 * user interactions with the menu system. It coordinates between user input,
 * business services, and output formatting to provide a complete user interface.
 */
class MenuHandler
{
private:
    std::shared_ptr<UserService> _userService;         ///< Service for user-related operations
    std::shared_ptr<TripService> _tripService;         ///< Service for trip-related operations
    std::shared_ptr<BookingService> _bookingService;   ///< Service for booking-related operations
    std::shared_ptr<InputHandler> _inputHandler;       ///< Handler for user input
    std::shared_ptr<OutputFormatter> _outputFormatter; ///< Formatter for console output

    bool _isRunning;    ///< Flag indicating if the menu system is active
    int _currentUserId; ///< Currently logged in user ID, -1 if none

    // Menu display methods
    /**
     * @brief Display the main menu with primary options
     */
    void displayMainMenu();

    /**
     * @brief Display the user account management menu
     */
    void displayUserMenu();

    /**
     * @brief Display the trip browsing and management menu
     */
    void displayTripMenu();

    /**
     * @brief Display the booking management menu
     */
    void displayBookingMenu();

    /**
     * @brief Display the administrator menu with advanced options
     */
    void displayAdminMenu();

    // Menu action methods
    /**
     * @brief Handle user selection from the main menu
     * @param choice The numeric choice made by the user
     */
    void handleMainMenuChoice(int choice);

    /**
     * @brief Handle user selection from the user menu
     * @param choice The numeric choice made by the user
     */
    void handleUserMenuChoice(int choice);

    /**
     * @brief Handle user selection from the trip menu
     * @param choice The numeric choice made by the user
     */
    void handleTripMenuChoice(int choice);

    /**
     * @brief Handle user selection from the booking menu
     * @param choice The numeric choice made by the user
     */
    void handleBookingMenuChoice(int choice);

    /**
     * @brief Handle user selection from the admin menu
     * @param choice The numeric choice made by the user
     */
    void handleAdminMenuChoice(int choice);

    // User related actions
    /**
     * @brief Register a new user in the system
     */
    void registerUser();

    /**
     * @brief Log a user into the system
     */
    void loginUser();

    /**
     * @brief Log the current user out of the system
     */
    void logoutUser();

    /**
     * @brief Display the current user's profile information
     */
    void displayUserProfile();

    /**
     * @brief Update the current user's profile information
     */
    void updateUserProfile();

    // Trip related actions
    /**
     * @brief Display all available trips
     */
    void viewAllTrips();

    /**
     * @brief Search for trips based on user criteria
     */
    void searchTrips();

    /**
     * @brief View detailed information about a specific trip
     * @param tripId The ID of the trip to view
     */
    void viewTripDetails(int tripId);

    // Booking related actions
    /**
     * @brief Create a new booking for the current user
     */
    void createNewBooking();

    /**
     * @brief View all bookings for the current user
     */
    void viewUserBookings();

    /**
     * @brief Cancel an existing booking
     */
    void cancelBooking();

    // Admin related actions
    /**
     * @brief Add a new trip to the system (admin only)
     */
    void addNewTrip();

    /**
     * @brief Update an existing trip's details (admin only)
     */
    void updateTrip();

    /**
     * @brief Remove a trip from the system (admin only)
     */
    void removeTrip();

    /**
     * @brief View all users in the system (admin only)
     */
    void viewAllUsers();

    /**
     * @brief View all bookings in the system (admin only)
     */
    void viewAllBookings();

public:
    /**
     * @brief Constructor for MenuHandler
     * @param userService Service for user-related operations
     * @param tripService Service for trip-related operations
     * @param bookingService Service for booking-related operations
     * @param inputHandler Handler for user input
     * @param outputFormatter Formatter for console output
     */
    MenuHandler(std::shared_ptr<UserService> userService,
                std::shared_ptr<TripService> tripService,
                std::shared_ptr<BookingService> bookingService,
                std::shared_ptr<InputHandler> inputHandler,
                std::shared_ptr<OutputFormatter> outputFormatter);

    /**
     * @brief Start the menu system
     */
    void start();

    /**
     * @brief Stop the menu system
     */
    void stop();

    /**
     * @brief Check if the menu system is currently running
     * @return true if the menu system is running, false otherwise
     */
    bool isRunning() const;
};

#endif // MENU_HANDLER_H