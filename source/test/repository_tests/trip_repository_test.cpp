#include <gtest/gtest.h>
#include "../../src/data/repositories/TripRepository.h"
#include "../../src/business/models/Trip.h"
#include "../../src/data/database/DatabaseConnection.h"
#include <filesystem>
#include <fstream>

class TripRepositoryTest : public ::testing::Test
{
protected:
    TripRepositoryTest() : testTrip(1, "Beach Vacation", 1000.0, 20, "01-06-2024", "07-06-2024") {}

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
        repo = std::make_unique<TripRepository>(dbConnection);

        // Ensure we start with a clean state
        std::ofstream file(testDataPath + "/trips.csv", std::ios::trunc);
        file << "id,name,cost,availableSeats,startDate,endDate" << std::endl;
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
    std::unique_ptr<TripRepository> repo;
    Trip testTrip;
};

// Test add trip
TEST_F(TripRepositoryTest, AddTrip)
{
    // Thêm chuyến đi mới - kỳ vọng thành công
    EXPECT_TRUE(repo->add(testTrip));

    // Thêm chuyến đi mới với ID khác - kỳ vọng thành công
    Trip anotherTrip(2, "Mountain Trek", 1500.0, 15, "01-07-2024", "07-07-2024");
    EXPECT_TRUE(repo->add(anotherTrip));

    // Verify trips were added correctly
    auto trips = repo->getAll();
    ASSERT_EQ(trips.size(), 2);

    // Lưu ý: ID có thể được tự động gán nên không nhất thiết phải bằng ID ban đầu
    bool foundFirstTrip = false;
    bool foundSecondTrip = false;

    for (const auto &trip : trips)
    {
        if (trip.getName() == "Beach Vacation" &&
            trip.getCost() == 1000.0 &&
            trip.getAvailableSeats() == 20 &&
            trip.getStartDate() == "01-06-2024" &&
            trip.getEndDate() == "07-06-2024")
        {
            foundFirstTrip = true;
        }

        if (trip.getName() == "Mountain Trek" &&
            trip.getCost() == 1500.0 &&
            trip.getAvailableSeats() == 15 &&
            trip.getStartDate() == "01-07-2024" &&
            trip.getEndDate() == "07-07-2024")
        {
            foundSecondTrip = true;
        }
    }

    EXPECT_TRUE(foundFirstTrip);
    EXPECT_TRUE(foundSecondTrip);
}

// Test get trip by ID
TEST_F(TripRepositoryTest, GetById)
{
    // Thêm chuyến đi
    ASSERT_TRUE(repo->add(testTrip));

    // Lấy ID của chuyến đi đã thêm
    auto trips = repo->getAll();
    ASSERT_FALSE(trips.empty());
    int addedTripId = trips[0].getId();

    // Lấy chuyến đi theo ID
    auto trip = repo->getById(addedTripId);
    ASSERT_TRUE(trip.has_value());
    EXPECT_EQ(trip->getName(), testTrip.getName());
    EXPECT_EQ(trip->getCost(), testTrip.getCost());
    EXPECT_EQ(trip->getAvailableSeats(), testTrip.getAvailableSeats());
    EXPECT_EQ(trip->getStartDate(), testTrip.getStartDate());
    EXPECT_EQ(trip->getEndDate(), testTrip.getEndDate());

    // Lấy chuyến đi không tồn tại
    auto nonExistingTrip = repo->getById(999);
    EXPECT_FALSE(nonExistingTrip.has_value());
}

// Test get all trips
TEST_F(TripRepositoryTest, GetAll)
{
    // Ban đầu không có chuyến đi nào
    auto initialTrips = repo->getAll();
    EXPECT_TRUE(initialTrips.empty());

    // Thêm một vài chuyến đi
    ASSERT_TRUE(repo->add(testTrip));
    ASSERT_TRUE(repo->add(Trip(2, "Mountain Trek", 1500.0, 15, "01-07-2024", "07-07-2024")));

    // Kiểm tra số lượng chuyến đi
    auto trips = repo->getAll();
    ASSERT_EQ(trips.size(), 2);
}

// Test update trip
TEST_F(TripRepositoryTest, Update)
{
    // Thêm chuyến đi
    ASSERT_TRUE(repo->add(testTrip));

    // Lấy ID của chuyến đi đã thêm
    auto trips = repo->getAll();
    ASSERT_FALSE(trips.empty());
    int addedTripId = trips[0].getId();

    // Cập nhật chuyến đi
    Trip updatedTrip(addedTripId, "Luxury Beach Vacation", 1200.0, 20, "01-06-2024", "07-06-2024");
    EXPECT_TRUE(repo->update(updatedTrip));

    // Kiểm tra cập nhật
    auto trip = repo->getById(addedTripId);
    ASSERT_TRUE(trip.has_value());
    EXPECT_EQ(trip->getName(), "Luxury Beach Vacation");
    EXPECT_EQ(trip->getCost(), 1200.0);

    // Cập nhật chuyến đi không tồn tại
    Trip nonExistingTrip(999, "Test Trip", 1000.0, 10, "01-08-2024", "07-08-2024");
    EXPECT_FALSE(repo->update(nonExistingTrip));
}

// Test delete trip
TEST_F(TripRepositoryTest, Delete)
{
    // Thêm chuyến đi
    ASSERT_TRUE(repo->add(testTrip));

    // Lấy ID của chuyến đi đã thêm
    auto trips = repo->getAll();
    ASSERT_FALSE(trips.empty());
    int addedTripId = trips[0].getId();

    // Xóa chuyến đi
    EXPECT_TRUE(repo->remove(addedTripId));

    // Kiểm tra xóa
    trips = repo->getAll();
    EXPECT_TRUE(trips.empty());

    // Xóa chuyến đi không tồn tại
    EXPECT_FALSE(repo->remove(999));
}

// Test find by name
TEST_F(TripRepositoryTest, FindByName)
{
    // Thêm một vài chuyến đi
    ASSERT_TRUE(repo->add(testTrip));
    ASSERT_TRUE(repo->add(Trip(2, "Beach Paradise", 2000.0, 10, "01-07-2024", "07-07-2024")));
    ASSERT_TRUE(repo->add(Trip(3, "Mountain Trek", 1500.0, 15, "01-08-2024", "07-08-2024")));

    // Tìm chuyến đi có "Beach" trong tên
    auto trips = repo->findByName("Beach");
    ASSERT_EQ(trips.size(), 2);

    // Tìm chuyến đi với tên chính xác
    trips = repo->findByName("Mountain Trek");
    ASSERT_EQ(trips.size(), 1);
    EXPECT_EQ(trips[0].getName(), "Mountain Trek");

    // Tìm tên không tồn tại
    trips = repo->findByName("NonExisting");
    EXPECT_TRUE(trips.empty());
}

// Test error handling
TEST_F(TripRepositoryTest, ErrorHandling)
{
    // Kiểm tra các trường hợp đặc biệt
    EXPECT_NO_THROW({
        // Tạo repository với đường dẫn không hợp lệ
        auto invalidDbConnection = DatabaseConnection::getInstance();
        invalidDbConnection->connect("/invalid/path");
        TripRepository invalidRepo(invalidDbConnection);

        // Thêm chuyến đi vào repository không hợp lệ
        Trip newTrip(2, "Test Trip", 1000.0, 10, "01-07-2024", "07-07-2024");

        // Thao tác có thể thành công hoặc thất bại tùy thuộc vào OS
        // Chỉ kiểm tra không crash
        invalidRepo.add(newTrip);
    });
}