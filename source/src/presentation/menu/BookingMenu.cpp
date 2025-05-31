#include "BookingMenu.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono> // Add missing chrono include

BookingMenu::BookingMenu(std::shared_ptr<InputHandler> inputHandler,
                         std::shared_ptr<OutputFormatter> outputFormatter,
                         std::shared_ptr<BookingService> bookingService,
                         std::shared_ptr<UserService> userService,
                         std::shared_ptr<TripService> tripService,
                         std::shared_ptr<BookingView> bookingView)
    : _inputHandler(inputHandler),
      _outputFormatter(outputFormatter),
      _bookingService(bookingService),
      _userService(userService),
      _tripService(tripService),
      _bookingView(bookingView)
{
}

void BookingMenu::show()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMenu("Booking Management", _menuOptions);
    int choice = _inputHandler->getIntInput("", 1, _menuOptions.size());
    processMenuChoice(choice);
}

void BookingMenu::processMenuChoice(int choice)
{
    switch (choice)
    {
    case 1: // View All Bookings
        viewAllBookings();
        break;
    case 2: // Find Booking
        findBooking();
        break;
    case 3: // Create New Booking
        createBooking();
        break;
    case 4: // Update Booking Status
        updateBookingStatus();
        break;
    case 5: // Cancel Booking
        cancelBooking();
        break;
    case 6: // Return to Main Menu
        return;
    default:
        _outputFormatter->displayErrorMessage("Invalid choice. Please try again.");
        break;
    }

    // Wait for user input before returning to menu
    _inputHandler->getStringInput("\nPress Enter to return to Booking Management menu...", true);
    show(); // Show the menu again (recursive)
}

void BookingMenu::viewAllBookings() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== VIEW ALL BOOKINGS ===\n");

    try
    {
        auto bookings = _bookingService->getAllBookings();
        if (bookings.empty())
        {
            _outputFormatter->displayMessage("No bookings found in the system.");
        }
        else
        {
            // Retrieve all users and trips for display
            auto users = _userService->getAllUsers();
            auto trips = _tripService->getAllTrips();
            _bookingView->displayAllBookings(bookings, users, trips);
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Failed to retrieve bookings: ") + e.what());
    }
}

void BookingMenu::findBooking() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND BOOKING ===\n");

    std::vector<std::string> findOptions = {
        "Find Booking by ID",
        "Find Bookings by User",
        "Find Bookings by Trip",
        "Return to Booking Menu"};

    _outputFormatter->displayMenu("Search Options", findOptions);
    int choice = _inputHandler->getIntInput("", 1, findOptions.size());

    switch (choice)
    {
    case 1: // Find Booking by ID
        findBookingById();
        break;
    case 2: // Find Bookings by User
        findBookingsByUser();
        break;
    case 3: // Find Bookings by Trip
        findBookingsByTrip();
        break;
    case 4: // Return to Booking Menu
        return;
    default:
        _outputFormatter->displayErrorMessage("Invalid choice. Please try again.");
        break;
    }
}

void BookingMenu::findBookingById() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND BOOKING BY ID ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter booking ID: ", 1);
        auto bookingOpt = _bookingService->getBookingById(id);

        if (!bookingOpt)
        {
            _outputFormatter->displayMessage("No booking found with that ID.");
            return;
        }

        Booking booking = *bookingOpt;

        // Find associated user
        auto userOpt = _userService->getUserById(booking.getUserId());
        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("User associated with this booking not found.");
            return;
        }

        // Find associated trip
        auto tripOpt = _tripService->getTripById(booking.getTripId());
        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("Trip associated with this booking not found.");
            return;
        }

        _bookingView->displayBookingDetails(booking, *userOpt, *tripOpt);
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error during search: ") + e.what());
    }
}

void BookingMenu::findBookingsByUser() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND BOOKINGS BY USER ===\n");

    try
    {
        // First find the user
        int userId = _inputHandler->getIntInput("Enter user ID: ", 1);
        auto userOpt = _userService->getUserById(userId);

        if (!userOpt)
        {
            _outputFormatter->displayMessage("No user found with that ID.");
            return;
        }

        _outputFormatter->displayMessage("\nUser found: " + userOpt->getName());

        // Get all bookings for this user
        auto bookings = _bookingService->findBookingsByUserId(userId);

        if (bookings.empty())
        {
            _outputFormatter->displayMessage("No bookings found for this user.");
            return;
        }

        // Get all trips for display
        auto trips = _tripService->getAllTrips();
        std::vector<User> users = {*userOpt}; // Just need this one user

        _bookingView->displayAllBookings(bookings, users, trips);
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error during search: ") + e.what());
    }
}

void BookingMenu::findBookingsByTrip() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND BOOKINGS BY TRIP ===\n");

    try
    {
        // First find the trip
        int tripId = _inputHandler->getIntInput("Enter trip ID: ", 1);
        auto tripOpt = _tripService->getTripById(tripId);

        if (!tripOpt)
        {
            _outputFormatter->displayMessage("No trip found with that ID.");
            return;
        }

        _outputFormatter->displayMessage("\nTrip found: " + tripOpt->getName());

        // Get all bookings for this trip
        auto bookings = _bookingService->findBookingsByTripId(tripId);

        if (bookings.empty())
        {
            _outputFormatter->displayMessage("No bookings found for this trip.");
            return;
        }

        // Get all users for display
        auto users = _userService->getAllUsers();
        std::vector<Trip> trips = {*tripOpt}; // Just need this one trip

        _bookingView->displayAllBookings(bookings, users, trips);
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error during search: ") + e.what());
    }
}

