#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/business/services/BookingService.h"
#include "../../src/business/interfaces/IBookingRepository.h"
#include "../../src/business/interfaces/IUserRepository.h"
#include "../../src/business/interfaces/ITripRepository.h"
#include "../../src/business/models/Booking.h"
#include "../../src/business/models/User.h"
#include "../../src/business/models/Trip.h"

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

// Mock repositories
class MockBookingRepository : public IBookingRepository
{
public:
    MOCK_METHOD(bool, add, (const Booking &), (override));
    MOCK_METHOD(std::optional<Booking>, getById, (int), (override));
    MOCK_METHOD(std::vector<Booking>, getAll, (), (override));
    MOCK_METHOD(bool, update, (const Booking &), (override));
    MOCK_METHOD(bool, remove, (int), (override));
    MOCK_METHOD(std::vector<Booking>, findByUserId, (int), (override));
    MOCK_METHOD(std::vector<Booking>, findByTripId, (int), (override));
};

class MockUserRepository : public IUserRepository
{
public:
    MOCK_METHOD(bool, add, (const User &), (override));
    MOCK_METHOD(std::optional<User>, getById, (int), (override));
    MOCK_METHOD(std::vector<User>, getAll, (), (override));
    MOCK_METHOD(bool, update, (const User &), (override));
    MOCK_METHOD(bool, remove, (int), (override));
    MOCK_METHOD(std::vector<User>, findByName, (const std::string &), (override));
};

class MockTripRepository : public ITripRepository
{
public:
    MOCK_METHOD(bool, add, (const Trip &), (override));
    MOCK_METHOD(std::optional<Trip>, getById, (int), (override));
    MOCK_METHOD(std::vector<Trip>, getAll, (), (override));
    MOCK_METHOD(bool, update, (const Trip &), (override));
    MOCK_METHOD(bool, remove, (int), (override));
    MOCK_METHOD(std::vector<Trip>, findByName, (const std::string &), (override));
};

class BookingServiceTest : public ::testing::Test
{
protected:
    // Thêm constructor mặc định để khởi tạo các đối tượng test
    BookingServiceTest() : testUser(1, "John Doe", "123 Main St", "0123456789", "john@example.com"),
                           testTrip(1, "Beach Vacation", 1000.0, 20, "01-06-2024", "07-06-2024"),
                           testBooking(1, testUser.getId(), testTrip.getId(), "26-05-2024", 2, 2000.0, "Confirmed")
    {
    }

    void SetUp() override
    {
        bookingRepo = std::make_shared<MockBookingRepository>();
        userRepo = std::make_shared<MockUserRepository>();
        tripRepo = std::make_shared<MockTripRepository>();
        service = std::make_unique<BookingService>(bookingRepo, userRepo, tripRepo);
    }

    std::shared_ptr<MockBookingRepository> bookingRepo;
    std::shared_ptr<MockUserRepository> userRepo;
    std::shared_ptr<MockTripRepository> tripRepo;
    std::unique_ptr<BookingService> service;
    User testUser;
    Trip testTrip;
    Booking testBooking;
};

// Test getAllBookings
TEST_F(BookingServiceTest, GetAllBookings)
{
    std::vector<Booking> bookings = {
        testBooking,
        Booking(2, 2, 2, "27-05-2024", 3, 3000.0, "Pending")};

    EXPECT_CALL(*bookingRepo, getAll())
        .WillOnce(Return(bookings));

    auto result = service->getAllBookings();
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getId(), 1);
    EXPECT_EQ(result[1].getId(), 2);
}

// Test getBookingById
TEST_F(BookingServiceTest, GetBookingById)
{
    EXPECT_CALL(*bookingRepo, getById(testBooking.getId()))
        .WillOnce(Return(std::optional<Booking>(testBooking)));

    auto booking = service->getBookingById(testBooking.getId());
    ASSERT_TRUE(booking.has_value());
    EXPECT_EQ(booking->getId(), testBooking.getId());
    EXPECT_EQ(booking->getUserId(), testBooking.getUserId());
    EXPECT_EQ(booking->getTripId(), testBooking.getTripId());

    // Test for non-existing booking
    EXPECT_CALL(*bookingRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->getBookingById(999).has_value());
}

