#ifndef BOOKING_VIEW_H
#define BOOKING_VIEW_H

#include <memory>
#include <vector>
#include "../../business/models/Booking.h"
#include "../../business/models/User.h"
#include "../../business/models/Trip.h"
#include "../console/OutputFormatter.h"

/**
 * @class BookingView
 * @brief View class for displaying Booking-related information
 *
 * This class is responsible for presenting Booking objects in various formats.
 * It uses the OutputFormatter to handle the actual display operations.
 */
class BookingView
{
private:
    std::shared_ptr<OutputFormatter> _outputFormatter;

public:
    /**
     * @brief Constructor
     * @param outputFormatter Shared pointer to the OutputFormatter
     */
    explicit BookingView(std::shared_ptr<OutputFormatter> outputFormatter);

    /**
     * @brief Display detailed information for a single booking
     * @param booking The booking to display
     * @param user The user associated with the booking
     * @param trip The trip associated with the booking
     */
    void displayBookingDetails(const Booking &booking, const User &user, const Trip &trip) const;

    /**
     * @brief Display a list of bookings in a tabular format
     * @param bookings Vector of bookings to display
     * @param users Vector of users for lookup
     * @param trips Vector of trips for lookup
     */
    void displayAllBookings(const std::vector<Booking> &bookings,
                            const std::vector<User> &users,
                            const std::vector<Trip> &trips) const;
};

#endif // BOOKING_VIEW_H