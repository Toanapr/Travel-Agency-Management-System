#ifndef TRIP_H
#define TRIP_H

#include <string>

/**
 * @class Trip
 * @brief Represents a travel trip offered by the agency
 *
 * The Trip class stores information about travel trips available for booking,
 * including details like cost, available seats, and travel dates.
 */
class Trip
{
private:
    int _id;                ///< Unique identifier for the trip
    std::string _name;      ///< Name or description of the trip
    double _cost;           ///< Cost per person for the trip
    int _availableSeats;    ///< Number of seats still available for booking
    std::string _startDate; ///< Trip start date in YYYY-MM-DD format
    std::string _endDate;   ///< Trip end date in YYYY-MM-DD format

public:
    /**
     * @brief Constructor for creating a new trip
     * @param id Unique identifier for the trip
     * @param name Name or description of the trip
     * @param cost Cost per person
     * @param availableSeats Number of seats available for booking
     * @param startDate Trip start date in YYYY-MM-DD format
     * @param endDate Trip end date in YYYY-MM-DD format
     */
    Trip(int id, const std::string &name, double cost, int availableSeats,
         const std::string &startDate, const std::string &endDate);

    // Getters
    /**
     * @brief Get the trip ID
     * @return The unique identifier for the trip
     */
    int getId() const;

    /**
     * @brief Get the trip name
     * @return The name or description of the trip
     */
    std::string getName() const;

    /**
     * @brief Get the trip cost
     * @return The cost per person
     */
    double getCost() const;

    /**
     * @brief Get the number of available seats
     * @return The number of seats still available for booking
     */
    int getAvailableSeats() const;

    /**
     * @brief Get the trip start date
     * @return The start date in YYYY-MM-DD format
     */
    std::string getStartDate() const;

    /**
     * @brief Get the trip end date
     * @return The end date in YYYY-MM-DD format
     */
    std::string getEndDate() const;

    // Setters
    /**
     * @brief Set the trip name
     * @param name The new name or description for the trip
     */
    void setName(const std::string &name);

    /**
     * @brief Set the trip cost
     * @param cost The new cost per person
     */
    void setCost(double cost);

    /**
     * @brief Set the number of available seats
     * @param availableSeats The new number of available seats
     */
    void setAvailableSeats(int availableSeats);

    /**
     * @brief Set the trip start date
     * @param startDate The new start date in YYYY-MM-DD format
     */
    void setStartDate(const std::string &startDate);

    /**
     * @brief Set the trip end date
     * @param endDate The new end date in YYYY-MM-DD format
     */
    void setEndDate(const std::string &endDate);
};

#endif // TRIP_H