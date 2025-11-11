cmake_minimum_required(VERSION 3.10.2)

# Statusmeldung
message(STATUS "Catch2 Tests included")

# Executable für Tests (Name z.B. exercise-010-tests)
add_executable(${PROJECT_NAME}-tests
    000-Main.cpp
    001-TestCase.cpp
    ../myvector.cpp              # WICHTIG: Implementierung hinzufügen
)

# Abhängigkeiten (Bibliotheken) hinzufügen
target_link_libraries(${PROJECT_NAME}-tests PRIVATE
    fmt::fmt
    nlohmann_json::nlohmann_json
    Catch2::Catch2WithMain
)

# Catch2 Test als CTest einbinden
add_catch2_test(
    TARGET ${PROJECT_NAME}-tests
)
