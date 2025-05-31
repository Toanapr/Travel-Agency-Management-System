#ifndef BOOKING_MENU_H
#define BOOKING_MENU_H

#include <memory>
#include <string>
#include <vector>
#include "../console/InputHandler.h"
#include "../console/OutputFormatter.h"
#include "../../business/services/BookingService.h"
#include "../../business/services/UserService.h"
#include "../../business/services/TripService.h"
#include "../view/BookingView.h"

/**
 * @class BookingMenu
 * @brief Handles the booking management menu functionality
 *
 * This class manages the menu for booking operations including viewing all bookings,
 * finding bookings, creating new bookings, updating and canceling bookings.
 */
class BookingMenu
{
private:
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;
    std::shared_ptr<BookingService> _bookingService;
    std::shared_ptr<UserService> _userService;
    std::shared_ptr<TripService> _tripService;
    std::shared_ptr<BookingView> _bookingView;    // Menu options
    std::vector<std::string> _menuOptions = {
        "View All Bookings",
        "Find Booking",
        "Create New Booking",
        "Update Booking Status",
        "Cancel Booking",
        "Return to Main Menu"};

    /**
     * @brief Process booking's menu choice
     * @param choice The option selected by the user
     */
    void processMenuChoice(int choice);

    /**
     * @brief Display all bookings in the system
     */
    void viewAllBookings() const;    /**
     * @brief Display the find booking submenu with different search options
     */
    void findBooking() const;

    /**
     * @brief Find a booking by its ID
     */
    void findBookingById() const;

    /**
     * @brief Find all bookings made by a specific user
     */
    void findBookingsByUser() const;

    /**
     * @brief Find all bookings for a specific trip
     */
    void findBookingsByTrip() const;

    /**
     * @brief Create a new booking
     */
    void createBooking();

    /**
     * @brief Update the status of an existing booking
     */
    void updateBookingStatus();

    /**
     * @brief Cancel an existing booking
     */
    void cancelBooking();

public:
    /**
     * @brief Constructor for BookingMenu
     * @param inputHandler Shared pointer to InputHandler for user input
     * @param outputFormatter Shared pointer to OutputFormatter for display
     * @param bookingService Shared pointer to BookingService for business logic
     * @param userService Shared pointer to UserService for user data
     * @param tripService Shared pointer to TripService for trip data
     * @param bookingView Shared pointer to BookingView for presentation
     */
    BookingMenu(std::shared_ptr<InputHandler> inputHandler,
                std::shared_ptr<OutputFormatter> outputFormatter,
                std::shared_ptr<BookingService> bookingService,
                std::shared_ptr<UserService> userService,
                std::shared_ptr<TripService> tripService,
                std::shared_ptr<BookingView> bookingView);

    /**
     * @brief Display the booking management menu and process selection
     */
    void show();
};

#endif // BOOKING_MENU_H