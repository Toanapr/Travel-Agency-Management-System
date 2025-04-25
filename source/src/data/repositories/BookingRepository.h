#ifndef BOOKING_REPOSITORY_H
#define BOOKING_REPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include "../../business/interfaces/IBookingRepository.h"
#include "../../business/models/Booking.h"
#include "../database/DatabaseConnection.h"

/**
 * @class BookingRepository
 * @brief Implementation of IBookingRepository for CSV file storage
 *
 * This class provides an implementation of the IBookingRepository interface
 * that uses CSV files for persistent storage of booking data. It handles all
 * CRUD operations for Booking objects, translating between object and CSV formats.
 */
class BookingRepository : public IBookingRepository
{
private:
    std::shared_ptr<DatabaseConnection> _dbConnection; ///< Database connection for file access
    const std::string _filename = "bookings.csv";      ///< Name of the CSV file for booking data storage

    /**
     * @brief Convert a CSV line to a Booking object
     * @param line CSV-formatted string containing booking data
     * @return Booking object created from the CSV data
     */
    Booking parseBookingFromCsv(const std::string &line);

    /**
     * @brief Convert a Booking object to CSV format
     * @param booking Booking object to convert
     * @return CSV-formatted string representing the booking
     */
    std::string convertBookingToCsv(const Booking &booking);

    /**
     * @brief Generate the next available ID for a new booking
     * @return Next available unique identifier
     */
    int getNextId();

public:
    /**
     * @brief Constructor for BookingRepository
     * @param dbConnection Shared pointer to DatabaseConnection for file operations
     */
    BookingRepository(std::shared_ptr<DatabaseConnection> dbConnection);

    // IBookingRepository implementation
    /**
     * @brief Retrieve all bookings from storage
     * @return Vector of all Booking objects
     */
    std::vector<Booking> getAll() override;

    /**
     * @brief Find a booking by its ID
     * @param id The unique identifier of the booking to find
     * @return Optional containing the booking if found, empty otherwise
     */
    std::optional<Booking> getById(int id) override;

    /**
     * @brief Find all bookings for a specific user
     * @param userId The unique identifier of the user
     * @return Vector of bookings made by the specified user
     */
    std::vector<Booking> findByUserId(int userId) override;

    /**
     * @brief Find all bookings for a specific trip
     * @param tripId The unique identifier of the trip
     * @return Vector of bookings for the specified trip
     */
    std::vector<Booking> findByTripId(int tripId) override;

    /**
     * @brief Add a new booking to storage
     * @param booking The booking object to add
     * @return true if the operation was successful, false otherwise
     */
    bool add(const Booking &booking) override;

    /**
     * @brief Update an existing booking in storage
     * @param booking The booking object with updated information
     * @return true if the operation was successful, false otherwise
     */
    bool update(const Booking &booking) override;

    /**
     * @brief Remove a booking from storage
     * @param id The unique identifier of the booking to remove
     * @return true if the operation was successful, false otherwise
     */
    bool remove(int id) override;
};

#endif // BOOKING_REPOSITORY_H