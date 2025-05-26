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
 source/src/data/database/QueryBuilder.cpp^
 source/src/data/repositories/UserRepository.cpp^
 source/src/data/repositories/TripRepository.cpp^
 source/src/data/repositories/BookingRepository.cpp^
 source/src/data/dto/UserDTO.cpp^
 source/src/data/dto/TripDTO.cpp^
 source/src/data/dto/BookingDTO.cpp^
 source/src/presentation/console/InputHandler.cpp^
 source/src/presentation/console/OutputFormatter.cpp^
 source/src/presentation/menu/MainMenu.cpp^
 source/src/presentation/menu/UserMenu.cpp^
 source/src/presentation/menu/TripMenu.cpp^
 source/src/presentation/menu/BookingMenu.cpp^
 source/src/presentation/menu/MenuHandler.cpp^
 source/src/presentation/view/UserView.cpp^
 source/src/presentation/view/TripView.cpp^
 source/src/presentation/view/BookingView.cpp^
 -Isource/src -o release/TravelAgencySystem.exe
 
    if %ERRORLEVEL% == 0 (
        echo Build successful! Executable is in the release folder.
        echo Running application...
        cd release
        TravelAgencySystem.exe
    ) else (
        echo Build failed! Check compiler errors above.
    )
) else (
    echo g++ compiler not found. Please install a C++ compiler.
)

pause