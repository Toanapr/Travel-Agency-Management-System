@echo off
echo Building Travel Agency Management System...

REM Create release directory if it doesn't exist
if not exist release mkdir release

REM Check if g++ is available
where g++ >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Using g++ compiler...
    
    REM Compile the project with g++
    g++ -std=c++17 -Wall -Wextra source/main.cpp^
 source/src/Application.cpp^
 source/src/business/models/User.cpp^
 source/src/business/models/Trip.cpp^
 source/src/business/models/Booking.cpp^
 source/src/business/services/UserService.cpp^
 source/src/business/services/TripService.cpp^
 source/src/business/services/BookingService.cpp^
 source/src/data/database/DatabaseConnection.cpp^
 source/src/data/repositories/UserRepository.cpp^
 -Isource/src -o release/TravelAgencySystem.exe
 
    if %ERRORLEVEL% == 0 (
        echo Build successful! Executable is in the release folder.
    ) else (
        echo Build failed! Check compiler errors above.
    )
) else (
    echo g++ compiler not found. Please install a C++ compiler.
)

pause