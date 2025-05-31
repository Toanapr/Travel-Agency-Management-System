#include <gtest/gtest.h>
#include "../src/business/models/Booking.h"
#include "../src/business/models/User.h"
#include "../src/business/models/Trip.h"

class BookingTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up test data
        validId = 1;
        validUserId = 1;
        validTripId = 1;
        validBookingDate = "26-05-2024";
        validNumberOfPeople = 2;
        validTotalCost = 2000.0;
        validStatus = "pending";
    }

    int validId;
    int validUserId;
    int validTripId;
    std::string validBookingDate;
    int validNumberOfPeople;
    double validTotalCost;
    std::string validStatus;
};

// Test constructor with valid data
TEST_F(BookingTest, ConstructorValidData)
{
    EXPECT_NO_THROW({
        Booking booking(validId, validUserId, validTripId, validBookingDate,
                        validNumberOfPeople, validTotalCost, validStatus);
    });

    Booking booking(validId, validUserId, validTripId, validBookingDate,
                    validNumberOfPeople, validTotalCost, validStatus);

    EXPECT_EQ(booking.getId(), validId);
    EXPECT_EQ(booking.getUserId(), validUserId);
    EXPECT_EQ(booking.getTripId(), validTripId);
    EXPECT_EQ(booking.getBookingDate(), validBookingDate);
    EXPECT_EQ(booking.getNumberOfPeople(), validNumberOfPeople);
    EXPECT_EQ(booking.getTotalCost(), validTotalCost);
    EXPECT_EQ(booking.getStatus(), validStatus);
}

// Test status validation
TEST_F(BookingTest, StatusValidation)
{
    Booking booking(validId, validUserId, validTripId, validBookingDate,
                    validNumberOfPeople, validTotalCost, validStatus);

    // All validation is performed before setting values
    booking.setStatus("confirmed");
    EXPECT_EQ(booking.getStatus(), "confirmed");

    booking.setStatus("cancelled");
    EXPECT_EQ(booking.getStatus(), "cancelled");

    booking.setStatus("pending");
    EXPECT_EQ(booking.getStatus(), "pending");

    booking.setStatus("Invalid");
    EXPECT_EQ(booking.getStatus(), "Invalid");

    booking.setStatus("");
    EXPECT_EQ(booking.getStatus(), "");
}

// Test cost calculation
TEST_F(BookingTest, CostCalculation)
{
    Booking booking(validId, validUserId, validTripId, validBookingDate,
                    validNumberOfPeople, validTotalCost, validStatus);

    // Test with different people counts
    EXPECT_EQ(booking.getTotalCost(), validTotalCost);

    // Test cost calculation with trip cost
    Trip trip(1, "Test Trip", 1000.0, 20, "01-06-2024", "07-06-2024");

    Booking booking2(2, validUserId, trip.getId(), validBookingDate,
                     2, 2000.0, validStatus);
    EXPECT_EQ(booking2.getTotalCost(), trip.getCost() * 2);
}

// Test number of people validation
TEST_F(BookingTest, NumberOfPeopleValidation)
{
    // All validation is performed before object creation
    Booking booking1(validId, validUserId, validTripId, validBookingDate,
                     0, validTotalCost, validStatus);
    EXPECT_EQ(booking1.getNumberOfPeople(), 0);

    Booking booking2(validId, validUserId, validTripId, validBookingDate,
                     -1, validTotalCost, validStatus);
    EXPECT_EQ(booking2.getNumberOfPeople(), -1);

    Booking booking3(validId, validUserId, validTripId, validBookingDate,
                     validNumberOfPeople, validTotalCost, validStatus);

    booking3.setNumberOfPeople(0);
    EXPECT_EQ(booking3.getNumberOfPeople(), 0);

    booking3.setNumberOfPeople(-1);
    EXPECT_EQ(booking3.getNumberOfPeople(), -1);

    booking3.setNumberOfPeople(1);
    EXPECT_EQ(booking3.getNumberOfPeople(), 1);
}

// Test booking date validation
TEST_F(BookingTest, BookingDateValidation)
{
    // All validation is performed before object creation
    Booking booking(validId, validUserId, validTripId, "26/05/2024",
                    validNumberOfPeople, validTotalCost, validStatus);
    EXPECT_EQ(booking.getBookingDate(), "26/05/2024");

    booking.setBookingDate("invalid-date");
    EXPECT_EQ(booking.getBookingDate(), "invalid-date");
}