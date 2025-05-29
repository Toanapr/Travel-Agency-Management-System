#ifndef TRIP_SERVICE_H
#define TRIP_SERVICE_H

#include <memory>
#include <vector>
#include <optional>
#include <string>
#include "../interfaces/ITripRepository.h"
#include "../models/Trip.h"

// Forward declaration to avoid circular dependency
class BookingService;

/**
 * @class TripService
 * @brief Service class for trip-related business logic
 *
 * This class handles all business logic related to trips, including
 * trip management, searching, and availability checking. It acts as an intermediary
 * between the presentation layer and the data access layer.
 */
class TripService
{
private:
    std::shared_ptr<ITripRepository> _tripRepository; ///< Repository for trip data access
    std::shared_ptr<BookingService> _bookingService;  ///< Service for booking operations

public:
    /**
     * @brief Constructor for TripService
     * @param tripRepository Repository implementation for trip data access
     * @param bookingService Service for booking operations
     */
    TripService(std::shared_ptr<ITripRepository> tripRepository, 
               std::shared_ptr<BookingService> bookingService = nullptr);

    // Trip management methods
    /**
     * @brief Get all trips in the system
     * @return Vector of all Trip objects
     */
    std::vector<Trip> getAllTrips();

    /**
     * @brief Find a trip by its ID
     * @param id The unique identifier of the trip
     * @return Optional containing the trip if found, empty otherwise
     */
    std::optional<Trip> getTripById(int id);

    /**
     * @brief Search for trips by name (partial match)
     * @param name Name or partial name to search for
     * @return Vector of trips whose names match the search criteria
     */
    std::vector<Trip> findTripsByName(const std::string &name);

    /**
     * @brief Add a new trip to the system
     * @param trip The trip object to add
     * @return true if successfully added, false otherwise
     */
    bool addTrip(const Trip &trip);

    /**
     * @brief Update an existing trip's information
     * @param trip The trip object with updated information
     * @return true if successfully updated, false otherwise
     */
    bool updateTrip(const Trip &trip);    /**
     * @brief Delete a trip from the system
     * @param id The unique identifier of the trip to delete
     * @return true if successfully deleted, false otherwise
     *         Returns false if the trip is referenced in any bookings
     */
    bool deleteTrip(int id);
    
    /**
     * @brief Check if a trip has any associated bookings
     * @param tripId The unique identifier of the trip
     * @return true if bookings exist for this trip, false otherwise
     */
    bool hasTripBookings(int tripId);

    // Additional business logic
    /**
     * @brief Search for trips based on multiple criteria
     * @param destination Destination name (partial match)
     * @param maxPrice Maximum price per person
     * @param startDate Earliest start date (YYYY-MM-DD format)
     * @param endDate Latest end date (YYYY-MM-DD format)
     * @return Vector of trips that match the search criteria
     */
    std::vector<Trip> searchTripsByCriteria(const std::string &destination, double maxPrice,
                                            const std::string &startDate, const std::string &endDate);

    /**
     * @brief Check if a trip has enough available seats
     * @param tripId The unique identifier of the trip
     * @param requestedSeats Number of seats needed
     * @return true if enough seats are available, false otherwise
     */
    bool isAvailable(int tripId, int requestedSeats);

    /**
     * @brief Update the number of available seats for a trip
     * @param tripId The unique identifier of the trip
     * @param bookedSeats Number of seats to be booked (reduces available seats)
     */
    void updateAvailableSeats(int tripId, int bookedSeats);
};

#endif // TRIP_SERVICE_H