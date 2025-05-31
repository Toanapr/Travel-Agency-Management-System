#include <gtest/gtest.h>
#include "../../src/data/repositories/BookingRepository.h"
#include "../../src/business/models/Booking.h"
#include "../../src/data/database/DatabaseConnection.h"
#include <filesystem>
#include <fstream>

class BookingRepositoryTest : public ::testing::Test
{
protected:
    BookingRepositoryTest() : testBooking(1, 1, 1, "01-05-2024", 2, 2000.0, "confirmed") {}

    void SetUp() override
    {
        // Create test data directory
        testDataPath = "test_data";
        if (!std::filesystem::exists(testDataPath))
        {
            std::filesystem::create_directory(testDataPath);
        }

        // Initialize database connection
        dbConnection = DatabaseConnection::getInstance();
        dbConnection->connect(testDataPath);

        // Create repository with database connection
        repo = std::make_unique<BookingRepository>(dbConnection);

        // Ensure we start with a clean state
        std::ofstream file(testDataPath + "/bookings.csv", std::ios::trunc);
        file << "id,userId,tripId,bookingDate,numberOfPeople,totalCost,status" << std::endl;
        file.close();
    }

    void TearDown() override
    {
        // Clean up test directory
        if (std::filesystem::exists(testDataPath))
        {
            std::filesystem::remove_all(testDataPath);
        }
    }

    std::string testDataPath;
    std::shared_ptr<DatabaseConnection> dbConnection;
    std::unique_ptr<BookingRepository> repo;
    Booking testBooking;
};

// Test add booking
TEST_F(BookingRepositoryTest, AddBooking)
{
    // Thêm đặt chỗ mới - kỳ vọng thành công
    EXPECT_TRUE(repo->add(testBooking));

    // Thêm đặt chỗ mới với ID khác - kỳ vọng thành công
    Booking anotherBooking(2, 2, 2, "02-05-2024", 3, 3000.0, "pending");
    EXPECT_TRUE(repo->add(anotherBooking));

    // Verify bookings were added correctly
    auto bookings = repo->getAll();
    ASSERT_EQ(bookings.size(), 2);

    // Lưu ý: ID có thể được tự động gán nên không nhất thiết phải bằng ID ban đầu
    bool foundFirstBooking = false;
    bool foundSecondBooking = false;

    for (const auto &booking : bookings)
    {
        if (booking.getUserId() == 1 &&
            booking.getTripId() == 1 &&
            booking.getBookingDate() == "01-05-2024" &&
            booking.getNumberOfPeople() == 2 &&
            booking.getTotalCost() == 2000.0 &&
            booking.getStatus() == "confirmed")
        {
            foundFirstBooking = true;
        }

        if (booking.getUserId() == 2 &&
            booking.getTripId() == 2 &&
            booking.getBookingDate() == "02-05-2024" &&
            booking.getNumberOfPeople() == 3 &&
            booking.getTotalCost() == 3000.0 &&
            booking.getStatus() == "pending")
        {
            foundSecondBooking = true;
        }
    }

    EXPECT_TRUE(foundFirstBooking);
    EXPECT_TRUE(foundSecondBooking);
}

// Test get booking by ID
TEST_F(BookingRepositoryTest, GetById)
{
    // Thêm đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));

    // Lấy ID của đặt chỗ đã thêm
    auto bookings = repo->getAll();
    ASSERT_FALSE(bookings.empty());
    int addedBookingId = bookings[0].getId();

    // Lấy đặt chỗ theo ID
    auto booking = repo->getById(addedBookingId);
    ASSERT_TRUE(booking.has_value());
    EXPECT_EQ(booking->getUserId(), testBooking.getUserId());
    EXPECT_EQ(booking->getTripId(), testBooking.getTripId());
    EXPECT_EQ(booking->getBookingDate(), testBooking.getBookingDate());
    EXPECT_EQ(booking->getNumberOfPeople(), testBooking.getNumberOfPeople());
    EXPECT_EQ(booking->getTotalCost(), testBooking.getTotalCost());
    EXPECT_EQ(booking->getStatus(), testBooking.getStatus());

    // Lấy đặt chỗ không tồn tại
    auto nonExistingBooking = repo->getById(999);
    EXPECT_FALSE(nonExistingBooking.has_value());
}

