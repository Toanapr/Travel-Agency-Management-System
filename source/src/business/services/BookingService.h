#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include <memory>
#include <vector>
#include <optional>
#include <string>
#include "../interfaces/IBookingRepository.h"
#include "../interfaces/IUserRepository.h"
#include "../interfaces/ITripRepository.h"
#include "../models/Booking.h"
#include "../models/User.h"
#include "../models/Trip.h"

/**
 * @class BookingService
 * @brief Service class for booking-related business logic
 *
 * This class handles all business logic related to bookings, including
 * creating, updating, and canceling bookings. It acts as an intermediary
 * between the presentation layer and the data access layer.
 */
class BookingService
{
private:
    std::shared_ptr<IBookingRepository> _bookingRepository; ///< Repository for booking data access
    std::shared_ptr<IUserRepository> _userRepository;       ///< Repository for user data access
    std::shared_ptr<ITripRepository> _tripRepository;       ///< Repository for trip data access

public:
    /**
     * @brief Constructor for BookingService
     * @param bookingRepository Repository implementation for booking data access
     * @param userRepository Repository implementation for user data access
     * @param tripRepository Repository implementation for trip data access
     */
    BookingService(std::shared_ptr<IBookingRepository> bookingRepository,
                   std::shared_ptr<IUserRepository> userRepository,
                   std::shared_ptr<ITripRepository> tripRepository);

    // Booking management methods
    /**
     * @brief Get all bookings in the system
     * @return Vector of all Booking objects
     */
    std::vector<Booking> getAllBookings();

    /**
     * @brief Find a booking by its ID
     * @param id The unique identifier of the booking
     * @return Optional containing the booking if found, empty otherwise
     */
    std::optional<Booking> getBookingById(int id);

    /**
     * @brief Find all bookings for a specific user
     * @param userId The unique identifier of the user
     * @return Vector of bookings made by the specified user
     */
    std::vector<Booking> findBookingsByUserId(int userId);

    /**
     * @brief Find all bookings for a specific trip
     * @param tripId The unique identifier of the trip
     * @return Vector of bookings for the specified trip
     */
    std::vector<Booking> findBookingsByTripId(int tripId);

    /**
     * @brief Create a new booking
     * @param userId The unique identifier of the user making the booking
     * @param tripId The unique identifier of the trip being booked
     * @param bookingDate The date of the booking in YYYY-MM-DD format
     * @param numberOfPeople The number of people included in this booking
     * @return true if the booking was successfully created, false otherwise
     */
    bool createBooking(int userId, int tripId, const std::string &bookingDate,
                       int numberOfPeople);

    /**
     * @brief Update the status of an existing booking
     * @param bookingId The unique identifier of the booking
     * @param status The new status for the booking (Confirmed, Pending, Cancelled)
     * @return true if the status was successfully updated, false otherwise
     */
    bool updateBookingStatus(int bookingId, const std::string &status);

    /**
     * @brief Cancel an existing booking
     * @param bookingId The unique identifier of the booking to cancel
     * @return true if the booking was successfully cancelled, false otherwise
     */
    bool cancelBooking(int bookingId);

    // Business logic
    /**
     * @brief Calculate the total cost for a booking
     * @param tripId The unique identifier of the trip
     * @param numberOfPeople The number of people in the booking
     * @return The total cost (trip cost * number of people)
     */
    double calculateTotalCost(int tripId, int numberOfPeople);

    /**
     * @brief Validate a booking request
     * @param userId The unique identifier of the user
     * @param tripId The unique identifier of the trip
     * @param numberOfPeople The number of people in the booking
     * @return true if the booking request is valid, false otherwise
     */
    bool validateBooking(int userId, int tripId, int numberOfPeople);
};

#endif // BOOKING_SERVICE_H