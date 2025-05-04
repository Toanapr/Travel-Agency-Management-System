#ifndef ITRIP_REPOSITORY_H
#define ITRIP_REPOSITORY_H

#include <vector>
#include <optional>
#include "../models/Trip.h"

/**
 * @interface ITripRepository
 * @brief Interface for trip data persistence operations
 *
 * This interface defines the contract for classes that handle
 * the persistence of Trip objects in the data store. It follows
 * the Repository pattern to abstract data access logic.
 */
class ITripRepository
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~ITripRepository() = default;

    /**
     * @brief Retrieve all trips from the data store
     * @return Vector containing all trips
     */
    virtual std::vector<Trip> getAll() = 0;

    /**
     * @brief Find a trip by its ID
     * @param id The unique identifier of the trip to find
     * @return Optional containing the trip if found, empty otherwise
     */
    virtual std::optional<Trip> getById(int id) = 0;

    /**
     * @brief Find trips by name or destination (partial match)
     * @param name The name or part of the name/destination to search for
     * @return Vector of trips whose names match the search criteria
     */
    virtual std::vector<Trip> findByName(const std::string &name) = 0;

    /**
     * @brief Add a new trip to the data store
     * @param trip The trip object to add
     * @return true if the operation was successful, false otherwise
     */
    virtual bool add(const Trip &trip) = 0;

    /**
     * @brief Update an existing trip in the data store
     * @param trip The trip object with updated information
     * @return true if the operation was successful, false otherwise
     */
    virtual bool update(const Trip &trip) = 0;

    /**
     * @brief Remove a trip from the data store
     * @param id The unique identifier of the trip to remove
     * @return true if the operation was successful, false otherwise
     */
    virtual bool remove(int id) = 0;
};

#endif // ITRIP_REPOSITORY_H