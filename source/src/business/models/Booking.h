#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "User.h"
#include "Trip.h"

/**
 * @class Booking
 * @brief Represents a travel booking made by a user
 *
 * The Booking class stores information about a reservation made by a user
 * for a specific trip, including booking details like date, number of people,
 * and payment information.
 */
class Booking
{
private:
    int _id;                  ///< Unique identifier for the booking
    int _userId;              ///< ID of the user who made the booking
    int _tripId;              ///< ID of the trip being booked
    std::string _bookingDate; ///< Date when booking was made in YYYY-MM-DD format
    int _numberOfPeople;      ///< Number of people included in this booking
    double _totalCost;        ///< Total cost of the booking
    std::string _status;      ///< Current status (Confirmed, Pending, Cancelled)

public:
    /**
     * @brief Constructor for creating a new booking
     * @param id Unique identifier for the booking
     * @param userId ID of the user who made the booking
     * @param tripId ID of the trip being booked
     * @param bookingDate Date when booking was made in YYYY-MM-DD format
     * @param numberOfPeople Number of people included in this booking
     * @param totalCost Total cost of the booking
     * @param status Current status (Confirmed, Pending, Cancelled)
     */
    Booking(int id, int userId, int tripId, const std::string &bookingDate,
            int numberOfPeople, double totalCost, const std::string &status);

    // Getters
    /**
     * @brief Get the booking ID
     * @return The unique identifier for the booking
     */
    int getId() const;

    /**
     * @brief Get the user ID
     * @return The ID of the user who made the booking
     */
    int getUserId() const;

    /**
     * @brief Get the trip ID
     * @return The ID of the trip being booked
     */
    int getTripId() const;

    /**
     * @brief Get the booking date
     * @return The date when booking was made in YYYY-MM-DD format
     */
    std::string getBookingDate() const;

    /**
     * @brief Get the number of people
     * @return The number of people included in this booking
     */
    int getNumberOfPeople() const;

    /**
     * @brief Get the total cost
     * @return The total cost of the booking
     */
    double getTotalCost() const;

    /**
     * @brief Get the booking status
     * @return The current status (Confirmed, Pending, Cancelled)
     */
    std::string getStatus() const;

    // Setters
    /**
     * @brief Set the user ID
     * @param userId The new user ID for the booking
     */
    void setUserId(int userId);

    /**
     * @brief Set the trip ID
     * @param tripId The new trip ID for the booking
     */
    void setTripId(int tripId);

    /**
     * @brief Set the booking date
     * @param bookingDate The new booking date in YYYY-MM-DD format
     */
    void setBookingDate(const std::string &bookingDate);

    /**
     * @brief Set the number of people
     * @param numberOfPeople The new number of people for the booking
     */
    void setNumberOfPeople(int numberOfPeople);

    /**
     * @brief Set the total cost
     * @param totalCost The new total cost for the booking
     */
    void setTotalCost(double totalCost);

    /**
     * @brief Set the booking status
     * @param status The new status for the booking (Confirmed, Pending, Cancelled)
     */
    void setStatus(const std::string &status);
};

#endif // BOOKING_H