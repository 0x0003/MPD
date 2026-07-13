// SPDX-License-Identifier: BSD-2-Clause
// author: Max Kellermann <max.kellermann@gmail.com>

#ifndef CHRONO_UTIL_HXX
#define CHRONO_UTIL_HXX

#include <chrono>

template<typename Clock, typename Duration>
constexpr bool
IsNegative(const std::chrono::time_point<Clock, Duration> p)
{
	return p < std::chrono::time_point<Clock, Duration>();
}

/**
 * Truncate a time_point to whole seconds.
 * This is needed on Windows where FILETIME has 100ns precision
 * but the database stores mtimes as time_t (seconds).
 */
inline std::chrono::system_clock::time_point
TruncateToSeconds(std::chrono::system_clock::time_point tp)
{
	return std::chrono::floor<std::chrono::seconds>(tp);
}

#endif