void BookingMenu::createBooking()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== CREATE NEW BOOKING ===\n");

    try
    {
        // Get user ID
        int userId = _inputHandler->getIntInput("Enter user ID: ", 1);
        auto userOpt = _userService->getUserById(userId);
        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("User not found. Booking cannot be created.");
            return;
        }

        // Display user details
        _outputFormatter->displayMessage("\nUser found:");
        _outputFormatter->displayUser(*userOpt);

        // Get trip ID
        int tripId = _inputHandler->getIntInput("\nEnter trip ID: ", 1);
        auto tripOpt = _tripService->getTripById(tripId);
        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("Trip not found. Booking cannot be created.");
            return;
        }

        // Display trip details
        _outputFormatter->displayMessage("\nTrip found:");
        _outputFormatter->displayTrip(*tripOpt);

        // Check available seats
        int availableSeats = tripOpt->getAvailableSeats();
        if (availableSeats <= 0)
        {
            _outputFormatter->displayErrorMessage("No available seats for this trip. Booking cannot be created.");
            return;
        }

        // Get number of people
        int maxPeople = availableSeats;
        _outputFormatter->displayInfoMessage("This trip has " + std::to_string(availableSeats) + " available seats.");
        int numberOfPeople = _inputHandler->getIntInput("Enter number of people for this booking: ", 1, maxPeople);

        // Calculate and display total cost
        double totalCost = _bookingService->calculateTotalCost(tripId, numberOfPeople);
        _outputFormatter->displayMessage("\nTotal cost for this booking: $" + std::to_string(totalCost));

        // Confirm booking
        if (_inputHandler->getYesNoInput("Confirm booking?"))
        {
            // Get current date for booking date
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std::tm *timeinfo = std::localtime(&time);
            std::ostringstream oss;
            oss << std::put_time(timeinfo, "%Y-%m-%d");
            std::string bookingDate = oss.str();

            // Create booking
            if (_bookingService->createBooking(userId, tripId, bookingDate, numberOfPeople))
            {
                _outputFormatter->displaySuccessMessage("Booking created successfully!");
            }
            else
            {
                _outputFormatter->displayErrorMessage("Failed to create booking.");
            }
        }
        else
        {
            _outputFormatter->displayMessage("Booking cancelled.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error creating booking: ") + e.what());
    }
}

void BookingMenu::updateBookingStatus()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== UPDATE BOOKING STATUS ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter booking ID: ", 1);
        auto bookingOpt = _bookingService->getBookingById(id);

        if (!bookingOpt)
        {
            _outputFormatter->displayErrorMessage("No booking found with that ID.");
            return;
        }

        Booking booking = *bookingOpt;

        // Find associated user
        auto userOpt = _userService->getUserById(booking.getUserId());
        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("User associated with this booking not found.");
            return;
        }

        // Find associated trip
        auto tripOpt = _tripService->getTripById(booking.getTripId());
        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("Trip associated with this booking not found.");
            return;
        }

        // Display current booking details
        _outputFormatter->displayMessage("Current booking details:");
        _outputFormatter->displayBooking(booking, *userOpt, *tripOpt);

        // Get new status
        _outputFormatter->displayMessage("\nCurrent status: " + booking.getStatus());
        _outputFormatter->displayMessage("Available statuses: Confirmed, Pending, Completed");
        std::string newStatus = _inputHandler->getStringInput("Enter new status: ");

        // Validate status
        if (newStatus != "Confirmed" && newStatus != "Pending" && newStatus != "Completed")
        {
            _outputFormatter->displayErrorMessage("Invalid status. Status must be one of: Confirmed, Pending, Completed");
            return;
        }

        // Confirm status change
        if (_inputHandler->getYesNoInput("Change status to '" + newStatus + "'?"))
        {
            if (_bookingService->updateBookingStatus(id, newStatus))
            {
                _outputFormatter->displaySuccessMessage("Booking status updated successfully!");
            }
            else
            {
                _outputFormatter->displayErrorMessage("Failed to update booking status.");
            }
        }
        else
        {
            _outputFormatter->displayMessage("Status update cancelled.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error updating status: ") + e.what());
    }
}

void BookingMenu::cancelBooking()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== CANCEL BOOKING ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter booking ID to cancel: ", 1);
        auto bookingOpt = _bookingService->getBookingById(id);

        if (!bookingOpt)
        {
            _outputFormatter->displayErrorMessage("No booking found with that ID.");
            return;
        }

        Booking booking = *bookingOpt;

        // Check if already cancelled
        if (booking.getStatus() == "Cancelled")
        {
            _outputFormatter->displayWarningMessage("This booking is already cancelled.");
            return;
        }

        // Find associated user
        auto userOpt = _userService->getUserById(booking.getUserId());
        if (!userOpt)
        {
            _outputFormatter->displayErrorMessage("User associated with this booking not found.");
            return;
        }

        // Find associated trip
        auto tripOpt = _tripService->getTripById(booking.getTripId());
        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("Trip associated with this booking not found.");
            return;
        }

        // Display booking details
        _outputFormatter->displayMessage("Booking details:");
        _outputFormatter->displayBooking(booking, *userOpt, *tripOpt);

        // Confirm cancellation
        if (_inputHandler->getYesNoInput("Are you sure you want to cancel this booking?"))
        {
            if (_bookingService->cancelBooking(id))
            {
                _outputFormatter->displaySuccessMessage("Booking cancelled successfully!");
            }
            else
            {
                _outputFormatter->displayErrorMessage("Failed to cancel booking.");
            }
        }
        else
        {
            _outputFormatter->displayMessage("Cancellation aborted.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error cancelling booking: ") + e.what());
    }
}