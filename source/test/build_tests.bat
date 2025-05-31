@echo off
echo ===================================
echo Building Travel Agency Tests
echo ===================================

REM Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found. Please install CMake and add it to your PATH.
    goto :end
)

REM Check if MinGW is installed
where mingw32-make >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: MinGW not found. Please install MinGW and add it to your PATH.
    goto :end
)

REM Create build directory
if not exist build mkdir build
cd build

echo.
echo Configuring with CMake...
cmake .. -G "MinGW Makefiles"
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed.
    cd ..
    goto :end
)

echo.
echo Building tests...
mingw32-make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    cd ..
    goto :end
)

echo.
echo ===================================
echo Build successful!
echo.
echo To run tests, use: .\travel_agency_tests.exe
echo ===================================

cd ..

:end
pause 