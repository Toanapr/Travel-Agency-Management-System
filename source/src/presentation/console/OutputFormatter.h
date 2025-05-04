#ifndef OUTPUT_FORMATTER_H
#define OUTPUT_FORMATTER_H

#include <string>
#include <vector>
#include <iostream>
#include "../../business/models/User.h"
#include "../../business/models/Trip.h"
#include "../../business/models/Booking.h"

/**
 * @class OutputFormatter
 * @brief Handles the formatting and display of data to the console
 *
 * This class is responsible for formatting and displaying various types of
 * application data to the console in a user-friendly way. It provides consistent
 * formatting for messages, entities, and menus throughout the application.
 */
class OutputFormatter
{
private:
    /**
     * @brief Draw a horizontal line on the console
     * @param width Width of the line in characters
     * @param symbol Character to use for drawing the line
     */
    void drawLine(int width = 80, char symbol = '-') const;

    /**
     * @brief Draw a header with title on the console
     * @param title Text to display in the header
     * @param width Width of the header in characters
     */
    void drawHeader(const std::string &title, int width = 80) const;

    /**
     * @brief Center text on the console
     * @param text Text to center
     * @param width Total width available for centering
     */
    void center(const std::string &text, int width = 80) const;

public:
    /**
     * @brief Default constructor
     */
    OutputFormatter() = default;

    // Display message methods
    /**
     * @brief Display a standard message to the console
     * @param message Text message to display
     */
    void displayMessage(const std::string &message) const;

    /**
     * @brief Display an error message to the console
     * @param message Error message to display
     */
    void displayErrorMessage(const std::string &message) const;

    /**
     * @brief Display a success message to the console
     * @param message Success message to display
     */
    void displaySuccessMessage(const std::string &message) const;

    // Display entity methods
    /**
     * @brief Display a user's details to the console
     * @param user User object to display
     */
    void displayUser(const User &user) const;

    /**
     * @brief Display multiple users' details to the console
     * @param users Vector of User objects to display
     */
    void displayUsers(const std::vector<User> &users) const;

    /**
     * @brief Display a trip's details to the console
     * @param trip Trip object to display
     */
    void displayTrip(const Trip &trip) const;

    /**
     * @brief Display multiple trips' details to the console
     * @param trips Vector of Trip objects to display
     */
    void displayTrips(const std::vector<Trip> &trips) const;

    /**
     * @brief Display a booking's details to the console
     * @param booking Booking object to display
     * @param user User associated with the booking
     * @param trip Trip associated with the booking
     */
    void displayBooking(const Booking &booking, const User &user, const Trip &trip) const;

    /**
     * @brief Display multiple bookings' details to the console
     * @param bookings Vector of Booking objects to display
     * @param users Vector of User objects associated with the bookings
     * @param trips Vector of Trip objects associated with the bookings
     */
    void displayBookings(const std::vector<Booking> &bookings,
                         const std::vector<User> &users,
                         const std::vector<Trip> &trips) const;

    // Display menu methods
    /**
     * @brief Display a menu with options to the console
     * @param title Title of the menu
     * @param options Vector of string options to display
     */
    void displayMenu(const std::string &title, const std::vector<std::string> &options) const;

    // Progress methods
    /**
     * @brief Display a progress indicator on the console
     * @param current Current progress value
     * @param total Total value representing 100% progress
     * @param message Optional message to display with the progress
     */
    void displayProgress(int current, int total, const std::string &message = "") const;

    /**
     * @brief Clear the console screen
     */
    void clearScreen() const;
};

#endif // OUTPUT_FORMATTER_H