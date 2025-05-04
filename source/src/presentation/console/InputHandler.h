#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include <limits>
#include <iostream>

/**
 * @class InputHandler
 * @brief Handles user input from the console
 *
 * This class is responsible for gathering and validating user input
 * from the console. It provides methods for different types of input
 * with validation and error handling to ensure data integrity.
 */
class InputHandler
{
private:
    /**
     * @brief Clear the input stream after errors
     */
    void clearInputStream();

    /**
     * @brief Validate email format
     * @param email Email address to validate
     * @return true if the email format is valid, false otherwise
     */
    bool validateEmail(const std::string &email);

    /**
     * @brief Validate phone number format
     * @param phone Phone number to validate
     * @return true if the phone number format is valid, false otherwise
     */
    bool validatePhone(const std::string &phone);

    /**
     * @brief Validate date format (YYYY-MM-DD)
     * @param date Date string to validate
     * @return true if the date format is valid, false otherwise
     */
    bool validateDate(const std::string &date);

public:
    /**
     * @brief Default constructor
     */
    InputHandler() = default;

    // Basic input methods
    /**
     * @brief Get integer input from the user
     * @param prompt Text to display before input
     * @param min Minimum acceptable value
     * @param max Maximum acceptable value
     * @return Valid integer within the specified range
     */
    int getIntInput(const std::string &prompt, int min = std::numeric_limits<int>::min(),
                    int max = std::numeric_limits<int>::max());

    /**
     * @brief Get double input from the user
     * @param prompt Text to display before input
     * @param min Minimum acceptable value
     * @param max Maximum acceptable value
     * @return Valid double within the specified range
     */
    double getDoubleInput(const std::string &prompt, double min = std::numeric_limits<double>::min(),
                          double max = std::numeric_limits<double>::max());

    /**
     * @brief Get string input from the user
     * @param prompt Text to display before input
     * @param allowEmpty Whether empty input is acceptable
     * @return User input string
     */
    std::string getStringInput(const std::string &prompt, bool allowEmpty = false);

    // Specific input methods
    /**
     * @brief Get a date input from the user in YYYY-MM-DD format
     * @param prompt Text to display before input
     * @return Valid date string in YYYY-MM-DD format
     */
    std::string getDateInput(const std::string &prompt);

    /**
     * @brief Get a valid email address from the user
     * @param prompt Text to display before input
     * @return Valid email address string
     */
    std::string getEmailInput(const std::string &prompt);

    /**
     * @brief Get a valid phone number from the user
     * @param prompt Text to display before input
     * @return Valid phone number string
     */
    std::string getPhoneInput(const std::string &prompt);

    /**
     * @brief Get a password from the user with optional confirmation
     * @param prompt Text to display before input
     * @param confirmPassword Whether to require password confirmation
     * @return Password string
     */
    std::string getPasswordInput(const std::string &prompt, bool confirmPassword = false);

    // Menu input method
    /**
     * @brief Get a menu choice from the user
     * @param options Vector of menu options to display
     * @return User's chosen option index (1-based)
     */
    int getMenuChoice(const std::vector<std::string> &options);

    // Confirmation methods
    /**
     * @brief Get a yes/no response from the user
     * @param prompt Text to display before input
     * @return true for yes response, false for no response
     */
    bool getYesNoInput(const std::string &prompt);
};

#endif // INPUT_HANDLER_H