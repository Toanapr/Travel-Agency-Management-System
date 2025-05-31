# Travel Agency Management System - Test Suite

This directory contains the test suite for the Travel Agency Management System. The tests are implemented using Google Test framework and cover models, repositories, and services.

## Directory Structure

- `model_tests/` - Tests for business models (User, Trip, Booking)
- `repository_tests/` - Tests for data repositories
- `service_tests/` - Tests for business services
- `build/` - Build directory (created during build process)
- `CMakeLists.txt` - CMake configuration for building tests
- `build_tests.bat` - Windows build script
- `build_tests.sh` - Linux/Mac build script
- `TEST_PLAN.md` - Comprehensive test plan

## Requirements

- CMake (version 3.14 or higher)
- C++ compiler with C++17 support
  - Windows: MinGW or Visual Studio
  - Linux/Mac: GCC or Clang
- Internet connection (for first build to download Google Test)

## Building Tests

### Windows

1. Open command prompt
2. Navigate to this directory
3. Run `build_tests.bat`

### Linux/Mac

1. Open terminal
2. Navigate to this directory
3. Make the script executable: `chmod +x build_tests.sh`
4. Run `./build_tests.sh`

## Running Tests

After a successful build:

### Windows

```
cd build
.\travel_agency_tests.exe
```

### Linux/Mac

```
cd build
./travel_agency_tests
```

## Test Categories

### Model Tests

These tests verify the functionality of the business model classes:
- User
- Trip
- Booking

### Repository Tests

These tests verify the data access layer:
- UserRepository
- TripRepository
- BookingRepository

### Service Tests

These tests verify the business logic layer:
- UserService
- TripService
- BookingService

## Manual Testing

Some features require manual testing, as described in the TEST_PLAN.md file. These include:

1. UI/UX functionality
2. End-to-end workflows
3. Integration between components

## Adding New Tests

To add new tests:
1. Create a new test file in the appropriate directory
2. Add the file to `CMakeLists.txt`
3. Rebuild the test suite

For more details, refer to the TEST_PLAN.md file.

## Test Structure

The tests are organized into three main categories:

### Model Tests (`model_tests/`)
- **user_test.cpp**: Tests for User model validation, constructors, getters/setters
- **trip_test.cpp**: Tests for Trip model validation, cost/seat validation, date validation  
- **booking_test.cpp**: Tests for Booking model validation, status validation, cost calculation

### Repository Tests (`repository_tests/`)
- **user_repository_test.cpp**: CRUD operations, search functionality, CSV file handling
- **trip_repository_test.cpp**: CRUD operations, search functionality, CSV file handling
- **booking_repository_test.cpp**: CRUD operations, search by user/trip ID, CSV file handling

### Service Tests (`service_tests/`)
- **user_service_test.cpp**: Business logic validation using mocks, user management operations
- **trip_service_test.cpp**: Business logic validation using mocks, trip management, availability checking
- **booking_service_test.cpp**: Booking creation logic, cost calculation, status management

## Test Coverage

The tests cover the following scenarios:

### Model Validation
- Constructor parameter validation
- Getter/setter functionality
- Data type validation (strings, numbers, dates)
- Business rule validation (positive costs, valid dates, etc.)

### Repository Operations
- CRUD operations (Create, Read, Update, Delete)
- Search functionality (by ID, name, user ID, trip ID)
- CSV file handling and persistence
- Error handling for invalid file paths and permissions

### Service Logic
- Business rule enforcement
- Integration between models and repositories
- Mock-based testing for isolated unit tests
- Edge case handling

### Error Handling
- Invalid input validation
- File system error handling
- Resource management
- Exception safety

## Test Data

Tests use temporary directories and CSV files that are automatically created and cleaned up:
- `test_data/users.csv`
- `test_data/trips.csv`  
- `test_data/bookings.csv`

## Notes

- All tests use CSV files for data persistence (no database required)
- Date format used: dd-mm-yyyy
- Repository constructors accept file paths as strings
- Service tests use Google Mock for repository mocking
- Tests are designed to be independent and can run in any order 