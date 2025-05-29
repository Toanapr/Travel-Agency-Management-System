#include "TripService.h"
#include "BookingService.h"
#include <algorithm>
#include <iterator>

TripService::TripService(std::shared_ptr<ITripRepository> tripRepository, std::shared_ptr<BookingService> bookingService)
    : _tripRepository(tripRepository), _bookingService(bookingService)
{
}

std::vector<Trip> TripService::getAllTrips()
{
    return _tripRepository->getAll();
}

std::optional<Trip> TripService::getTripById(int id)
{
    return _tripRepository->getById(id);
}

std::vector<Trip> TripService::findTripsByName(const std::string &name)
{
    return _tripRepository->findByName(name);
}

bool TripService::addTrip(const Trip &trip)
{
    return _tripRepository->add(trip);
}

bool TripService::updateTrip(const Trip &trip)
{
    return _tripRepository->update(trip);
}

bool TripService::deleteTrip(int id)
{
    // Check if there are any bookings for this trip
    if (_bookingService && hasTripBookings(id))
    {
        // Can't delete a trip that has bookings
        return false;
    }
    return _tripRepository->remove(id);
}

bool TripService::hasTripBookings(int tripId)
{
    if (!_bookingService)
    {
        return false;
    }
    
    auto bookings = _bookingService->findBookingsByTripId(tripId);
    return !bookings.empty();
}

std::vector<Trip> TripService::searchTripsByCriteria(const std::string &destination,
                                                     double maxPrice,
                                                     const std::string &startDate,
                                                     const std::string &endDate)
{
    auto allTrips = _tripRepository->getAll();
    std::vector<Trip> filteredTrips;

    // Filter trips based on criteria
    std::copy_if(allTrips.begin(), allTrips.end(), std::back_inserter(filteredTrips),
                 [&](const Trip &trip)
                 {
                     bool match = true;

                     // Filter by destination if specified
                     if (!destination.empty())
                     {
                         std::string tripName = trip.getName();
                         std::transform(tripName.begin(), tripName.end(), tripName.begin(), ::tolower);

                         std::string searchDest = destination;
                         std::transform(searchDest.begin(), searchDest.end(), searchDest.begin(), ::tolower);

                         if (tripName.find(searchDest) == std::string::npos)
                         {
                             match = false;
                         }
                     }

                     // Filter by price if specified
                     if (maxPrice > 0 && trip.getCost() > maxPrice)
                     {
                         match = false;
                     }

                     // Filter by start date if specified
                     if (!startDate.empty() && trip.getStartDate() < startDate)
                     {
                         match = false;
                     }

                     // Filter by end date if specified
                     if (!endDate.empty() && trip.getEndDate() > endDate)
                     {
                         match = false;
                     }

                     return match;
                 });

    return filteredTrips;
}

bool TripService::isAvailable(int tripId, int requestedSeats)
{
    auto tripOpt = _tripRepository->getById(tripId);

    if (!tripOpt)
    {
        return false;
    }

    return tripOpt->getAvailableSeats() >= requestedSeats;
}

void TripService::updateAvailableSeats(int tripId, int bookedSeats)
{
    auto tripOpt = _tripRepository->getById(tripId);

    if (tripOpt)
    {
        Trip trip = *tripOpt;
        int newAvailableSeats = trip.getAvailableSeats() - bookedSeats;

        // Ensure we don't go negative
        if (newAvailableSeats < 0)
        {
            newAvailableSeats = 0;
        }

        trip.setAvailableSeats(newAvailableSeats);
        _tripRepository->update(trip);
    }
}