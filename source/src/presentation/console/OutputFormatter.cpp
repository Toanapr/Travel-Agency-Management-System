// filepath: f:\TravelAgency\source\src\presentation\console\OutputFormatter.cpp
#include "OutputFormatter.h"
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <sstream>

// Windows-specific headers for color support
#ifdef _WIN32
#include <windows.h>
#ifdef max
#undef max
#endif
#endif

void OutputFormatter::setColor(ConsoleColor color) const
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD colorAttribute = 0;

    switch (color)
    {
    case ConsoleColor::RED:
        colorAttribute = FOREGROUND_RED | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::GREEN:
        colorAttribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::YELLOW:
        colorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::BLUE:
        colorAttribute = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::MAGENTA:
        colorAttribute = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::CYAN:
        colorAttribute = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case ConsoleColor::WHITE:
        colorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    default:
        colorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default white
        break;
    }

    SetConsoleTextAttribute(hConsole, colorAttribute);
#else
    // ANSI color codes for Unix/Linux/macOS terminals
    switch (color)
    {
    case ConsoleColor::RED:
        std::cout << "\033[1;31m"; // Bright red
        break;
    case ConsoleColor::GREEN:
        std::cout << "\033[1;32m"; // Bright green
        break;
    case ConsoleColor::YELLOW:
        std::cout << "\033[1;33m"; // Bright yellow
        break;
    case ConsoleColor::BLUE:
        std::cout << "\033[1;34m"; // Bright blue
        break;
    case ConsoleColor::MAGENTA:
        std::cout << "\033[1;35m"; // Bright magenta
        break;
    case ConsoleColor::CYAN:
        std::cout << "\033[1;36m"; // Bright cyan
        break;
    case ConsoleColor::WHITE:
        std::cout << "\033[1;37m"; // Bright white
        break;
    default:
        std::cout << "\033[0m"; // Reset to default
        break;
    }
#endif
}

void OutputFormatter::resetColor() const
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    std::cout << "\033[0m"; // Reset to default
#endif
}

void OutputFormatter::drawLine(int width, char symbol) const
{
    std::cout << std::string(width, symbol) << std::endl;
}

void OutputFormatter::drawLine(int width, char symbol, ConsoleColor color) const
{
    setColor(color);
    std::cout << std::string(width, symbol) << std::endl;
    resetColor();
}

void OutputFormatter::drawHeader(const std::string &title, int width) const
{
    drawLine(width);
    center(title, width);
    drawLine(width);
}

void OutputFormatter::drawHeader(const std::string &title, int width, ConsoleColor color) const
{
    drawLine(width, '-', color);
    center(title, width, color);
    drawLine(width, '-', color);
}

void OutputFormatter::center(const std::string &text, int width) const
{
    int padding = std::max(0, (width - static_cast<int>(text.length())) / 2);
    std::cout << std::string(padding, ' ') << text << std::endl;
}

void OutputFormatter::center(const std::string &text, int width, ConsoleColor color) const
{
    int padding = std::max(0, (width - static_cast<int>(text.length())) / 2);
    setColor(color);
    std::cout << std::string(padding, ' ') << text << std::endl;
    resetColor();
}

void OutputFormatter::displayMessage(const std::string &message) const
{
    std::cout << message << std::endl;
}

void OutputFormatter::displayMessage(const std::string &message, ConsoleColor color) const
{
    setColor(color);
    std::cout << message << std::endl;
    resetColor();
}

void OutputFormatter::displayErrorMessage(const std::string &message) const
{
    setColor(ConsoleColor::RED);
    std::cout << "ERROR: " << message << std::endl;
    resetColor();
}

void OutputFormatter::displaySuccessMessage(const std::string &message) const
{
    setColor(ConsoleColor::GREEN);
    std::cout << "SUCCESS: " << message << std::endl;
    resetColor();
}

void OutputFormatter::displayWarningMessage(const std::string &message) const
{
    setColor(ConsoleColor::YELLOW);
    std::cout << "WARNING: " << message << std::endl;
    resetColor();
}

void OutputFormatter::displayInfoMessage(const std::string &message) const
{
    setColor(ConsoleColor::BLUE);
    std::cout << "INFO: " << message << std::endl;
    resetColor();
}

void OutputFormatter::displayUser(const User &user) const
{
    drawLine();
    setColor(ConsoleColor::CYAN);
    std::cout << "USER DETAILS" << std::endl;
    resetColor();
    drawLine();

    setColor(ConsoleColor::WHITE);
    std::cout << "ID: ";
    resetColor();
    std::cout << user.getId() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Name: ";
    resetColor();
    std::cout << user.getName() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Address: ";
    resetColor();
    std::cout << user.getAddress() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Phone: ";
    resetColor();
    std::cout << user.getPhone() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Email: ";
    resetColor();
    std::cout << user.getEmail() << std::endl;

    drawLine();
}

