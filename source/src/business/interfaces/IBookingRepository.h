#ifndef IBOOKING_REPOSITORY_H
#define IBOOKING_REPOSITORY_H

#include <vector>
#include <optional>
#include "../models/Booking.h"

/**
 * @interface IBookingRepository
 * @brief Interface for booking data persistence operations
 *
 * This interface defines the contract for classes that handle
 * the persistence of Booking objects in the data store. It follows
 * the Repository pattern to abstract data access logic.
 */
class IBookingRepository
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IBookingRepository() = default;

    /**
     * @brief Retrieve all bookings from the data store
     * @return Vector containing all bookings
     */
    virtual std::vector<Booking> getAll() = 0;

    /**
     * @brief Find a booking by its ID
     * @param id The unique identifier of the booking to find
     * @return Optional containing the booking if found, empty otherwise
     */
    virtual std::optional<Booking> getById(int id) = 0;

    /**
     * @brief Find all bookings for a specific user
     * @param userId The unique identifier of the user
     * @return Vector of bookings made by the specified user
     */
    virtual std::vector<Booking> findByUserId(int userId) = 0;

    /**
     * @brief Find all bookings for a specific trip
     * @param tripId The unique identifier of the trip
     * @return Vector of bookings for the specified trip
     */
    virtual std::vector<Booking> findByTripId(int tripId) = 0;

    /**
     * @brief Add a new booking to the data store
     * @param booking The booking object to add
     * @return true if the operation was successful, false otherwise
     */
    virtual bool add(const Booking &booking) = 0;

    /**
     * @brief Update an existing booking in the data store
     * @param booking The booking object with updated information
     * @return true if the operation was successful, false otherwise
     */
    virtual bool update(const Booking &booking) = 0;

    /**
     * @brief Remove a booking from the data store
     * @param id The unique identifier of the booking to remove
     * @return true if the operation was successful, false otherwise
     */
    virtual bool remove(int id) = 0;
};

#endif // IBOOKING_REPOSITORY_H