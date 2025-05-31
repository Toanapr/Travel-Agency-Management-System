#include "BookingRepository.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

BookingRepository::BookingRepository(std::shared_ptr<DatabaseConnection> dbConnection)
    : _dbConnection(dbConnection)
{
}

std::vector<Booking> BookingRepository::getAll()
{
    std::vector<Booking> bookings;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) != "id")
        {
            bookings.push_back(parseBookingFromCsv(line));
        }

        // Read all other lines
        while (std::getline(file, line))
        {
            bookings.push_back(parseBookingFromCsv(line));
        }

        file.close();
    }

    return bookings;
}

std::optional<Booking> BookingRepository::getById(int id)
{
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) == "id")
        {
            // It's a header, do nothing
        }
        else
        {
            // Check if the first line contains the booking
            Booking booking = parseBookingFromCsv(line);
            if (booking.getId() == id)
            {
                file.close();
                return booking;
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            Booking booking = parseBookingFromCsv(line);
            if (booking.getId() == id)
            {
                file.close();
                return booking;
            }
        }

        file.close();
    }

    return std::nullopt;
}

std::vector<Booking> BookingRepository::findByUserId(int userId)
{
    std::vector<Booking> bookings;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) == "id")
        {
            // It's a header, do nothing
        }
        else
        {
            // Check if the first line contains a booking with matching userId
            Booking booking = parseBookingFromCsv(line);
            if (booking.getUserId() == userId)
            {
                bookings.push_back(booking);
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            Booking booking = parseBookingFromCsv(line);
            if (booking.getUserId() == userId)
            {
                bookings.push_back(booking);
            }
        }

        file.close();
    }

    return bookings;
}

std::vector<Booking> BookingRepository::findByTripId(int tripId)
{
    std::vector<Booking> bookings;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) == "id")
        {
            // It's a header, do nothing
        }
        else
        {
            // Check if the first line contains a booking with matching tripId
            Booking booking = parseBookingFromCsv(line);
            if (booking.getTripId() == tripId)
            {
                bookings.push_back(booking);
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            Booking booking = parseBookingFromCsv(line);
            if (booking.getTripId() == tripId)
            {
                bookings.push_back(booking);
            }
        }

        file.close();
    }

    return bookings;
}

bool BookingRepository::add(const Booking &booking)
{
    // Generate a new ID for the booking (max ID + 1)
    int newId = getNextId();

    // Create a copy of the booking with the new ID
    Booking newBooking = booking;
    newBooking.setId(newId);

    // Open the file for appending
    std::ofstream file = _dbConnection->openFileForWriting(_filename, true);

    if (file.is_open())
    {
        // Only add the data (no header)
        file << convertBookingToCsv(newBooking) << std::endl;
        file.close();
        return true;
    }

    return false;
}

bool BookingRepository::update(const Booking &booking)
{
    std::vector<Booking> bookings = getAll();
    bool found = false;

    for (auto &existingBooking : bookings)
    {
        if (existingBooking.getId() == booking.getId())
        {
            existingBooking = booking;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return false;
    }

    // Rewrite the entire file
    std::ofstream file = _dbConnection->openFileForWriting(_filename, false);

    if (file.is_open())
    {
        // Add header
        file << "id,userId,tripId,bookingDate,numberOfPeople,totalCost,status" << std::endl;

        // Add all bookings
        for (const auto &b : bookings)
        {
            file << convertBookingToCsv(b) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

bool BookingRepository::remove(int id)
{
    std::vector<Booking> bookings = getAll();
    auto it = std::find_if(bookings.begin(), bookings.end(),
                           [id](const Booking &booking)
                           { return booking.getId() == id; });

    if (it == bookings.end())
    {
        return false;
    }

    bookings.erase(it);

    // Rewrite the entire file
    std::ofstream file = _dbConnection->openFileForWriting(_filename, false);

    if (file.is_open())
    {
        // Add header
        file << "id,userId,tripId,bookingDate,numberOfPeople,totalCost,status" << std::endl;

        // Add all remaining bookings
        for (const auto &booking : bookings)
        {
            file << convertBookingToCsv(booking) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

int BookingRepository::getNextId()
{
    std::vector<Booking> bookings = getAll();

    if (bookings.empty())
    {
        return 1;
    }

    int maxId = 0;
    for (const auto &booking : bookings)
    {
        if (booking.getId() > maxId)
        {
            maxId = booking.getId();
        }
    }

    return maxId + 1;
}

Booking BookingRepository::parseBookingFromCsv(const std::string &line)
{
    std::stringstream ss(line);
    std::string idStr, userIdStr, tripIdStr, bookingDate, numberOfPeopleStr, totalCostStr, status;

    // Parse CSV format: id,userId,tripId,bookingDate,numberOfPeople,totalCost,status
    std::getline(ss, idStr, ',');
    std::getline(ss, userIdStr, ',');
    std::getline(ss, tripIdStr, ',');
    std::getline(ss, bookingDate, ',');
    std::getline(ss, numberOfPeopleStr, ',');
    std::getline(ss, totalCostStr, ',');
    std::getline(ss, status);

    int id = std::stoi(idStr);
    int userId = std::stoi(userIdStr);
    int tripId = std::stoi(tripIdStr);
    int numberOfPeople = std::stoi(numberOfPeopleStr);
    double totalCost = std::stod(totalCostStr);

    return Booking(id, userId, tripId, bookingDate, numberOfPeople, totalCost, status);
}

std::string BookingRepository::convertBookingToCsv(const Booking &booking)
{
    return std::to_string(booking.getId()) + "," +
           std::to_string(booking.getUserId()) + "," +
           std::to_string(booking.getTripId()) + "," +
           booking.getBookingDate() + "," +
           std::to_string(booking.getNumberOfPeople()) + "," +
           std::to_string(booking.getTotalCost()) + "," +
           booking.getStatus();
}