void OutputFormatter::displayUsers(const std::vector<User> &users) const
{
    if (users.empty())
    {
        displayWarningMessage("No users found.");
        return;
    }

    drawHeader("USER LIST", 80, ConsoleColor::CYAN);

    // Print table header
    setColor(ConsoleColor::WHITE);
    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "Address"
              << std::setw(15) << "Phone"
              << std::setw(30) << "Email"
              << std::endl;
    resetColor();

    drawLine();

    // Print each user
    for (const auto &user : users)
    {
        std::cout << std::left
                  << std::setw(5) << user.getId()
                  << std::setw(20) << user.getName()
                  << std::setw(20) << user.getAddress()
                  << std::setw(15) << user.getPhone()
                  << std::setw(30) << user.getEmail()
                  << std::endl;
    }

    drawLine();
    setColor(ConsoleColor::YELLOW);
    std::cout << "Total Users: " << users.size() << std::endl;
    resetColor();
}

void OutputFormatter::displayTrip(const Trip &trip) const
{
    drawLine();
    setColor(ConsoleColor::CYAN);
    std::cout << "TRIP DETAILS" << std::endl;
    resetColor();
    drawLine();

    setColor(ConsoleColor::WHITE);
    std::cout << "ID: ";
    resetColor();
    std::cout << trip.getId() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Name: ";
    resetColor();
    std::cout << trip.getName() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Cost: ";
    resetColor();
    std::cout << "$" << std::fixed << std::setprecision(2) << trip.getCost() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Available Seats: ";
    resetColor();
    std::cout << trip.getAvailableSeats() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Start Date: ";
    resetColor();
    std::cout << trip.getStartDate() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "End Date: ";
    resetColor();
    std::cout << trip.getEndDate() << std::endl;

    drawLine();
}

void OutputFormatter::displayTrips(const std::vector<Trip> &trips) const
{
    if (trips.empty())
    {
        displayWarningMessage("No trips found.");
        return;
    }

    drawHeader("TRIP LIST", 100, ConsoleColor::CYAN);

    // Print table header
    setColor(ConsoleColor::WHITE);
    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(35) << "Name"
              << std::setw(10) << "Cost($)"
              << std::setw(15) << "Available"
              << std::setw(15) << "Start Date"
              << std::setw(15) << "End Date"
              << std::endl;
    resetColor();

    drawLine(100);

    // Print each trip
    for (const auto &trip : trips)
    {
        std::cout << std::left
                  << std::setw(5) << trip.getId()
                  << std::setw(35) << trip.getName()
                  << std::setw(10) << std::fixed << std::setprecision(2) << trip.getCost()
                  << std::setw(15) << trip.getAvailableSeats()
                  << std::setw(15) << trip.getStartDate()
                  << std::setw(15) << trip.getEndDate()
                  << std::endl;
    }

    drawLine(100);
    setColor(ConsoleColor::YELLOW);
    std::cout << "Total Trips: " << trips.size() << std::endl;
    resetColor();
}

void OutputFormatter::displayBooking(const Booking &booking, const User &user, const Trip &trip) const
{
    drawLine();
    setColor(ConsoleColor::CYAN);
    std::cout << "BOOKING DETAILS" << std::endl;
    resetColor();
    drawLine();

    setColor(ConsoleColor::WHITE);
    std::cout << "Booking ID: ";
    resetColor();
    std::cout << booking.getId() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Trip: ";
    resetColor();
    std::cout << trip.getName() << " (ID: " << trip.getId() << ")" << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Customer: ";
    resetColor();
    std::cout << user.getName() << " (ID: " << user.getId() << ")" << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Booking Date: ";
    resetColor();
    std::cout << booking.getBookingDate() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Number of People: ";
    resetColor();
    std::cout << booking.getNumberOfPeople() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Total Cost: ";
    resetColor();
    std::cout << "$" << std::fixed << std::setprecision(2) << booking.getTotalCost() << std::endl;

    setColor(ConsoleColor::WHITE);
    std::cout << "Status: ";

    // Color-code the status
    if (booking.getStatus() == "Confirmed")
    {
        setColor(ConsoleColor::GREEN);
    }
    else if (booking.getStatus() == "Pending")
    {
        setColor(ConsoleColor::YELLOW);
    }
    else if (booking.getStatus() == "Cancelled")
    {
        setColor(ConsoleColor::RED);
    }
    else if (booking.getStatus() == "Completed")
    {
        setColor(ConsoleColor::BLUE);
    }

    std::cout << booking.getStatus() << std::endl;
    resetColor();

    drawLine();
}

