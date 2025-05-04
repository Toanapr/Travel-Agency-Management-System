#include "BookingService.h"
#include <chrono>
#include <iomanip>
#include <sstream>

BookingService::BookingService(std::shared_ptr<IBookingRepository> bookingRepository,
                               std::shared_ptr<IUserRepository> userRepository,
                               std::shared_ptr<ITripRepository> tripRepository)
    : _bookingRepository(bookingRepository),
      _userRepository(userRepository),
      _tripRepository(tripRepository)
{
}

std::vector<Booking> BookingService::getAllBookings()
{
    return _bookingRepository->getAll();
}

std::optional<Booking> BookingService::getBookingById(int id)
{
    return _bookingRepository->getById(id);
}

std::vector<Booking> BookingService::findBookingsByUserId(int userId)
{
    return _bookingRepository->findByUserId(userId);
}

std::vector<Booking> BookingService::findBookingsByTripId(int tripId)
{
    return _bookingRepository->findByTripId(tripId);
}

bool BookingService::createBooking(int userId, int tripId, const std::string &bookingDate,
                                   int numberOfPeople)
{
    // Validate booking
    if (!validateBooking(userId, tripId, numberOfPeople))
    {
        return false;
    }

    // Calculate total cost
    double totalCost = calculateTotalCost(tripId, numberOfPeople);

    // Create booking
    int nextId = 1;
    auto allBookings = _bookingRepository->getAll();
    if (!allBookings.empty())
    {
        nextId = allBookings.back().getId() + 1;
    }

    Booking booking(nextId, userId, tripId, bookingDate, numberOfPeople, totalCost, "Confirmed");

    // Add booking to repository
    bool success = _bookingRepository->add(booking);

    // Update available seats for the trip
    if (success)
    {
        auto tripOpt = _tripRepository->getById(tripId);
        if (tripOpt)
        {
            Trip trip = *tripOpt;
            int newAvailableSeats = trip.getAvailableSeats() - numberOfPeople;
            if (newAvailableSeats >= 0)
            {
                trip.setAvailableSeats(newAvailableSeats);
                _tripRepository->update(trip);
            }
        }
    }

    return success;
}

bool BookingService::updateBookingStatus(int bookingId, const std::string &status)
{
    auto bookingOpt = _bookingRepository->getById(bookingId);
    if (!bookingOpt)
    {
        return false;
    }

    Booking booking = *bookingOpt;
    booking.setStatus(status);

    return _bookingRepository->update(booking);
}

bool BookingService::cancelBooking(int bookingId)
{
    auto bookingOpt = _bookingRepository->getById(bookingId);
    if (!bookingOpt)
    {
        return false;
    }

    Booking booking = *bookingOpt;

    // Return seats to trip inventory
    auto tripOpt = _tripRepository->getById(booking.getTripId());
    if (tripOpt && booking.getStatus() != "Cancelled")
    {
        Trip trip = *tripOpt;
        int newAvailableSeats = trip.getAvailableSeats() + booking.getNumberOfPeople();
        trip.setAvailableSeats(newAvailableSeats);
        _tripRepository->update(trip);
    }

    // Update booking status to cancelled
    booking.setStatus("Cancelled");
    return _bookingRepository->update(booking);
}

double BookingService::calculateTotalCost(int tripId, int numberOfPeople)
{
    auto tripOpt = _tripRepository->getById(tripId);
    if (!tripOpt)
    {
        return 0.0;
    }

    return tripOpt->getCost() * numberOfPeople;
}

bool BookingService::validateBooking(int userId, int tripId, int numberOfPeople)
{
    // Check if user exists
    auto userOpt = _userRepository->getById(userId);
    if (!userOpt)
    {
        return false;
    }

    // Check if trip exists
    auto tripOpt = _tripRepository->getById(tripId);
    if (!tripOpt)
    {
        return false;
    }

    // Check if enough seats are available
    if (tripOpt->getAvailableSeats() < numberOfPeople)
    {
        return false;
    }

    return true;
}