// Test findBookingsByUserId
TEST_F(BookingServiceTest, FindBookingsByUserId)
{
    std::vector<Booking> userBookings = {
        testBooking,
        Booking(2, testUser.getId(), 2, "27-05-2024", 1, 1500.0, "Pending")};

    EXPECT_CALL(*bookingRepo, findByUserId(testUser.getId()))
        .WillOnce(Return(userBookings));

    auto bookings = service->findBookingsByUserId(testUser.getId());
    ASSERT_EQ(bookings.size(), 2);
    EXPECT_EQ(bookings[0].getUserId(), testUser.getId());
    EXPECT_EQ(bookings[1].getUserId(), testUser.getId());

    // Test with no bookings
    EXPECT_CALL(*bookingRepo, findByUserId(999))
        .WillOnce(Return(std::vector<Booking>()));

    bookings = service->findBookingsByUserId(999);
    EXPECT_TRUE(bookings.empty());
}

// Test findBookingsByTripId
TEST_F(BookingServiceTest, FindBookingsByTripId)
{
    std::vector<Booking> tripBookings = {
        testBooking,
        Booking(2, 2, testTrip.getId(), "27-05-2024", 3, 3000.0, "Confirmed")};

    EXPECT_CALL(*bookingRepo, findByTripId(testTrip.getId()))
        .WillOnce(Return(tripBookings));

    auto bookings = service->findBookingsByTripId(testTrip.getId());
    ASSERT_EQ(bookings.size(), 2);
    EXPECT_EQ(bookings[0].getTripId(), testTrip.getId());
    EXPECT_EQ(bookings[1].getTripId(), testTrip.getId());

    // Test with no bookings
    EXPECT_CALL(*bookingRepo, findByTripId(999))
        .WillOnce(Return(std::vector<Booking>()));

    bookings = service->findBookingsByTripId(999);
    EXPECT_TRUE(bookings.empty());
}

// Test createBooking with valid data
TEST_F(BookingServiceTest, CreateBookingValidData)
{
    // Chuẩn bị dữ liệu test
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));

    // Đảm bảo tripRepo->getById được gọi nhiều lần và luôn trả về testTrip
    EXPECT_CALL(*tripRepo, getById(testTrip.getId()))
        .WillRepeatedly(Return(std::optional<Trip>(testTrip)));

    // The booking service will create a booking with ID=0
    EXPECT_CALL(*bookingRepo, add(_))
        .WillOnce([](const Booking &booking)
                  {
            EXPECT_EQ(booking.getUserId(), 1);
            EXPECT_EQ(booking.getTripId(), 1);
            EXPECT_EQ(booking.getNumberOfPeople(), 2);
            EXPECT_DOUBLE_EQ(booking.getTotalCost(), 2000.0);
            EXPECT_EQ(booking.getStatus(), "Confirmed");
            return true; });

    // Should update trip available seats
    EXPECT_CALL(*tripRepo, update(_))
        .WillOnce([&](const Trip &trip)
                  {
            EXPECT_EQ(trip.getId(), testTrip.getId());
            EXPECT_EQ(trip.getAvailableSeats(), 18); // 20 - 2 = 18
            return true; });

    EXPECT_TRUE(service->createBooking(testUser.getId(), testTrip.getId(), "26-05-2024", 2));
}

// Test createBooking with invalid user
TEST_F(BookingServiceTest, CreateBookingInvalidUser)
{
    EXPECT_CALL(*userRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->createBooking(999, testTrip.getId(), "26-05-2024", 2));
}

// Test createBooking with invalid trip
TEST_F(BookingServiceTest, CreateBookingInvalidTrip)
{
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));
    EXPECT_CALL(*tripRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->createBooking(testUser.getId(), 999, "26-05-2024", 2));
}