void OutputFormatter::displayBookings(const std::vector<Booking> &bookings,
                                      const std::vector<User> &users,
                                      const std::vector<Trip> &trips) const
{
    if (bookings.empty())
    {
        displayWarningMessage("No bookings found.");
        return;
    }

    drawHeader("BOOKING LIST", 120, ConsoleColor::CYAN);

    // Print table header
    setColor(ConsoleColor::WHITE);
    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(25) << "Customer"
              << std::setw(35) << "Trip"
              << std::setw(15) << "Date"
              << std::setw(8) << "People"
              << std::setw(12) << "Cost($)"
              << std::setw(15) << "Status"
              << std::endl;
    resetColor();

    drawLine(120);

    // For each booking, find matching user and trip
    for (const auto &booking : bookings)
    {
        // Find user
        std::string userName = "Unknown";
        auto userIt = std::find_if(users.begin(), users.end(),
                                   [&booking](const User &u)
                                   { return u.getId() == booking.getUserId(); });
        if (userIt != users.end())
        {
            userName = userIt->getName();
        }

        // Find trip
        std::string tripName = "Unknown";
        auto tripIt = std::find_if(trips.begin(), trips.end(),
                                   [&booking](const Trip &t)
                                   { return t.getId() == booking.getTripId(); });
        if (tripIt != trips.end())
        {
            tripName = tripIt->getName();
        }

        // Display booking row
        std::cout << std::left
                  << std::setw(5) << booking.getId()
                  << std::setw(25) << userName
                  << std::setw(35) << tripName
                  << std::setw(15) << booking.getBookingDate()
                  << std::setw(8) << booking.getNumberOfPeople()
                  << std::setw(12) << std::fixed << std::setprecision(2) << booking.getTotalCost();

        // Color-code the status
        std::string status = booking.getStatus();
        std::cout << std::setw(0);
        if (status == "Confirmed")
        {
            setColor(ConsoleColor::GREEN);
        }
        else if (status == "Pending")
        {
            setColor(ConsoleColor::YELLOW);
        }
        else if (status == "Cancelled")
        {
            setColor(ConsoleColor::RED);
        }
        else if (status == "Completed")
        {
            setColor(ConsoleColor::BLUE);
        }

        std::cout << std::setw(15) << status;
        resetColor();
        std::cout << std::endl;
    }

    drawLine(120);
    setColor(ConsoleColor::YELLOW);
    std::cout << "Total Bookings: " << bookings.size() << std::endl;
    resetColor();
}

void OutputFormatter::displayMenu(const std::string &title, const std::vector<std::string> &options) const
{
    clearScreen();
    drawHeader(title, 60, ConsoleColor::CYAN);

    for (size_t i = 0; i < options.size(); ++i)
    {
        setColor(ConsoleColor::WHITE);
        std::cout << i + 1 << ". ";
        resetColor();
        std::cout << options[i] << std::endl;
    }

    drawLine(60);
    setColor(ConsoleColor::YELLOW);
    std::cout << "Enter your choice (1-" << options.size() << "): ";
    resetColor();
}

void OutputFormatter::displayProgress(int current, int total, const std::string &message) const
{
    const int barWidth = 50;
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);

    setColor(ConsoleColor::BLUE);
    std::cout << message << " [";

    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
        {
            setColor(ConsoleColor::GREEN);
            std::cout << "=";
        }
        else if (i == pos)
        {
            setColor(ConsoleColor::YELLOW);
            std::cout << ">";
        }
        else
        {
            resetColor();
            std::cout << " ";
        }
    }

    setColor(ConsoleColor::BLUE);
    std::cout << "] ";

    // Set color based on progress
    if (progress < 0.33)
    {
        setColor(ConsoleColor::RED);
    }
    else if (progress < 0.66)
    {
        setColor(ConsoleColor::YELLOW);
    }
    else
    {
        setColor(ConsoleColor::GREEN);
    }

    std::cout << int(progress * 100.0) << "%";

    setColor(ConsoleColor::BLUE);
    std::cout << " (" << current << "/" << total << ")\r";
    std::cout.flush();

    if (current == total)
    {
        std::cout << std::endl;
    }

    resetColor();
}

void OutputFormatter::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}