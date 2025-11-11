// point_fmt.hpp
#pragma once

#include "point.hpp"
#include <fmt/core.h>

/**
 * @brief fmt formatter specialization for Point<T>
 * Allows using Point with fmt::print, fmt::format, etc.
 * 
 * Usage:
 *   Point<int> p{1, 2};
 *   fmt::print("{}", p);  // Output: (1, 2)
 */
template <typename T>
struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};
