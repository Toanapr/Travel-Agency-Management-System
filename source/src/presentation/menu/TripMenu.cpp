#include "TripMenu.h"
#include <iostream>

TripMenu::TripMenu(std::shared_ptr<InputHandler> inputHandler,
                   std::shared_ptr<OutputFormatter> outputFormatter,
                   std::shared_ptr<TripService> tripService,
                   std::shared_ptr<TripView> tripView)
    : _inputHandler(inputHandler),
      _outputFormatter(outputFormatter),
      _tripService(tripService),
      _tripView(tripView)
{
}

void TripMenu::show()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMenu("Trip Management", _menuOptions);
    int choice = _inputHandler->getIntInput("", 1, _menuOptions.size());
    processMenuChoice(choice);
}

void TripMenu::processMenuChoice(int choice)
{
    switch (choice)
    {
    case 1: // View All Trips
        viewAllTrips();
        break;
    case 2: // Find Trip
        findTrip();
        break;
    case 3: // Add New Trip
        addTrip();
        break;
    case 4: // Edit Trip
        editTrip();
        break;
    case 5: // Delete Trip
        deleteTrip();
        break;
    case 6: // Return to Main Menu
        return;
    default:
        _outputFormatter->displayErrorMessage("Invalid choice. Please try again.");
        break;
    }

    // Wait for user input before returning to menu
    _inputHandler->getStringInput("\nPress Enter to return to Trip Management menu...", true);
    show(); // Show the menu again (recursive)
}

void TripMenu::viewAllTrips() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== VIEW ALL TRIPS ===\n");

    try
    {
        auto trips = _tripService->getAllTrips();
        if (trips.empty())
        {
            _outputFormatter->displayMessage("No trips found in the system.");
        }
        else
        {
            _tripView->displayAllTrips(trips);
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Failed to retrieve trips: ") + e.what());
    }
}

