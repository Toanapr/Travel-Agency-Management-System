#include "Application.h"
#include <iostream>

// Singleton instance implementation
Application& Application::getInstance() {
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
      _menuHandler(nullptr) {
}

// Initialize components
void Application::initializeDatabase() {
    // Use getInstance() to get the singleton instance
    _dbConnection = DatabaseConnection::getInstance();
    _dbConnection->connect("data/database.csv");
}

void Application::initializeRepositories() {
    // Implementation would create actual repositories
    // For now, we'll just create a UserRepository as a placeholder
    _userRepository = std::make_shared<UserRepository>(_dbConnection);
}

void Application::initializeServices() {
    // Initialize services with repositories
    _userService = std::make_shared<UserService>(_userRepository);
}

void Application::initializeUIComponents() {
    // Initialize UI components
    _inputHandler = std::make_shared<InputHandler>();
    _outputFormatter = std::make_shared<OutputFormatter>();
    // _menuHandler = std::make_shared<MenuHandler>(_inputHandler, _outputFormatter);
}

// Application lifecycle methods
void Application::initialize() {
    std::cout << "Initializing Application..." << std::endl;
    initializeDatabase();
    initializeRepositories();
    initializeServices();
    initializeUIComponents();
    std::cout << "Application initialized successfully." << std::endl;
}

void Application::run() {
    std::cout << "Application is running..." << std::endl;
    // In a real implementation, this would handle the main application loop
    std::cout << "Welcome to the Travel Agency Management System!" << std::endl;
}

void Application::shutdown() {
    std::cout << "Shutting down application..." << std::endl;
    // Clean up resources
    if (_dbConnection) {
        _dbConnection->disconnect();
    }
    _dbConnection = nullptr;
    _userRepository = nullptr;
    _tripRepository = nullptr;
    _bookingRepository = nullptr;
    _userService = nullptr;
    _tripService = nullptr;
    _bookingService = nullptr;
    _inputHandler = nullptr;
    _outputFormatter = nullptr;
    _menuHandler = nullptr;
    std::cout << "Application shut down successfully." << std::endl;
}