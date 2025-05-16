#include "TripRepository.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

TripRepository::TripRepository(std::shared_ptr<DatabaseConnection> dbConnection)
    : _dbConnection(dbConnection)
{
}

std::vector<Trip> TripRepository::getAll()
{
    std::vector<Trip> trips;
    std::ifstream file = _dbConnection->openFileForReading(_filename);

    if (file.is_open())
    {
        std::string line;

        // Skip header line if exists
        if (std::getline(file, line) && line.substr(0, 2) != "id")
        {
            trips.push_back(parseTripFromCsv(line));
        }

        // Read all other lines
        while (std::getline(file, line))
        {
            trips.push_back(parseTripFromCsv(line));
        }

        file.close();
    }

    return trips;
}

std::optional<Trip> TripRepository::getById(int id)
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
            // Check if the first line contains the trip
            Trip trip = parseTripFromCsv(line);
            if (trip.getId() == id)
            {
                file.close();
                return trip;
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            Trip trip = parseTripFromCsv(line);
            if (trip.getId() == id)
            {
                file.close();
                return trip;
            }
        }

        file.close();
    }

    return std::nullopt;
}

std::vector<Trip> TripRepository::findByName(const std::string &name)
{
    std::vector<Trip> trips;
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
            // Check if the first line contains the trip with matching name
            Trip trip = parseTripFromCsv(line);
            std::string tripName = trip.getName();
            std::transform(tripName.begin(), tripName.end(), tripName.begin(), ::tolower);

            std::string searchName = name;
            std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

            if (tripName.find(searchName) != std::string::npos)
            {
                trips.push_back(trip);
            }
        }

        // Check all other lines
        while (std::getline(file, line))
        {
            Trip trip = parseTripFromCsv(line);
            std::string tripName = trip.getName();
            std::transform(tripName.begin(), tripName.end(), tripName.begin(), ::tolower);

            std::string searchName = name;
            std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

            if (tripName.find(searchName) != std::string::npos)
            {
                trips.push_back(trip);
            }
        }

        file.close();
    }

    return trips;
}

bool TripRepository::add(const Trip &trip)
{
    // Generate a new ID for the trip (max ID + 1)
    int newId = getNextId();

    // Create a copy of the trip with the new ID
    Trip newTrip = trip;
    newTrip.setId(newId);

    // Open the file for appending
    std::ofstream file = _dbConnection->openFileForWriting(_filename, true);

    if (file.is_open())
    {
        // Only add the data (no header)
        file << convertTripToCsv(newTrip) << std::endl;
        file.close();
        return true;
    }

    return false;
}

bool TripRepository::update(const Trip &trip)
{
    std::vector<Trip> trips = getAll();
    bool found = false;

    for (auto &existingTrip : trips)
    {
        if (existingTrip.getId() == trip.getId())
        {
            existingTrip = trip;
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
        file << "id,name,cost,availableSeats,startDate,endDate" << std::endl;

        // Add all trips
        for (const auto &t : trips)
        {
            file << convertTripToCsv(t) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

bool TripRepository::remove(int id)
{
    std::vector<Trip> trips = getAll();
    auto it = std::find_if(trips.begin(), trips.end(),
                           [id](const Trip &trip)
                           { return trip.getId() == id; });

    if (it == trips.end())
    {
        return false;
    }

    trips.erase(it);

    // Rewrite the entire file
    std::ofstream file = _dbConnection->openFileForWriting(_filename, false);

    if (file.is_open())
    {
        // Add header
        file << "id,name,cost,availableSeats,startDate,endDate" << std::endl;

        // Add all remaining trips
        for (const auto &trip : trips)
        {
            file << convertTripToCsv(trip) << std::endl;
        }

        file.close();
        return true;
    }

    return false;
}

int TripRepository::getNextId()
{
    std::vector<Trip> trips = getAll();

    if (trips.empty())
    {
        return 1;
    }

    int maxId = 0;
    for (const auto &trip : trips)
    {
        if (trip.getId() > maxId)
        {
            maxId = trip.getId();
        }
    }

    return maxId + 1;
}

Trip TripRepository::parseTripFromCsv(const std::string &line)
{
    std::stringstream ss(line);
    std::string idStr, name, costStr, availableSeatsStr, startDate, endDate;

    // Parse CSV format: id,name,cost,availableSeats,startDate,endDate
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, costStr, ',');
    std::getline(ss, availableSeatsStr, ',');
    std::getline(ss, startDate, ',');
    std::getline(ss, endDate);

    int id = std::stoi(idStr);
    double cost = std::stod(costStr);
    int availableSeats = std::stoi(availableSeatsStr);

    return Trip(id, name, cost, availableSeats, startDate, endDate);
}

std::string TripRepository::convertTripToCsv(const Trip &trip)
{
    return std::to_string(trip.getId()) + "," +
           trip.getName() + "," +
           std::to_string(trip.getCost()) + "," +
           std::to_string(trip.getAvailableSeats()) + "," +
           trip.getStartDate() + "," +
           trip.getEndDate();
}