void TripMenu::findTrip() const
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== FIND TRIP ===\n");

    std::vector<std::string> searchOptions = {
        "Find by ID",
        "Find by Name",
        "Return to Trip Menu"};

    _outputFormatter->displayMenu("Search Options", searchOptions);
    int choice = _inputHandler->getIntInput("", 1, searchOptions.size());

    try
    {
        switch (choice)
        {
        case 1:
        { // Find by ID
            int id = _inputHandler->getIntInput("Enter trip ID: ", 1);
            auto tripOpt = _tripService->getTripById(id);
            if (tripOpt)
            {
                _tripView->displayTripDetails(*tripOpt);
            }
            else
            {
                _outputFormatter->displayMessage("No trip found with that ID.");
            }
            break;
        }
        case 2:
        { // Find by Name
            std::string name = _inputHandler->getStringInput("Enter trip name or destination (or part of it): ");
            auto trips = _tripService->findTripsByName(name);
            if (trips.empty())
            {
                _outputFormatter->displayMessage("No trips found matching the search criteria.");
            }
            else
            {
                _tripView->displayAllTrips(trips);
            }
            break;
        }
        case 3: // Return to Trip Menu
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

void TripMenu::addTrip()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== ADD NEW TRIP ===\n");

    try
    {        // Get trip information
        std::string name = _inputHandler->getStringInput("Enter trip name/destination: ");
        double cost = _inputHandler->getDoubleInput("Enter cost per person ($): ", 0.0);
        int availableSeats = _inputHandler->getIntInput("Enter available seats: ", 1);
        std::string startDate = _inputHandler->getDateInput("Enter start date");
        std::string endDate;
        
        // Ensure end date is greater than start date
        bool validEndDate = false;
        while (!validEndDate) {
            endDate = _inputHandler->getDateInput("Enter end date");
            
            // Compare dates (format: DD-MM-YYYY)
            if (isEndDateValid(startDate, endDate)) {
                validEndDate = true;
            } else {
                _outputFormatter->displayErrorMessage("End date must be after the start date. Please try again.");
            }
        }

        // Create a new Trip (ID will be set by the service)
        Trip newTrip(0, name, cost, availableSeats, startDate, endDate);

        // Add the trip to the system
        if (_tripService->addTrip(newTrip))
        {
            _outputFormatter->displaySuccessMessage("Trip added successfully!");
        }
        else
        {
            _outputFormatter->displayErrorMessage("Failed to add trip.");
        }
    }
    catch (const std::exception &e)    {
        _outputFormatter->displayErrorMessage(std::string("Error adding trip: ") + e.what());
    }
}

bool TripMenu::isEndDateValid(const std::string &startDate, const std::string &endDate)
{
    // Format: DD-MM-YYYY
    // Extract individual components
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;
    
    sscanf(startDate.c_str(), "%d-%d-%d", &startDay, &startMonth, &startYear);
    sscanf(endDate.c_str(), "%d-%d-%d", &endDay, &endMonth, &endYear);
    
    // Compare years first
    if (endYear > startYear) {
        return true;
    }
    else if (endYear < startYear) {
        return false;
    }
    
    // Same year, compare months
    if (endMonth > startMonth) {
        return true;
    }
    else if (endMonth < startMonth) {
        return false;
    }
    
    // Same year and month, compare days
    return endDay > startDay;
}

void TripMenu::editTrip()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== EDIT TRIP ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter the ID of the trip to edit: ", 1);
        auto tripOpt = _tripService->getTripById(id);

        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("No trip found with that ID.");
            return;
        }

        Trip trip = *tripOpt;
        _tripView->displayTripDetails(trip);

        // Get updated information
        _outputFormatter->displayMessage("\nEnter new information (leave empty to keep current value):");

        std::string name = _inputHandler->getStringInput("Name [" + trip.getName() + "]: ", true);
        if (!name.empty())
            trip.setName(name);

        std::string costStr = _inputHandler->getStringInput(
            "Cost per person [$" + std::to_string(trip.getCost()) + "]: ", true);
        if (!costStr.empty())
        {
            try
            {
                double cost = std::stod(costStr);
                if (cost >= 0)
                {
                    trip.setCost(cost);
                }
                else
                {
                    _outputFormatter->displayErrorMessage("Cost cannot be negative. Keeping original value.");
                }
            }
            catch (...)
            {
                _outputFormatter->displayErrorMessage("Invalid cost format. Keeping original value.");
            }
        }

        std::string seatsStr = _inputHandler->getStringInput(
            "Available seats [" + std::to_string(trip.getAvailableSeats()) + "]: ", true);
        if (!seatsStr.empty())
        {
            try
            {
                int seats = std::stoi(seatsStr);
                if (seats >= 0)
                {
                    trip.setAvailableSeats(seats);
                }
                else
                {
                    _outputFormatter->displayErrorMessage("Seats cannot be negative. Keeping original value.");
                }
            }
            catch (...)
            {
                _outputFormatter->displayErrorMessage("Invalid seats format. Keeping original value.");
            }
        }

        std::string startDate = _inputHandler->getStringInput(
            "Start date [" + trip.getStartDate() + "]: ", true);
        if (!startDate.empty())
        {
            if (_inputHandler->validateDate(startDate))
            {
                trip.setStartDate(startDate);
            }
            else
            {
                _outputFormatter->displayErrorMessage("Invalid date format. Keeping original value.");
            }
        }

        std::string endDate = _inputHandler->getStringInput(
            "End date [" + trip.getEndDate() + "]: ", true);
        if (!endDate.empty())
        {
            if (_inputHandler->validateDate(endDate))
            {
                trip.setEndDate(endDate);
            }
            else
            {
                _outputFormatter->displayErrorMessage("Invalid date format. Keeping original value.");
            }
        }

        // Update the trip
        if (_tripService->updateTrip(trip))
        {
            _outputFormatter->displaySuccessMessage("Trip information updated successfully!");
        }
        else
        {
            _outputFormatter->displayErrorMessage("Failed to update trip information.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error updating trip: ") + e.what());
    }
}

void TripMenu::deleteTrip()
{
    _outputFormatter->clearScreen();
    _outputFormatter->displayMessage("=== DELETE TRIP ===\n");

    try
    {
        int id = _inputHandler->getIntInput("Enter the ID of the trip to delete: ", 1);
        auto tripOpt = _tripService->getTripById(id);

        if (!tripOpt)
        {
            _outputFormatter->displayErrorMessage("No trip found with that ID.");
            return;
        }

        Trip trip = *tripOpt;
        _tripView->displayTripDetails(trip);        if (_inputHandler->getYesNoInput("Are you sure you want to delete this trip?"))
        {
            // Check if trip has bookings first
            if (_tripService->hasTripBookings(id))
            {
                _outputFormatter->displayErrorMessage("Cannot delete trip: There are bookings associated with this trip.");
            }
            else if (_tripService->deleteTrip(id))
            {
                _outputFormatter->displaySuccessMessage("Trip deleted successfully!");
            }
            else
            {
                _outputFormatter->displayErrorMessage("Failed to delete trip.");
            }
        }
        else
        {
            _outputFormatter->displayMessage("Trip deletion cancelled.");
        }
    }
    catch (const std::exception &e)
    {
        _outputFormatter->displayErrorMessage(std::string("Error deleting trip: ") + e.what());
    }
}