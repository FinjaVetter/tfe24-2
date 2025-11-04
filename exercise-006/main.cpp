#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>

#include "CLI/CLI.hpp"
#include "config.h"

#include <type_traits>
#include <cmath>
#include <utility>

// for convenience
using json = nlohmann::json;

// ============================================================================
// Point Template Class Definition
// ============================================================================

// Generic Point class template for arithmetic types
template <typename T>
class Point {
  // Ensure T is an arithmetic type (int, float, double, etc.)
  static_assert(std::is_arithmetic<T>::value, 
                "Point<T>: T must be an arithmetic type");

public:
  // Member variables
  T x{};
  T y{};

  // Default constructor: initializes x and y to T{}
  Point() = default;

  // Value constructor: initializes with given coordinates
  Point(T x_, T y_) : x{x_}, y{y_} {}

  // Move the point by dx and dy
  void move(T dx, T dy) {
    x += dx;
    y += dy;
  }

  // Return type for distance calculation
  // Uses common_type to handle mixed arithmetic types safely
  using dist_t = std::common_type_t<T, double>;

  // Calculate Euclidean distance to another point
  auto distance_to(const Point& other) const -> dist_t {
    // Cast to wider type before subtraction to avoid overflow
    const auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
    const auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
    // Use std::hypot for numerical stability
    return std::hypot(dx, dy);
  }

  // Equality comparison
  bool operator==(const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  // Inequality comparison
  bool operator!=(const Point& rhs) const {
    return !(*this == rhs);
  }

  // Optional: Point addition
  Point operator+(const Point& rhs) const {
    return Point{x + rhs.x, y + rhs.y};
  }

  // Optional: Point subtraction
  Point operator-(const Point& rhs) const {
    return Point{x - rhs.x, y - rhs.y};
  }

  // Optional: Scalar multiplication with type promotion
  template <typename U>
  auto operator*(U scalar) const -> Point<std::common_type_t<T, U>> {
    using result_t = std::common_type_t<T, U>;
    return Point<result_t>{
      static_cast<result_t>(x) * static_cast<result_t>(scalar),
      static_cast<result_t>(y) * static_cast<result_t>(scalar)
    };
  }
};

// ============================================================================
// fmt Formatter Specialization
// ============================================================================

// fmt formatter specialization for Point<T>
// Allows using Point with fmt::print, fmt::format, etc.
template <typename T>
struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
  // Format the point as "(x, y)"
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};

