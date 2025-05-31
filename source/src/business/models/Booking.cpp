#include "Booking.h"
#include <stdexcept>

Booking::Booking(int id, int userId, int tripId, const std::string &bookingDate,
                 int numberOfPeople, double totalCost, const std::string &status)
    : _id(id), _userId(userId), _tripId(tripId), _bookingDate(bookingDate),
      _numberOfPeople(numberOfPeople), _totalCost(totalCost), _status(status)
{
    // Validation is performed before object creation
}

int Booking::getId() const
{
    return _id;
}

int Booking::getUserId() const
{
    return _userId;
}

int Booking::getTripId() const
{
    return _tripId;
}

std::string Booking::getBookingDate() const
{
    return _bookingDate;
}

int Booking::getNumberOfPeople() const
{
    return _numberOfPeople;
}

double Booking::getTotalCost() const
{
    return _totalCost;
}

std::string Booking::getStatus() const
{
    return _status;
}

void Booking::setId(int id)
{
    _id = id;
}

void Booking::setUserId(int userId)
{
    _userId = userId;
}

void Booking::setTripId(int tripId)
{
    _tripId = tripId;
}

void Booking::setBookingDate(const std::string &bookingDate)
{
    _bookingDate = bookingDate;
}

void Booking::setNumberOfPeople(int numberOfPeople)
{
    _numberOfPeople = numberOfPeople;
}

void Booking::setTotalCost(double totalCost)
{
    _totalCost = totalCost;
}

void Booking::setStatus(const std::string &status)
{
    _status = status;
}

bool Booking::operator==(const Booking &other) const
{
    return _id == other._id &&
           _userId == other._userId &&
           _tripId == other._tripId &&
           _bookingDate == other._bookingDate &&
           _numberOfPeople == other._numberOfPeople &&
           _totalCost == other._totalCost &&
           _status == other._status;
}