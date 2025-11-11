#include <fmt/chrono.h>
#include <fmt/format.h>
#include "CLI/CLI.hpp"
#include "config.h"
#include "myvector.hpp"

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    fmt::print("Hello, {}!\n", app.get_name());

    {
        MyVector vec;
        vec.push_back(42);
        vec.push_back(7);
        fmt::println("vec.size() = {}", vec.size());
        fmt::println("vec.at(0) = {}", vec.at(0));
    }

    MyVector vec2(5);
    vec2[2] = 99;
    fmt::println("vec2.size() = {}, vec2[2] = {}", vec2.size(), vec2[2]);
    vec2.push_back(123);
    fmt::println("After push_back vec2.size() = {}, back = {}", vec2.size(), vec2[vec2.size()-1]);
    vec2.clear();
    fmt::println("After clear, vec2.size() = {}", vec2.size());

    fmt::println("Hello exercise number 3 after Vector");
    return 0;
}
