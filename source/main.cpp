#include <iostream>
#include "src/Application.h"

int main()
{
    try
    {
        // Get application instance
        Application &app = Application::getInstance();

        // Initialize application
        app.initialize();

        // Run application
        app.run();

        // Shutdown application
        app.shutdown();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error occurred." << std::endl;
        return 1;
    }
}