// Test get all bookings
TEST_F(BookingRepositoryTest, GetAll)
{
    // Ban đầu không có đặt chỗ nào
    auto initialBookings = repo->getAll();
    EXPECT_TRUE(initialBookings.empty());

    // Thêm một vài đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));
    ASSERT_TRUE(repo->add(Booking(2, 1, 2, "02-05-2024", 3, 3000.0, "confirmed")));

    // Kiểm tra số lượng đặt chỗ
    auto bookings = repo->getAll();
    ASSERT_EQ(bookings.size(), 2);
}

// Test update booking
TEST_F(BookingRepositoryTest, Update)
{
    // Thêm đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));

    // Lấy ID của đặt chỗ đã thêm
    auto bookings = repo->getAll();
    ASSERT_FALSE(bookings.empty());
    int addedBookingId = bookings[0].getId();

    // Cập nhật đặt chỗ
    Booking updatedBooking(addedBookingId, testBooking.getUserId(), testBooking.getTripId(),
                           testBooking.getBookingDate(), 3, 3000.0, "confirmed");
    EXPECT_TRUE(repo->update(updatedBooking));

    // Kiểm tra cập nhật
    auto booking = repo->getById(addedBookingId);
    ASSERT_TRUE(booking.has_value());
    EXPECT_EQ(booking->getNumberOfPeople(), 3);
    EXPECT_EQ(booking->getTotalCost(), 3000.0);

    // Cập nhật đặt chỗ không tồn tại
    Booking nonExistingBooking(999, 1, 1, "01-05-2024", 2, 2000.0, "confirmed");
    EXPECT_FALSE(repo->update(nonExistingBooking));
}

// Test delete booking
TEST_F(BookingRepositoryTest, Delete)
{
    // Thêm đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));

    // Lấy ID của đặt chỗ đã thêm
    auto bookings = repo->getAll();
    ASSERT_FALSE(bookings.empty());
    int addedBookingId = bookings[0].getId();

    // Xóa đặt chỗ
    EXPECT_TRUE(repo->remove(addedBookingId));

    // Kiểm tra xóa
    bookings = repo->getAll();
    EXPECT_TRUE(bookings.empty());

    // Xóa đặt chỗ không tồn tại
    EXPECT_FALSE(repo->remove(999));
}

// Test find by user ID
TEST_F(BookingRepositoryTest, FindByUserId)
{
    // Thêm một vài đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));
    ASSERT_TRUE(repo->add(Booking(2, 1, 2, "02-05-2024", 2, 1000.0, "confirmed")));
    ASSERT_TRUE(repo->add(Booking(3, 2, 1, "03-05-2024", 2, 2000.0, "confirmed")));

    // Tìm đặt chỗ theo user ID
    auto bookings = repo->findByUserId(1);
    ASSERT_EQ(bookings.size(), 2);

    // Tìm đặt chỗ theo user ID không tồn tại
    bookings = repo->findByUserId(999);
    EXPECT_TRUE(bookings.empty());
}

// Test find by trip ID
TEST_F(BookingRepositoryTest, FindByTripId)
{
    // Thêm một vài đặt chỗ
    ASSERT_TRUE(repo->add(testBooking));
    ASSERT_TRUE(repo->add(Booking(2, 2, 1, "02-05-2024", 2, 1000.0, "confirmed")));
    ASSERT_TRUE(repo->add(Booking(3, 3, 2, "03-05-2024", 2, 2000.0, "confirmed")));

    // Tìm đặt chỗ theo trip ID
    auto bookings = repo->findByTripId(1);
    ASSERT_EQ(bookings.size(), 2);

    // Tìm đặt chỗ theo trip ID không tồn tại
    bookings = repo->findByTripId(999);
    EXPECT_TRUE(bookings.empty());
}

// Test error handling
TEST_F(BookingRepositoryTest, ErrorHandling)
{
    // Kiểm tra các trường hợp đặc biệt
    EXPECT_NO_THROW({
        // Tạo repository với đường dẫn không hợp lệ
        auto invalidDbConnection = DatabaseConnection::getInstance();
        invalidDbConnection->connect("/invalid/path");
        BookingRepository invalidRepo(invalidDbConnection);

        // Thêm đặt chỗ vào repository không hợp lệ
        Booking newBooking(2, 1, 1, "01-05-2024", 2, 1000.0, "confirmed");

        // Thao tác có thể thành công hoặc thất bại tùy thuộc vào OS
        // Chỉ kiểm tra không crash
        invalidRepo.add(newBooking);
    });
}