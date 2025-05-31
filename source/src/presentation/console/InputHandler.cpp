// filepath: f:\TravelAgency\source\src\presentation\console\InputHandler.cpp
#include "InputHandler.h"
#include <regex>
#include <iomanip>
#include <algorithm>
#include <memory>

InputHandler::InputHandler() 
    : _outputFormatter(std::make_shared<OutputFormatter>())
{
}

InputHandler::InputHandler(std::shared_ptr<OutputFormatter> outputFormatter)
    : _outputFormatter(outputFormatter ? outputFormatter : std::make_shared<OutputFormatter>())
{
}

void InputHandler::clearInputStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool InputHandler::validateEmail(const std::string &email)
{
    // Basic email validation using regex
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool InputHandler::validatePhone(const std::string &phone)
{
    // Allow Vietnam phone number formats:
    // +84xxxxxxxxx (international format with country code)
    // 0xxxxxxxxx (domestic format with leading zero)
    // Must be 10 or 11 digits total including leading 0 or country code
    const std::regex pattern(R"(((\+84|0)([0-9]{9}|[0-9]{8}))|((\+84[-\s]|0[-\s])([0-9]{3}[-\s][0-9]{3}[-\s][0-9]{3}|[0-9]{2}[-\s][0-9]{3}[-\s][0-9]{3})))");
    return std::regex_match(phone, pattern);
}

bool InputHandler::validateDate(const std::string &date)
{
    // Check format DD-MM-YYYY
    const std::regex pattern(R"(\d{2}-\d{2}-\d{4})");
    if (!std::regex_match(date, pattern))
    {
        return false;
    }

    // Extract day, month, and year
    int day, month, year;
    sscanf(date.c_str(), "%d-%d-%d", &day, &month, &year);

    // Check valid month
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Check valid day based on month
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap year
    int maxDays = daysInMonth[month];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    {
        maxDays = 29;
    }

    if (day < 1 || day > maxDays)
    {
        return false;
    }

    return true;
}

int InputHandler::getIntInput(const std::string &prompt, int min, int max)
{
    int value;
    bool validInput = false;
    std::string inputStr;

    do
    {
        std::cout << prompt;
        std::getline(std::cin, inputStr);
        
        // Remove leading and trailing whitespace
        inputStr.erase(0, inputStr.find_first_not_of(" \t\r\n"));
        inputStr.erase(inputStr.find_last_not_of(" \t\r\n") + 1);
        
        // Check if the string is empty
        if (inputStr.empty()) {
            _outputFormatter->displayErrorMessage("Input cannot be empty. Please enter a valid number.");
            continue;
        }
        
        // Check if the string contains only digits
        bool isValid = true;
        for (char c : inputStr) {
            if (!std::isdigit(c)) {
                isValid = false;
                break;
            }
        }
          if (!isValid) {
            _outputFormatter->displayErrorMessage("Please enter a valid whole number without decimals or other characters.");
            continue;
        }
          // Convert to integer
        try {
            value = std::stoi(inputStr);
            
            // Check range
            if (value < min || value > max) {
                _outputFormatter->displayErrorMessage("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max) + ".");
            }
            else {
                validInput = true;
            }
        }        catch (const std::exception& e) {
            _outputFormatter->displayErrorMessage("Input value is too large or invalid. Please enter a valid number.");
        }
        
    } while (!validInput);

    return value;
}

double InputHandler::getDoubleInput(const std::string &prompt, double min, double max)
{
    double value;
    bool validInput = false;
    std::string inputStr;

    do
    {
        std::cout << prompt;
        std::getline(std::cin, inputStr);
        
        // Remove leading and trailing whitespace
        inputStr.erase(0, inputStr.find_first_not_of(" \t\r\n"));
        inputStr.erase(inputStr.find_last_not_of(" \t\r\n") + 1);
        
        // Check if the string is empty
        if (inputStr.empty()) {
            _outputFormatter->displayErrorMessage("Input cannot be empty. Please enter a valid number.");
            continue;
        }
        
        // Check if the string contains valid characters for a double
        bool isValid = true;
        bool hasDecimalPoint = false;
        
        // Allow a minus sign at the beginning
        size_t startPos = (inputStr[0] == '-') ? 1 : 0;
        
        for (size_t i = startPos; i < inputStr.length(); i++) {
            if (inputStr[i] == '.' || inputStr[i] == ',') {
                // Only one decimal point is allowed
                if (hasDecimalPoint) {
                    isValid = false;
                    break;
                }
                hasDecimalPoint = true;
            }
            else if (!std::isdigit(inputStr[i])) {
                isValid = false;
                break;
            }
        }
          if (!isValid) {
            _outputFormatter->displayErrorMessage("Please enter a valid number.");
            continue;
        }
        
        // Replace comma with dot if present
        std::replace(inputStr.begin(), inputStr.end(), ',', '.');
          // Convert to double
        try {
            value = std::stod(inputStr);
            
            // Check range
            if (value < min || value > max) {
                _outputFormatter->displayErrorMessage("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max) + ".");
            }
            else {
                validInput = true;
            }
        }
        catch (const std::exception& e) {
            _outputFormatter->displayErrorMessage("Input value is invalid. Please enter a valid number.");
        }
        
    } while (!validInput);

    return value;
}

std::string InputHandler::getStringInput(const std::string &prompt, bool allowEmpty)
{
    std::string input;
    bool validInput = false;    do
    {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty() && !allowEmpty)
        {
            _outputFormatter->displayErrorMessage("Input cannot be empty. Please try again.");
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    return input;
}

std::string InputHandler::getDateInput(const std::string &prompt)
{
    std::string date;
    bool validInput = false;    do
    {
        std::cout << prompt << " (Format: DD-MM-YYYY): ";
        std::getline(std::cin, date);

        if (!validateDate(date))
        {
            _outputFormatter->displayErrorMessage("Invalid date format or date. Please use DD-MM-YYYY format.");
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    return date;
}

std::string InputHandler::getEmailInput(const std::string &prompt)
{
    std::string email;
    bool validInput = false;    do
    {
        std::cout << prompt;
        std::getline(std::cin, email);

        if (!validateEmail(email))
        {
            _outputFormatter->displayErrorMessage("Invalid email format. Please try again.");
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    return email;
}

std::string InputHandler::getPhoneInput(const std::string &prompt)
{
    std::string phone;
    bool validInput = false;    do
    {
        std::cout << prompt;
        std::getline(std::cin, phone);

        if (!validatePhone(phone))
        {
            _outputFormatter->displayErrorMessage("Invalid phone number format. Please enter a valid Vietnamese phone number.");
            std::cout << "       Valid formats: +84xxxxxxxxx, 0xxxxxxxxx, +84-xxx-xxx-xxx, 0-xxx-xxx-xxx" << std::endl;
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    return phone;
}

std::string InputHandler::getPasswordInput(const std::string &prompt, bool confirmPassword)
{
    std::string password, confirmPwd;
    bool validInput = false;

    do
    {
        std::cout << prompt;
        // In a real application, you would use platform-specific code to hide password input
        std::getline(std::cin, password);        if (password.empty())
        {
            _outputFormatter->displayErrorMessage("Password cannot be empty. Please try again.");
            continue;
        }

        if (confirmPassword)
        {
            std::cout << "Confirm password: ";
            std::getline(std::cin, confirmPwd);

            if (password != confirmPwd)
            {
                _outputFormatter->displayErrorMessage("Passwords do not match. Please try again.");
                continue;
            }
        }

        validInput = true;
    } while (!validInput);

    return password;
}

int InputHandler::getMenuChoice(const std::vector<std::string> &options)
{
    // Display menu options
    std::cout << "\nMenu Options:" << std::endl;
    for (size_t i = 0; i < options.size(); ++i)
    {
        std::cout << (i + 1) << ". " << options[i] << std::endl;
    }
    std::cout << std::endl;

    // Get user choice
    return getIntInput("Enter your choice (1-" + std::to_string(options.size()) + "): ", 1, static_cast<int>(options.size()));
}

bool InputHandler::getYesNoInput(const std::string &prompt)
{
    std::string input;
    bool validInput = false;

    do
    {
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, input);
          // Remove leading and trailing whitespace
        input.erase(0, input.find_first_not_of(" \t\r\n"));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);
        
        // Check if the input is exactly "y" or "n" (case sensitive)
        if (input == "y" || input == "n")
        {
            validInput = true;
        }
        else
        {
            _outputFormatter->displayErrorMessage("Please enter exactly 'y' for yes or 'n' for no.");
        }
    } while (!validInput);

    return (input == "y");
}