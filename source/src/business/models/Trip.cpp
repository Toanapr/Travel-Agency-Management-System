#include "Trip.h"
#include <stdexcept>

Trip::Trip(int id, const std::string &name, double cost, int availableSeats,
           const std::string &startDate, const std::string &endDate)
    : _id(id), _name(name), _cost(cost), _availableSeats(availableSeats),
      _startDate(startDate), _endDate(endDate)
{
    // Validation is performed before object creation
}

int Trip::getId() const
{
    return _id;
}

std::string Trip::getName() const
{
    return _name;
}

double Trip::getCost() const
{
    return _cost;
}

int Trip::getAvailableSeats() const
{
    return _availableSeats;
}

std::string Trip::getStartDate() const
{
    return _startDate;
}

std::string Trip::getEndDate() const
{
    return _endDate;
}

void Trip::setId(int id)
{
    _id = id;
}

void Trip::setName(const std::string &name)
{
    _name = name;
}

void Trip::setCost(double cost)
{
    _cost = cost;
}

void Trip::setAvailableSeats(int availableSeats)
{
    _availableSeats = availableSeats;
}

void Trip::setStartDate(const std::string &startDate)
{
    _startDate = startDate;
}

void Trip::setEndDate(const std::string &endDate)
{
    _endDate = endDate;
}

bool Trip::operator==(const Trip &other) const
{
    return _id == other._id &&
           _name == other._name &&
           _cost == other._cost &&
           _availableSeats == other._availableSeats &&
           _startDate == other._startDate &&
           _endDate == other._endDate;
}