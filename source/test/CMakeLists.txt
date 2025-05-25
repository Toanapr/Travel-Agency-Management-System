cmake_minimum_required(VERSION 3.14)
project(TravelAgencyTests)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add source files
set(SOURCE_FILES
  ../src/business/models/User.cpp
  ../src/business/models/Trip.cpp
  ../src/business/models/Booking.cpp
  ../src/data/repositories/UserRepository.cpp
  ../src/data/repositories/TripRepository.cpp
  ../src/data/repositories/BookingRepository.cpp
  ../src/data/database/DatabaseConnection.cpp
  ../src/business/services/UserService.cpp
  ../src/business/services/TripService.cpp
  ../src/business/services/BookingService.cpp
)

# Add test executable
add_executable(travel_agency_tests
  ${SOURCE_FILES}
  model_tests/user_test.cpp
  model_tests/trip_test.cpp
  model_tests/booking_test.cpp
  repository_tests/user_repository_test.cpp
  repository_tests/trip_repository_test.cpp
  repository_tests/booking_repository_test.cpp
  service_tests/user_service_test.cpp
  service_tests/trip_service_test.cpp
  service_tests/booking_service_test.cpp
)

# Link with GoogleTest
target_link_libraries(travel_agency_tests PRIVATE
  gtest_main
  gmock_main
)

# Include directories
target_include_directories(travel_agency_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/../src
  ${CMAKE_SOURCE_DIR}/../src/business/models
  ${CMAKE_SOURCE_DIR}/../src/business/services
  ${CMAKE_SOURCE_DIR}/../src/data/repositories
  ${CMAKE_SOURCE_DIR}/../src/data/database
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(travel_agency_tests) 