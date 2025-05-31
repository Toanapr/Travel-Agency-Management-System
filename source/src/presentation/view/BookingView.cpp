#include "BookingView.h"

BookingView::BookingView(std::shared_ptr<OutputFormatter> outputFormatter)
    : _outputFormatter(outputFormatter)
{
}

void BookingView::displayBookingDetails(const Booking &booking, const User &user, const Trip &trip) const
{
    _outputFormatter->displayBooking(booking, user, trip);
}

void BookingView::displayAllBookings(const std::vector<Booking> &bookings,
                                     const std::vector<User> &users,
                                     const std::vector<Trip> &trips) const
{
    _outputFormatter->displayBookings(bookings, users, trips);
}