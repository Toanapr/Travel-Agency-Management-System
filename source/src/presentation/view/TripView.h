#ifndef TRIP_VIEW_H
#define TRIP_VIEW_H

#include <memory>
#include <vector>
#include "../../business/models/Trip.h"
#include "../console/OutputFormatter.h"

/**
 * @class TripView
 * @brief View class for displaying Trip-related information
 *
 * This class is responsible for presenting Trip objects in various formats.
 * It uses the OutputFormatter to handle the actual display operations.
 */
class TripView
{
private:
    std::shared_ptr<OutputFormatter> _outputFormatter;

public:
    /**
     * @brief Constructor
     * @param outputFormatter Shared pointer to the OutputFormatter
     */
    explicit TripView(std::shared_ptr<OutputFormatter> outputFormatter);

    /**
     * @brief Display detailed information for a single trip
     * @param trip The trip to display
     */
    void displayTripDetails(const Trip &trip) const;

    /**
     * @brief Display a list of trips in a tabular format
     * @param trips Vector of trips to display
     */
    void displayAllTrips(const std::vector<Trip> &trips) const;
};

#endif // TRIP_VIEW_H