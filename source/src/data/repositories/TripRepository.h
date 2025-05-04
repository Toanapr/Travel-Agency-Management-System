#ifndef TRIP_REPOSITORY_H
#define TRIP_REPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include "../../business/interfaces/ITripRepository.h"
#include "../../business/models/Trip.h"
#include "../database/DatabaseConnection.h"

/**
 * @class TripRepository
 * @brief Implementation of ITripRepository for CSV file storage
 *
 * This class provides an implementation of the ITripRepository interface
 * that uses CSV files for persistent storage of trip data. It handles all
 * CRUD operations for Trip objects, translating between object and CSV formats.
 */
class TripRepository : public ITripRepository
{
private:
    std::shared_ptr<DatabaseConnection> _dbConnection; ///< Database connection for file access
    const std::string _filename = "trips.csv";         ///< Name of the CSV file for trip data storage

    /**
     * @brief Convert a CSV line to a Trip object
     * @param line CSV-formatted string containing trip data
     * @return Trip object created from the CSV data
     */
    Trip parseTripFromCsv(const std::string &line);

    /**
     * @brief Convert a Trip object to CSV format
     * @param trip Trip object to convert
     * @return CSV-formatted string representing the trip
     */
    std::string convertTripToCsv(const Trip &trip);

    /**
     * @brief Generate the next available ID for a new trip
     * @return Next available unique identifier
     */
    int getNextId();

public:
    /**
     * @brief Constructor for TripRepository
     * @param dbConnection Shared pointer to DatabaseConnection for file operations
     */
    TripRepository(std::shared_ptr<DatabaseConnection> dbConnection);

    // ITripRepository implementation
    /**
     * @brief Retrieve all trips from storage
     * @return Vector of all Trip objects
     */
    std::vector<Trip> getAll() override;

    /**
     * @brief Find a trip by its ID
     * @param id The unique identifier of the trip to find
     * @return Optional containing the trip if found, empty otherwise
     */
    std::optional<Trip> getById(int id) override;

    /**
     * @brief Find trips by name (partial match)
     * @param name The name or part of the name to search for
     * @return Vector of trips whose names match the search criteria
     */
    std::vector<Trip> findByName(const std::string &name) override;

    /**
     * @brief Add a new trip to storage
     * @param trip The trip object to add
     * @return true if the operation was successful, false otherwise
     */
    bool add(const Trip &trip) override;

    /**
     * @brief Update an existing trip in storage
     * @param trip The trip object with updated information
     * @return true if the operation was successful, false otherwise
     */
    bool update(const Trip &trip) override;

    /**
     * @brief Remove a trip from storage
     * @param id The unique identifier of the trip to remove
     * @return true if the operation was successful, false otherwise
     */
    bool remove(int id) override;
};

#endif // TRIP_REPOSITORY_H