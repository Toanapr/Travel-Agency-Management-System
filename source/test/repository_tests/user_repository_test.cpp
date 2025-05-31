#include <gtest/gtest.h>
#include "../../src/data/repositories/UserRepository.h"
#include "../../src/business/models/User.h"
#include "../../src/data/database/DatabaseConnection.h"
#include <filesystem>
#include <fstream>

class UserRepositoryTest : public ::testing::Test
{
protected:
    UserRepositoryTest() : testUser(1, "John Doe", "123 Main St", "0123456789", "john@example.com") {}

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
        repo = std::make_unique<UserRepository>(dbConnection);

        // Ensure we start with a clean state
        std::ofstream file(testDataPath + "/users.csv", std::ios::trunc);
        file << "id,name,address,phone,email" << std::endl;
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
    std::unique_ptr<UserRepository> repo;
    User testUser;
};

// Test add user
TEST_F(UserRepositoryTest, AddUser)
{
    // Thêm người dùng mới - kỳ vọng thành công
    EXPECT_TRUE(repo->add(testUser));

    // Thêm người dùng mới với ID khác - kỳ vọng thành công
    User anotherUser(2, "Jane Smith", "456 Oak St", "9876543210", "jane@example.com");
    EXPECT_TRUE(repo->add(anotherUser));

    // Verify users were added correctly
    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 2);

    // Lưu ý: ID có thể được tự động gán nên không nhất thiết phải bằng ID ban đầu
    bool foundFirstUser = false;
    bool foundSecondUser = false;

    for (const auto &user : users)
    {
        if (user.getName() == "John Doe" &&
            user.getAddress() == "123 Main St" &&
            user.getPhone() == "0123456789" &&
            user.getEmail() == "john@example.com")
        {
            foundFirstUser = true;
        }

        if (user.getName() == "Jane Smith" &&
            user.getAddress() == "456 Oak St" &&
            user.getPhone() == "9876543210" &&
            user.getEmail() == "jane@example.com")
        {
            foundSecondUser = true;
        }
    }

    EXPECT_TRUE(foundFirstUser);
    EXPECT_TRUE(foundSecondUser);
}

// Test get user by ID
TEST_F(UserRepositoryTest, GetById)
{
    // Thêm người dùng
    ASSERT_TRUE(repo->add(testUser));

    // Lấy ID của người dùng đã thêm
    auto users = repo->getAll();
    ASSERT_FALSE(users.empty());
    int addedUserId = users[0].getId();

    // Lấy người dùng theo ID
    auto user = repo->getById(addedUserId);
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getName(), testUser.getName());
    EXPECT_EQ(user->getAddress(), testUser.getAddress());
    EXPECT_EQ(user->getPhone(), testUser.getPhone());
    EXPECT_EQ(user->getEmail(), testUser.getEmail());

    // Lấy người dùng không tồn tại
    auto nonExistingUser = repo->getById(999);
    EXPECT_FALSE(nonExistingUser.has_value());
}

// Test get all users
TEST_F(UserRepositoryTest, GetAll)
{
    // Ban đầu không có người dùng nào
    auto initialUsers = repo->getAll();
    EXPECT_TRUE(initialUsers.empty());

    // Thêm một vài người dùng
    ASSERT_TRUE(repo->add(testUser));
    ASSERT_TRUE(repo->add(User(2, "Jane Doe", "456 Oak Ave", "9876543210", "jane@example.com")));

    // Kiểm tra số lượng người dùng
    auto users = repo->getAll();
    ASSERT_EQ(users.size(), 2);
}

// Test update user
TEST_F(UserRepositoryTest, Update)
{
    // Thêm người dùng
    ASSERT_TRUE(repo->add(testUser));

    // Lấy ID của người dùng đã thêm
    auto users = repo->getAll();
    ASSERT_FALSE(users.empty());
    int addedUserId = users[0].getId();

    // Cập nhật người dùng
    User updatedUser(addedUserId, "John Smith", "123 Main St", "0123456789", "john.smith@example.com");
    EXPECT_TRUE(repo->update(updatedUser));

    // Kiểm tra cập nhật
    auto user = repo->getById(addedUserId);
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getName(), "John Smith");
    EXPECT_EQ(user->getEmail(), "john.smith@example.com");

    // Cập nhật người dùng không tồn tại
    User nonExistingUser(999, "Test", "999 Test St", "1234567890", "test@example.com");
    EXPECT_FALSE(repo->update(nonExistingUser));
}

// Test delete user
TEST_F(UserRepositoryTest, Delete)
{
    // Thêm người dùng
    ASSERT_TRUE(repo->add(testUser));

    // Lấy ID của người dùng đã thêm
    auto users = repo->getAll();
    ASSERT_FALSE(users.empty());
    int addedUserId = users[0].getId();

    // Xóa người dùng
    EXPECT_TRUE(repo->remove(addedUserId));

    // Kiểm tra xóa
    users = repo->getAll();
    EXPECT_TRUE(users.empty());

    // Xóa người dùng không tồn tại
    EXPECT_FALSE(repo->remove(999));
}

// Test find by name
TEST_F(UserRepositoryTest, FindByName)
{
    // Thêm một vài người dùng
    ASSERT_TRUE(repo->add(testUser));
    ASSERT_TRUE(repo->add(User(2, "John Smith", "456 Oak Ave", "9876543210", "john.smith@example.com")));
    ASSERT_TRUE(repo->add(User(3, "Jane Doe", "789 Pine St", "5555555555", "jane@example.com")));

    // Tìm người dùng có "John" trong tên
    auto users = repo->findByName("John");
    ASSERT_EQ(users.size(), 2);

    // Tìm người dùng với tên chính xác
    users = repo->findByName("Jane Doe");
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(users[0].getName(), "Jane Doe");

    // Tìm tên không tồn tại
    users = repo->findByName("NonExisting");
    EXPECT_TRUE(users.empty());
}

// Test error handling
TEST_F(UserRepositoryTest, ErrorHandling)
{
    // Kiểm tra các trường hợp đặc biệt
    EXPECT_NO_THROW({
        // Tạo repository với đường dẫn không hợp lệ
        auto invalidDbConnection = DatabaseConnection::getInstance();
        invalidDbConnection->connect("/invalid/path");
        UserRepository invalidRepo(invalidDbConnection);

        // Thêm người dùng vào repository không hợp lệ
        User newUser(2, "Test", "999 Test St", "1234567890", "test@example.com");

        // Thao tác có thể thành công hoặc thất bại tùy thuộc vào OS
        // Chỉ kiểm tra không crash
        invalidRepo.add(newUser);
    });
}