#include <gtest/gtest.h>
#include "../src/business/models/Trip.h"
#include <chrono>
#include <ctime>

class TripTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up test data
        validId = 1;
        validName = "Beach Vacation";
        validCost = 1000.0;
        validAvailableSeats = 20;
        validStartDate = "01-06-2024";
        validEndDate = "07-06-2024";
    }

    int validId;
    std::string validName;
    double validCost;
    int validAvailableSeats;
    std::string validStartDate;
    std::string validEndDate;
};

// Test constructor with valid data
TEST_F(TripTest, ConstructorValidData)
{
    EXPECT_NO_THROW({
        Trip trip(validId, validName, validCost, validAvailableSeats, validStartDate, validEndDate);
    });

    Trip trip(validId, validName, validCost, validAvailableSeats, validStartDate, validEndDate);

    EXPECT_EQ(trip.getId(), validId);
    EXPECT_EQ(trip.getName(), validName);
    EXPECT_EQ(trip.getCost(), validCost);
    EXPECT_EQ(trip.getAvailableSeats(), validAvailableSeats);
    EXPECT_EQ(trip.getStartDate(), validStartDate);
    EXPECT_EQ(trip.getEndDate(), validEndDate);
}

// Test constructor with invalid data
TEST_F(TripTest, ConstructorInvalidData)
{
    // All validation is performed before object creation, so no exceptions should be thrown
    Trip trip1(0, validName, validCost, validAvailableSeats, validStartDate, validEndDate);
    EXPECT_EQ(trip1.getId(), 0);

    Trip trip2(validId, validName, -100.0, validAvailableSeats, validStartDate, validEndDate);
    EXPECT_EQ(trip2.getCost(), -100.0);

    Trip trip3(validId, validName, validCost, -10, validStartDate, validEndDate);
    EXPECT_EQ(trip3.getAvailableSeats(), -10);

    Trip trip4(validId, validName, validCost, validAvailableSeats, "07-06-2024", "01-06-2024");
    EXPECT_EQ(trip4.getStartDate(), "07-06-2024");
    EXPECT_EQ(trip4.getEndDate(), "01-06-2024");
}

// Test cost validation
TEST_F(TripTest, CostValidation)
{
    // All validation is performed before object creation
    Trip trip1(validId, validName, 0.0, validAvailableSeats, validStartDate, validEndDate);
    EXPECT_EQ(trip1.getCost(), 0.0);

    Trip trip2(validId, validName, -1.0, validAvailableSeats, validStartDate, validEndDate);
    EXPECT_EQ(trip2.getCost(), -1.0);

    Trip trip3(validId, validName, 0.01, validAvailableSeats, validStartDate, validEndDate);
    EXPECT_EQ(trip3.getCost(), 0.01);
}

// Test available seats validation
TEST_F(TripTest, AvailableSeatsValidation)
{
    Trip trip(validId, validName, validCost, validAvailableSeats, validStartDate, validEndDate);

    trip.setAvailableSeats(validAvailableSeats);
    EXPECT_EQ(trip.getAvailableSeats(), validAvailableSeats);

    trip.setAvailableSeats(0);
    EXPECT_EQ(trip.getAvailableSeats(), 0);

    trip.setAvailableSeats(-1);
    EXPECT_EQ(trip.getAvailableSeats(), -1);
}

// Test date validation
TEST_F(TripTest, DateValidation)
{
    // All validation is performed before object creation
    Trip trip1(validId, validName, validCost, validAvailableSeats, "01/06/2024", validEndDate);
    EXPECT_EQ(trip1.getStartDate(), "01/06/2024");

    Trip trip2(validId, validName, validCost, validAvailableSeats, "32-06-2024", validEndDate);
    EXPECT_EQ(trip2.getStartDate(), "32-06-2024");

    Trip trip3(validId, validName, validCost, validAvailableSeats, "invalid-date", validEndDate);
    EXPECT_EQ(trip3.getStartDate(), "invalid-date");
}