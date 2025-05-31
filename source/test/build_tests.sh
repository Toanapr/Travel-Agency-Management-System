#!/bin/bash

echo "==================================="
echo "Building Travel Agency Tests"
echo "==================================="

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake not found. Please install CMake."
    exit 1
fi

# Check if make is installed
if ! command -v make &> /dev/null; then
    echo "ERROR: make not found. Please install build tools."
    exit 1
fi

# Create build directory
mkdir -p build
cd build

echo
echo "Configuring with CMake..."
cmake ..
if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed."
    cd ..
    exit 1
fi

echo
echo "Building tests..."
make
if [ $? -ne 0 ]; then
    echo "ERROR: Build failed."
    cd ..
    exit 1
fi

echo
echo "==================================="
echo "Build successful!"
echo
echo "To run tests, use: ./travel_agency_tests"
echo "==================================="

cd .. 