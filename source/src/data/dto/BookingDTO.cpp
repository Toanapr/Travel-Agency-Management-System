#include "BookingDTO.h"

BookingDTO::BookingDTO() : _id(0), _userId(0), _tripId(0), _bookingDate(""),
                           _numberOfPersons(0), _totalPrice(0.0), _status("")
{
}

BookingDTO::BookingDTO(int id, int userId, int tripId, const std::string &bookingDate,
                       int numberOfPersons, double totalPrice, const std::string &status)
    : _id(id), _userId(userId), _tripId(tripId), _bookingDate(bookingDate),
      _numberOfPersons(numberOfPersons), _totalPrice(totalPrice), _status(status)
{
}

int BookingDTO::getId() const
{
    return _id;
}

int BookingDTO::getUserId() const
{
    return _userId;
}

int BookingDTO::getTripId() const
{
    return _tripId;
}

const std::string &BookingDTO::getBookingDate() const
{
    return _bookingDate;
}

int BookingDTO::getNumberOfPersons() const
{
    return _numberOfPersons;
}

double BookingDTO::getTotalPrice() const
{
    return _totalPrice;
}

const std::string &BookingDTO::getStatus() const
{
    return _status;
}

void BookingDTO::setId(int id)
{
    _id = id;
}

void BookingDTO::setUserId(int userId)
{
    _userId = userId;
}

void BookingDTO::setTripId(int tripId)
{
    _tripId = tripId;
}

void BookingDTO::setBookingDate(const std::string &bookingDate)
{
    _bookingDate = bookingDate;
}

void BookingDTO::setNumberOfPersons(int numberOfPersons)
{
    _numberOfPersons = numberOfPersons;
}

void BookingDTO::setTotalPrice(double totalPrice)
{
    _totalPrice = totalPrice;
}

void BookingDTO::setStatus(const std::string &status)
{
    _status = status;
}