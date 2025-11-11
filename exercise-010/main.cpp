#include <fmt/chrono.h>
#include <fmt/format.h>
#include "CLI/CLI.hpp"
#include "config.h"
#include "myvector.hpp"

auto main(int argc, char **argv) -> int
{
    // Create a CLI application object with the project name
    CLI::App app{PROJECT_NAME};

    try
    {
        // Set a version flag for the CLI with version and build date info
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        // Parse the command line arguments
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        // Handle CLI parse errors and exit gracefully
        return app.exit(e);
    }

    // Print welcome message with the application name
    fmt::print("Hello, {}!\n", app.get_name());

    {
        // Create a MyVector object with default constructor (empty vector)
        MyVector vec;
        // Add two elements to the vector
        vec.push_back(42);
        vec.push_back(7);
        // Print the current size and the first element using 'at' (with bounds checking)
        fmt::println("vec.size() = {}", vec.size());
        fmt::println("vec.at(0) = {}", vec.at(0));
    } // 'vec' goes out of scope here and its destructor is called, freeing memory

    // Create a MyVector object with initial size of 5 elements
    MyVector vec2(5);
    // Assign value 99 to the element at index 2 using operator[]
    vec2[2] = 99;
    fmt::println("vec2.size() = {}, vec2[2] = {}", vec2.size(), vec2[2]);
    // Add a new element at the end, causing internal reallocation if needed
    vec2.push_back(123);
    fmt::println("After push_back vec2.size() = {}, back = {}", vec2.size(), vec2[vec2.size()-1]);
    // Clear the vector contents, size becomes zero but capacity remains
    vec2.clear();
    fmt::println("After clear, vec2.size() = {}", vec2.size());

    // Print an ending message
    fmt::println("Hello exercise number 3 after Vector");
    return 0;
}
