#include <gtest/gtest.h>
#include "../src/business/models/User.h"

class UserTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up test data
        validId = 1;
        validName = "John Doe";
        validAddress = "123 Main St";
        validPhone = "0123456789";
        validEmail = "john@example.com";
    }

    int validId;
    std::string validName;
    std::string validAddress;
    std::string validPhone;
    std::string validEmail;
};

// Test constructor with valid data
TEST_F(UserTest, ConstructorValidData)
{
    EXPECT_NO_THROW({
        User user(validId, validName, validAddress, validPhone, validEmail);
    });

    User user(validId, validName, validAddress, validPhone, validEmail);
    EXPECT_EQ(user.getId(), validId);
    EXPECT_EQ(user.getName(), validName);
    EXPECT_EQ(user.getAddress(), validAddress);
    EXPECT_EQ(user.getPhone(), validPhone);
    EXPECT_EQ(user.getEmail(), validEmail);
}

// Test constructor with invalid data
TEST_F(UserTest, ConstructorInvalidData)
{
    // All validation is performed before object creation
    User user1(-1, validName, validAddress, validPhone, validEmail);
    EXPECT_EQ(user1.getId(), -1);

    User user2(validId, "", validAddress, validPhone, validEmail);
    EXPECT_EQ(user2.getName(), "");

    User user3(validId, validName, "", validPhone, validEmail);
    EXPECT_EQ(user3.getAddress(), "");

    User user4(validId, validName, validAddress, validPhone, "invalid-email");
    EXPECT_EQ(user4.getEmail(), "invalid-email");

    User user5(validId, validName, validAddress, "abc", validEmail);
    EXPECT_EQ(user5.getPhone(), "abc");
}

// Test getters
TEST_F(UserTest, Getters)
{
    User user(validId, validName, validAddress, validPhone, validEmail);

    EXPECT_EQ(user.getId(), validId);
    EXPECT_EQ(user.getName(), validName);
    EXPECT_EQ(user.getAddress(), validAddress);
    EXPECT_EQ(user.getPhone(), validPhone);
    EXPECT_EQ(user.getEmail(), validEmail);
}

// Test setters
TEST_F(UserTest, Setters)
{
    User user(validId, validName, validAddress, validPhone, validEmail);

    int newId = 2;
    std::string newName = "Jane Doe";
    std::string newAddress = "456 Oak Ave";
    std::string newPhone = "9876543210";
    std::string newEmail = "jane@example.com";

    user.setId(newId);
    user.setName(newName);
    user.setAddress(newAddress);
    user.setPhone(newPhone);
    user.setEmail(newEmail);

    EXPECT_EQ(user.getId(), newId);
    EXPECT_EQ(user.getName(), newName);
    EXPECT_EQ(user.getAddress(), newAddress);
    EXPECT_EQ(user.getPhone(), newPhone);
    EXPECT_EQ(user.getEmail(), newEmail);
}

// Test ID validation
TEST_F(UserTest, IdValidation)
{
    // All validation is performed before object creation
    User user1(0, validName, validAddress, validPhone, validEmail);
    EXPECT_EQ(user1.getId(), 0);

    User user2(-1, validName, validAddress, validPhone, validEmail);
    EXPECT_EQ(user2.getId(), -1);

    User user3(1, validName, validAddress, validPhone, validEmail);
    EXPECT_EQ(user3.getId(), 1);
}