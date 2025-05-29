#include "Application.h"
#include <iostream>
#include <filesystem>
#include "data/repositories/UserRepository.h"
#include "data/repositories/TripRepository.h"
#include "data/repositories/BookingRepository.h"
#include "presentation/menu/MenuHandler.h"

// Singleton instance implementation
Application &Application::getInstance()
{
    static Application instance;
    return instance;
}

// Private constructor
Application::Application()
    : _dbConnection(nullptr),
      _userRepository(nullptr),
      _tripRepository(nullptr),
      _bookingRepository(nullptr),
      _userService(nullptr),
      _tripService(nullptr),
      _bookingService(nullptr),
      _inputHandler(nullptr),
      _outputFormatter(nullptr),
      _menuHandler(nullptr)
{
}

// Initialize components
void Application::initializeDatabase()
{
    // Use getInstance() to get the singleton instance
    _dbConnection = DatabaseConnection::getInstance();

    // Always use the data_csv directory in the source folder
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path baseDir;

    // Check if we're in the TravelAgency directory
    if (currentPath.filename() == "TravelAgency")
    {
        baseDir = currentPath;
    }
    else
    {
        // Try to find TravelAgency parent directory
        baseDir = currentPath;
        while (!baseDir.empty() && baseDir.filename() != "TravelAgency")
        {
            baseDir = baseDir.parent_path();
        }

        // If not found, use current directory
        if (baseDir.empty())
        {
            baseDir = currentPath;
        }
    }

    // Always use the source/data_csv directory
    std::filesystem::path dataPath = baseDir / "source" / "data_csv";

    // Create the directory if it doesn't exist
    if (!std::filesystem::exists(dataPath))
    {
        try
        {
            std::filesystem::create_directories(dataPath);

            // Create empty CSV files with headers
            std::ofstream usersFile(dataPath / "users.csv");
            usersFile << "id,name,address,phone,email" << std::endl;
            usersFile.close();

            std::ofstream tripsFile(dataPath / "trips.csv");
            tripsFile << "id,name,destination,startDate,endDate,price,maxParticipants" << std::endl;
            tripsFile.close();

            std::ofstream bookingsFile(dataPath / "bookings.csv");
            bookingsFile << "id,userId,tripId,bookingDate,status,participants" << std::endl;
            bookingsFile.close();

            std::cout << "Created data directory at: " << dataPath.string() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error creating data directory: " << e.what() << std::endl;
        }
    }

    std::cout << "Using data directory: " << dataPath.string() << std::endl;
    _dbConnection->connect(dataPath.string());
}

void Application::initializeRepositories()
{
    // Initialize all repositories with database connection
    _userRepository = std::make_shared<UserRepository>(_dbConnection);
    _tripRepository = std::make_shared<TripRepository>(_dbConnection);
    _bookingRepository = std::make_shared<BookingRepository>(_dbConnection);
}

void Application::initializeServices()
{
    // First initialize BookingService since other services depend on it
    _bookingService = std::make_shared<BookingService>(_bookingRepository, _userRepository, _tripRepository);
    
    // Then initialize UserService and TripService with BookingService
    _userService = std::make_shared<UserService>(_userRepository, _bookingService);
    _tripService = std::make_shared<TripService>(_tripRepository, _bookingService);
}

void Application::initializeUIComponents()
{
    // Initialize UI components
    _outputFormatter = std::make_shared<OutputFormatter>();
    _inputHandler = std::make_shared<InputHandler>(_outputFormatter);
    _menuHandler = std::make_shared<MenuHandler>(_userService, _tripService, _bookingService);
}

// Application lifecycle methods
void Application::initialize()
{
    std::cout << "Initializing Travel Agency Management System..." << std::endl;

    try
    {
        initializeDatabase();
        std::cout << "Database initialized successfully." << std::endl;

        initializeRepositories();
        std::cout << "Repositories initialized successfully." << std::endl;

        initializeServices();
        std::cout << "Services initialized successfully." << std::endl;

        initializeUIComponents();
        std::cout << "UI components initialized successfully." << std::endl;

        std::cout << "Application initialized successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during initialization: " << e.what() << std::endl;
        throw; // Re-throw to allow calling code to handle the exception
    }
}

void Application::run()
{
    try
    {
        // Start the menu system
        if (_menuHandler)
        {
            _menuHandler->start();
        }
        else
        {
            throw std::runtime_error("Menu handler is not initialized");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during application execution: " << e.what() << std::endl;
        shutdown(); // Ensure resources are released properly
    }
}

void Application::shutdown()
{
    std::cout << "Shutting down Travel Agency Management System..." << std::endl;

    // Clean up resources in reverse order of initialization
    _menuHandler = nullptr;
    _inputHandler = nullptr;
    _outputFormatter = nullptr;

    _bookingService = nullptr;
    _tripService = nullptr;
    _userService = nullptr;

    _bookingRepository = nullptr;
    _tripRepository = nullptr;
    _userRepository = nullptr;

    if (_dbConnection)
    {
        _dbConnection->disconnect();
    }
    _dbConnection = nullptr;

    std::cout << "Application shut down successfully." << std::endl;
}