#include <iostream>
#include "src/Application.h"

int main()
{
    try
    {
        Application &app = Application::getInstance();
        app.initialize();
        app.run();
        app.shutdown();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Application terminated with error: " << e.what() << std::endl;
        return 1;
    }
}