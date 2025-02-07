/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QTime.hpp"
#include "okapi/api/units/RQuantity.hpp"

namespace okapi {
QUANTITY_TYPE(0, 1, -1, 0, QSpeed)

constexpr QSpeed mps = meter / second;
constexpr QSpeed miph = mile / hour;
constexpr QSpeed kmph = kilometer / hour;
constexpr QSpeed tps = tile / second; // added tile per second
constexpr QSpeed fps = foot / second; // added ft per second

inline namespace literals {
constexpr QSpeed operator"" _mps(long double x) {
  return static_cast<double>(x) * mps;
}
constexpr QSpeed operator"" _miph(long double x) {
  return static_cast<double>(x) * mile / hour;
}
constexpr QSpeed operator"" _kmph(long double x) {
  return static_cast<double>(x) * kilometer / hour;
}

constexpr QSpeed operator"" _tps (long double x) {
  return static_cast<double>(x) * tps;
}

constexpr QSpeed operator"" _fps (long double x) {
  return static_cast<double>(x) * fps;
}

constexpr QSpeed operator"" _mps(unsigned long long int x) {
  return static_cast<double>(x) * mps;
}
constexpr QSpeed operator"" _miph(unsigned long long int x) {
  return static_cast<double>(x) * mile / hour;
}
constexpr QSpeed operator"" _kmph(unsigned long long int x) {
  return static_cast<double>(x) * kilometer / hour;
}

constexpr QSpeed operator"" _tps (unsigned long long int x) {
  return static_cast<double>(x) * tps;
}

constexpr QSpeed operator"" _fps (unsigned long long int x) {
  return static_cast<double>(x) * fps;
}
} // namespace literals
} // namespace okapi