// ============================================================================
// Main Function
// ============================================================================

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    
    // Subcommand for distance calculation
    auto* dist_cmd = app.add_subcommand("distance", "Calculate distance between two points");
    int x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    dist_cmd->add_option("-x,--x1", x1, "X coordinate of first point")->required();
    dist_cmd->add_option("-y,--y1", y1, "Y coordinate of first point")->required();
    dist_cmd->add_option("--x2", x2, "X coordinate of second point")->required();
    dist_cmd->add_option("--y2", y2, "Y coordinate of second point")->required();
    
    // Subcommand for move operation
    auto* move_cmd = app.add_subcommand("move", "Move a point");
    int px = 0, py = 0, dx = 1, dy = 1;
    move_cmd->add_option("-x", px, "Initial X coordinate")->required();
    move_cmd->add_option("-y", py, "Initial Y coordinate")->required();
    move_cmd->add_option("--dx", dx, "Delta X")->required();
    move_cmd->add_option("--dy", dy, "Delta Y")->required();
    
    // Subcommand for arithmetic operations
    auto* arith_cmd = app.add_subcommand("arithmetic", "Perform arithmetic operations on points");
    int ax = 10, ay = 20, bx = 3, by = 7;
    double scalar = 2.5;
    arith_cmd->add_option("--ax", ax, "X coordinate of point A")->default_val(10);
    arith_cmd->add_option("--ay", ay, "Y coordinate of point A")->default_val(20);
    arith_cmd->add_option("--bx", bx, "X coordinate of point B")->default_val(3);
    arith_cmd->add_option("--by", by, "Y coordinate of point B")->default_val(7);
    arith_cmd->add_option("-s,--scalar", scalar, "Scalar for multiplication")->default_val(2.5);
    
    // Subcommand for full demo
    auto* demo_cmd = app.add_subcommand("demo", "Run full demonstration of all Point<T> features");
    
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.require_subcommand(0, 1); // Allow 0 or 1 subcommand
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("=================================\n");
    
    // Handle distance subcommand
    if (dist_cmd->parsed()) {
        fmt::print("Distance Calculation\n");
        fmt::print("=================================\n\n");
        
        Point<int> p1{x1, y1};
        Point<int> p2{x2, y2};
        
        fmt::print("Point 1: {}\n", p1);
        fmt::print("Point 2: {}\n", p2);
        fmt::print("Distance: {:.6f}\n\n", p1.distance_to(p2));
        
        // JSON output
        json j;
        j["point1"] = {{"x", p1.x}, {"y", p1.y}};
        j["point2"] = {{"x", p2.x}, {"y", p2.y}};
        j["distance"] = p1.distance_to(p2);
        fmt::print("JSON output:\n{}\n", j.dump(2));
        
        return 0;
    }
    
    // Handle move subcommand
    if (move_cmd->parsed()) {
        fmt::print("Move Operation\n");
        fmt::print("=================================\n\n");
        
        Point<int> p{px, py};
        fmt::print("Initial point: {}\n", p);
        fmt::print("Moving by: ({}, {})\n", dx, dy);
        
        p.move(dx, dy);
        fmt::print("Result: {}\n\n", p);
        
        // JSON output
        json j;
        j["initial"] = {{"x", px}, {"y", py}};
        j["delta"] = {{"dx", dx}, {"dy", dy}};
        j["result"] = {{"x", p.x}, {"y", p.y}};
        fmt::print("JSON output:\n{}\n", j.dump(2));
        
        return 0;
    }
    
    // Handle arithmetic subcommand
    if (arith_cmd->parsed()) {
        fmt::print("Arithmetic Operations\n");
        fmt::print("=================================\n\n");
        
        Point<int> pa{ax, ay};
        Point<int> pb{bx, by};
        
        fmt::print("Point A: {}\n", pa);
        fmt::print("Point B: {}\n", pb);
        fmt::print("\nOperations:\n");
        fmt::print("  A + B = {}\n", pa + pb);
        fmt::print("  A - B = {}\n", pa - pb);
        
        auto scaled = pa * scalar;
        fmt::print("  A * {:.2f} = {}\n\n", scalar, scaled);
        
        // JSON output
        json j;
        j["pointA"] = {{"x", pa.x}, {"y", pa.y}};
        j["pointB"] = {{"x", pb.x}, {"y", pb.y}};
        j["addition"] = {{"x", (pa + pb).x}, {"y", (pa + pb).y}};
        j["subtraction"] = {{"x", (pa - pb).x}, {"y", (pa - pb).y}};
        j["scalar_multiplication"] = {
            {"scalar", scalar},
            {"result", {{"x", scaled.x}, {"y", scaled.y}}}
        };
        fmt::print("JSON output:\n{}\n", j.dump(2));
        
        return 0;
    }
    
    // Default behavior: run full demo if no subcommand was used
    fmt::print("Point<T> Template Class Demo\n");
    fmt::print("=================================\n\n");

    /* INSERT YOUR CODE HERE */
    
    // 1. Create points with integer coordinates
    fmt::print("1. Integer Points:\n");
    Point<int> p1{0, 0};
    Point<int> p2{3, 4};
    
    fmt::print("   Point p1: {}\n", p1);
    fmt::print("   Point p2: {}\n", p2);
    fmt::print("   Distance: {:.6f}\n\n", p1.distance_to(p2));
    
    // 2. Create points with double coordinates
    fmt::print("2. Double Points:\n");
    Point<double> p3{1.5, 2.5};
    Point<double> p4{4.5, 6.5};
    
    fmt::print("   Point p3: {}\n", p3);
    fmt::print("   Point p4: {}\n", p4);
    fmt::print("   Distance: {:.6f}\n\n", p3.distance_to(p4));
    
    // 3. Move operations
    fmt::print("3. Move Operations:\n");
    Point<int> moving{0, 0};
    fmt::print("   Before move: {}\n", moving);
    moving.move(5, -2);
    fmt::print("   After move(5, -2): {}\n", moving);
    fmt::print("   Distance to p2: {:.6f}\n\n", moving.distance_to(p2));
    
    // 4. Equality comparison
    fmt::print("4. Equality Tests:\n");
    Point<int> p5{3, 4};
    Point<int> p6{3, 4};
    Point<int> p7{5, 6};
    
    fmt::print("   p5 {} == p6 {} : {}\n", p5, p6, p5 == p6);
    fmt::print("   p5 {} == p7 {} : {}\n", p5, p7, p5 == p7);
    fmt::print("   p5 {} != p7 {} : {}\n\n", p5, p7, p5 != p7);
    
    // 5. Arithmetic operations (optional operators)
    fmt::print("5. Arithmetic Operations:\n");
    Point<int> pa{10, 20};
    Point<int> pb{3, 7};
    
    fmt::print("   pa: {}\n", pa);
    fmt::print("   pb: {}\n", pb);
    fmt::print("   pa + pb = {}\n", pa + pb);
    fmt::print("   pa - pb = {}\n", pa - pb);
    
    auto scaled = pa * 2.5;
    fmt::print("   pa * 2.5 = {}\n\n", scaled);
    
    // 6. Edge case: Large values
    fmt::print("6. Edge Case - Large Values:\n");
    Point<int> large1{1000000, 1000000};
    Point<int> large2{-1000000, -1000000};
    fmt::print("   Point 1: {}\n", large1);
    fmt::print("   Point 2: {}\n", large2);
    fmt::print("   Distance: {:.6f}\n\n", large1.distance_to(large2));
    
    // 7. Multiple consecutive moves
    fmt::print("7. Stability Test - 100 Consecutive Moves:\n");
    Point<int> stable{0, 0};
    fmt::print("   Start: {}\n", stable);
    for (int i = 0; i < 100; ++i) {
        stable.move(1, 1);
    }
    fmt::print("   After 100 moves(1,1): {}\n\n", stable);
    
    // 8. Type safety demonstration
    fmt::print("8. Type Safety:\n");
    Point<int> pi{5, 10};
    Point<double> pd{5.5, 10.5};
    fmt::print("   Integer point: {}\n", pi);
    fmt::print("   Double point: {}\n", pd);
    fmt::print("   Note: Cannot mix types directly (compile-time safety)\n\n");
    
    // 9. Zero distance edge case
    fmt::print("9. Edge Case - Zero Distance:\n");
    Point<int> same1{7, 9};
    Point<int> same2{7, 9};
    fmt::print("   Point 1: {}\n", same1);
    fmt::print("   Point 2: {}\n", same2);
    fmt::print("   Distance: {:.6f}\n", same1.distance_to(same2));
    fmt::print("   Are equal: {}\n\n", same1 == same2);
    
    // 10. JSON integration example
    fmt::print("10. JSON Integration:\n");
    json j;
    j["points"] = json::array();
    j["points"].push_back({{"name", "origin"}, {"x", p1.x}, {"y", p1.y}});
    j["points"].push_back({{"name", "target"}, {"x", p2.x}, {"y", p2.y}});
    j["operations"] = {
        {"distance", p1.distance_to(p2)},
        {"sum", {{"x", (p1 + p2).x}, {"y", (p1 + p2).y}}},
        {"difference", {{"x", (p2 - p1).x}, {"y", (p2 - p1).y}}}
    };
    
    fmt::print("   JSON output:\n{}\n\n", j.dump(2));
    
    fmt::print("=================================\n");
    fmt::print("All Point<T> operations completed successfully!\n");
    fmt::print("=================================\n\n");
    fmt::print("Try these commands:\n");
    fmt::print("  {} distance --x1 0 --y1 0 --x2 3 --y2 4\n", app.get_name());
    fmt::print("  {} move -x 10 -y 20 --dx 5 --dy -3\n", app.get_name());
    fmt::print("  {} arithmetic --ax 10 --ay 20 --bx 3 --by 7 -s 2.5\n", app.get_name());
    fmt::print("  {} demo\n", app.get_name());

    return 0; /* exit gracefully*/
}
