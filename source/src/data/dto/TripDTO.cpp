#include "TripDTO.h"

TripDTO::TripDTO() : _id(0), _name(""), _destination(""), _startDate(""),
                     _endDate(""), _price(0.0), _capacity(0), _description("")
{
}

TripDTO::TripDTO(int id, const std::string &name, const std::string &destination,
                 const std::string &startDate, const std::string &endDate,
                 double price, int capacity, const std::string &description)
    : _id(id), _name(name), _destination(destination), _startDate(startDate),
      _endDate(endDate), _price(price), _capacity(capacity), _description(description)
{
}

int TripDTO::getId() const
{
    return _id;
}

const std::string &TripDTO::getName() const
{
    return _name;
}

const std::string &TripDTO::getDestination() const
{
    return _destination;
}

const std::string &TripDTO::getStartDate() const
{
    return _startDate;
}

const std::string &TripDTO::getEndDate() const
{
    return _endDate;
}

double TripDTO::getPrice() const
{
    return _price;
}

int TripDTO::getCapacity() const
{
    return _capacity;
}

const std::string &TripDTO::getDescription() const
{
    return _description;
}

void TripDTO::setId(int id)
{
    _id = id;
}

void TripDTO::setName(const std::string &name)
{
    _name = name;
}

void TripDTO::setDestination(const std::string &destination)
{
    _destination = destination;
}

void TripDTO::setStartDate(const std::string &startDate)
{
    _startDate = startDate;
}

void TripDTO::setEndDate(const std::string &endDate)
{
    _endDate = endDate;
}

void TripDTO::setPrice(double price)
{
    _price = price;
}

void TripDTO::setCapacity(int capacity)
{
    _capacity = capacity;
}

void TripDTO::setDescription(const std::string &description)
{
    _description = description;
}