#ifndef TRIP_DTO_H
#define TRIP_DTO_H

#include <string>

/**
 * @class TripDTO
 * @brief Data Transfer Object for Trip entities
 *
 * This class represents the data structure used to transfer trip data
 * between the data layer and business layer of the application.
 * It is designed to match the CSV structure for trip data.
 */
class TripDTO
{
private:
    int _id;                  ///< Unique identifier for the trip
    std::string _name;        ///< Trip name/title
    std::string _destination; ///< Trip destination
    std::string _startDate;   ///< Start date in string format
    std::string _endDate;     ///< End date in string format
    double _price;            ///< Trip price
    int _capacity;            ///< Maximum number of participants
    std::string _description; ///< Trip description

public:
    /**
     * @brief Default constructor
     */
    TripDTO();

    /**
     * @brief Parameterized constructor
     * @param id Trip's unique identifier
     * @param name Trip name/title
     * @param destination Trip destination
     * @param startDate Start date (as string)
     * @param endDate End date (as string)
     * @param price Trip price
     * @param capacity Maximum number of participants
     * @param description Trip description
     */
    TripDTO(int id, const std::string &name, const std::string &destination,
            const std::string &startDate, const std::string &endDate,
            double price, int capacity, const std::string &description);

    /**
     * @brief Get the trip ID
     * @return Trip's unique identifier
     */
    int getId() const;

    /**
     * @brief Get the trip name
     * @return Trip name/title
     */
    const std::string &getName() const;

    /**
     * @brief Get the trip destination
     * @return Trip destination
     */
    const std::string &getDestination() const;

    /**
     * @brief Get the trip start date
     * @return Start date as string
     */
    const std::string &getStartDate() const;

    /**
     * @brief Get the trip end date
     * @return End date as string
     */
    const std::string &getEndDate() const;

    /**
     * @brief Get the trip price
     * @return Trip price
     */
    double getPrice() const;

    /**
     * @brief Get the trip capacity
     * @return Maximum number of participants
     */
    int getCapacity() const;

    /**
     * @brief Get the trip description
     * @return Trip description
     */
    const std::string &getDescription() const;

    /**
     * @brief Set the trip ID
     * @param id New unique identifier
     */
    void setId(int id);

    /**
     * @brief Set the trip name
     * @param name New trip name/title
     */
    void setName(const std::string &name);

    /**
     * @brief Set the trip destination
     * @param destination New trip destination
     */
    void setDestination(const std::string &destination);

    /**
     * @brief Set the trip start date
     * @param startDate New start date (as string)
     */
    void setStartDate(const std::string &startDate);

    /**
     * @brief Set the trip end date
     * @param endDate New end date (as string)
     */
    void setEndDate(const std::string &endDate);

    /**
     * @brief Set the trip price
     * @param price New trip price
     */
    void setPrice(double price);

    /**
     * @brief Set the trip capacity
     * @param capacity New maximum number of participants
     */
    void setCapacity(int capacity);

    /**
     * @brief Set the trip description
     * @param description New trip description
     */
    void setDescription(const std::string &description);
};

#endif // TRIP_DTO_H