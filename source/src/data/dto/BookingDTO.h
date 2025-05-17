#ifndef BOOKING_DTO_H
#define BOOKING_DTO_H

#include <string>

/**
 * @class BookingDTO
 * @brief Data Transfer Object for Booking entities
 *
 * This class represents the data structure used to transfer booking data
 * between the data layer and business layer of the application.
 * It is designed to match the CSV structure for booking data.
 */
class BookingDTO
{
private:
    int _id;                  ///< Unique identifier for the booking
    int _userId;              ///< ID of the user who made the booking
    int _tripId;              ///< ID of the trip that was booked
    std::string _bookingDate; ///< Date when the booking was made
    int _numberOfPersons;     ///< Number of persons included in the booking
    double _totalPrice;       ///< Total price of the booking
    std::string _status;      ///< Status of the booking (e.g., "Confirmed", "Pending", "Cancelled")

public:
    /**
     * @brief Default constructor
     */
    BookingDTO();

    /**
     * @brief Parameterized constructor
     * @param id Booking's unique identifier
     * @param userId ID of the user who made the booking
     * @param tripId ID of the trip that was booked
     * @param bookingDate Date when the booking was made
     * @param numberOfPersons Number of persons included in the booking
     * @param totalPrice Total price of the booking
     * @param status Status of the booking
     */
    BookingDTO(int id, int userId, int tripId, const std::string &bookingDate,
               int numberOfPersons, double totalPrice, const std::string &status);

    /**
     * @brief Get the booking ID
     * @return Booking's unique identifier
     */
    int getId() const;

    /**
     * @brief Get the user ID
     * @return ID of the user who made the booking
     */
    int getUserId() const;

    /**
     * @brief Get the trip ID
     * @return ID of the trip that was booked
     */
    int getTripId() const;

    /**
     * @brief Get the booking date
     * @return Date when the booking was made
     */
    const std::string &getBookingDate() const;

    /**
     * @brief Get the number of persons
     * @return Number of persons included in the booking
     */
    int getNumberOfPersons() const;

    /**
     * @brief Get the total price
     * @return Total price of the booking
     */
    double getTotalPrice() const;

    /**
     * @brief Get the booking status
     * @return Status of the booking
     */
    const std::string &getStatus() const;

    /**
     * @brief Set the booking ID
     * @param id New unique identifier
     */
    void setId(int id);

    /**
     * @brief Set the user ID
     * @param userId New user ID
     */
    void setUserId(int userId);

    /**
     * @brief Set the trip ID
     * @param tripId New trip ID
     */
    void setTripId(int tripId);

    /**
     * @brief Set the booking date
     * @param bookingDate New booking date
     */
    void setBookingDate(const std::string &bookingDate);

    /**
     * @brief Set the number of persons
     * @param numberOfPersons New number of persons
     */
    void setNumberOfPersons(int numberOfPersons);

    /**
     * @brief Set the total price
     * @param totalPrice New total price
     */
    void setTotalPrice(double totalPrice);

    /**
     * @brief Set the booking status
     * @param status New booking status
     */
    void setStatus(const std::string &status);
};

#endif // BOOKING_DTO_H