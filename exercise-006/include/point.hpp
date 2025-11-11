// point.hpp
#pragma once

#include <type_traits>
#include <cmath>
#include <utility>

/**
 * @brief Generic Point class template for arithmetic types
 * @tparam T Arithmetic type (int, float, double, etc.)
 */
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

  /**
   * @brief Move the point by dx and dy
   * @param dx Delta x
   * @param dy Delta y
   */
  void move(T dx, T dy) {
    x += dx;
    y += dy;
  }

  // Return type for distance calculation
  // Uses common_type to handle mixed arithmetic types safely
  using dist_t = std::common_type_t<T, double>;

  /**
   * @brief Calculate Euclidean distance to another point
   * @param other The other point
   * @return Distance as common_type of T and double
   */
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

  // Point addition
  Point operator+(const Point& rhs) const {
    return Point{x + rhs.x, y + rhs.y};
  }

  // Point subtraction
  Point operator-(const Point& rhs) const {
    return Point{x - rhs.x, y - rhs.y};
  }

  /**
   * @brief Scalar multiplication with type promotion
   * @tparam U Type of scalar
   * @param scalar Scalar value to multiply with
   * @return New point with promoted type
   */
  template <typename U>
  auto operator*(U scalar) const -> Point<std::common_type_t<T, U>> {
    using result_t = std::common_type_t<T, U>;
    return Point<result_t>{
      static_cast<result_t>(x) * static_cast<result_t>(scalar),
      static_cast<result_t>(y) * static_cast<result_t>(scalar)
    };
  }
};