// Test createBooking with insufficient seats
TEST_F(BookingServiceTest, CreateBookingInsufficientSeats)
{
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));
    EXPECT_CALL(*tripRepo, getById(testTrip.getId()))
        .WillOnce(Return(std::optional<Trip>(testTrip)));

    EXPECT_FALSE(service->createBooking(testUser.getId(), testTrip.getId(), "26-05-2024", 25));
}

// Test updateBookingStatus
TEST_F(BookingServiceTest, UpdateBookingStatus)
{
    Booking updatedBooking = testBooking;
    updatedBooking.setStatus("Cancelled");

    EXPECT_CALL(*bookingRepo, getById(testBooking.getId()))
        .WillOnce(Return(std::optional<Booking>(testBooking)));
    EXPECT_CALL(*bookingRepo, update(_))
        .WillOnce([](const Booking &booking)
                  {
            EXPECT_EQ(booking.getStatus(), "Cancelled");
            return true; });

    EXPECT_TRUE(service->updateBookingStatus(testBooking.getId(), "Cancelled"));

    // Test with non-existing booking
    EXPECT_CALL(*bookingRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->updateBookingStatus(999, "Cancelled"));
}

// Test cancelBooking
TEST_F(BookingServiceTest, CancelBooking)
{
    EXPECT_CALL(*bookingRepo, getById(testBooking.getId()))
        .WillOnce(Return(std::optional<Booking>(testBooking)));
    EXPECT_CALL(*tripRepo, getById(testBooking.getTripId()))
        .WillOnce(Return(std::optional<Trip>(testTrip)));

    Trip updatedTrip = testTrip;
    updatedTrip.setAvailableSeats(22); // 20 + 2 = 22
    EXPECT_CALL(*tripRepo, update(updatedTrip))
        .WillOnce(Return(true));

    EXPECT_CALL(*bookingRepo, update(_))
        .WillOnce([](const Booking &booking)
                  {
            EXPECT_EQ(booking.getStatus(), "Cancelled");
            return true; });

    EXPECT_TRUE(service->cancelBooking(testBooking.getId()));

    // Test with non-existing booking
    EXPECT_CALL(*bookingRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->cancelBooking(999));
}

// Test calculateTotalCost
TEST_F(BookingServiceTest, CalculateTotalCost)
{
    EXPECT_CALL(*tripRepo, getById(testTrip.getId()))
        .WillOnce(Return(std::optional<Trip>(testTrip)));

    double cost = service->calculateTotalCost(testTrip.getId(), 2);
    EXPECT_EQ(cost, 2000.0);

    // Test with non-existing trip
    EXPECT_CALL(*tripRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    cost = service->calculateTotalCost(999, 2);
    EXPECT_EQ(cost, 0.0);
}

// Test validateBooking
TEST_F(BookingServiceTest, ValidateBooking)
{
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));
    EXPECT_CALL(*tripRepo, getById(testTrip.getId()))
        .WillOnce(Return(std::optional<Trip>(testTrip)));

    EXPECT_TRUE(service->validateBooking(testUser.getId(), testTrip.getId(), 2));

    // Test with invalid user
    EXPECT_CALL(*userRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->validateBooking(999, testTrip.getId(), 2));

    // Test with invalid trip
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));
    EXPECT_CALL(*tripRepo, getById(999))
        .WillOnce(Return(std::nullopt));

    EXPECT_FALSE(service->validateBooking(testUser.getId(), 999, 2));

    // Test with insufficient seats
    EXPECT_CALL(*userRepo, getById(testUser.getId()))
        .WillOnce(Return(std::optional<User>(testUser)));
    EXPECT_CALL(*tripRepo, getById(testTrip.getId()))
        .WillOnce(Return(std::optional<Trip>(testTrip)));

    EXPECT_FALSE(service->validateBooking(testUser.getId(), testTrip.getId(), 25));
}