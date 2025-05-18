#ifndef TRIP_MENU_H
#define TRIP_MENU_H

#include <memory>
#include <string>
#include <vector>
#include "../console/InputHandler.h"
#include "../console/OutputFormatter.h"
#include "../../business/services/TripService.h"
#include "../view/TripView.h"

/**
 * @class TripMenu
 * @brief Handles the trip management menu functionality
 *
 * This class manages the menu for trip operations including viewing available trips,
 * finding trips, adding, editing, and deleting trips.
 */
class TripMenu
{
private:
    std::shared_ptr<InputHandler> _inputHandler;
    std::shared_ptr<OutputFormatter> _outputFormatter;
    std::shared_ptr<TripService> _tripService;
    std::shared_ptr<TripView> _tripView;

    // Menu options
    std::vector<std::string> _menuOptions = {
        "View All Trips",
        "Find Trip",
        "Add New Trip",
        "Edit Trip",
        "Delete Trip",
        "Return to Main Menu"};

    /**
     * @brief Process trip's menu choice
     * @param choice The option selected by the user
     */
    void processMenuChoice(int choice);

    /**
     * @brief Display all trips in the system
     */
    void viewAllTrips() const;

    /**
     * @brief Find a trip by ID or name
     */
    void findTrip() const;

    /**
     * @brief Add a new trip to the system
     */
    void addTrip();

    /**
     * @brief Edit an existing trip
     */
    void editTrip();    /**
     * @brief Delete a trip from the system
     */
    void deleteTrip();

    /**
     * @brief Check if the end date is valid (after the start date)
     * @param startDate Trip start date in DD-MM-YYYY format
     * @param endDate Trip end date in DD-MM-YYYY format
     * @return true if end date is after start date, false otherwise
     */
    bool isEndDateValid(const std::string &startDate, const std::string &endDate);

public:
    /**
     * @brief Constructor for TripMenu
     * @param inputHandler Shared pointer to InputHandler for user input
     * @param outputFormatter Shared pointer to OutputFormatter for display
     * @param tripService Shared pointer to TripService for business logic
     * @param tripView Shared pointer to TripView for presentation
     */
    TripMenu(std::shared_ptr<InputHandler> inputHandler,
             std::shared_ptr<OutputFormatter> outputFormatter,
             std::shared_ptr<TripService> tripService,
             std::shared_ptr<TripView> tripView);

    /**
     * @brief Display the trip management menu and process selection
     */
    void show();
};

#endif // TRIP_MENU_H