/**
 * @file delay.hpp
 * @brief Concept for delay implementations.
 *
 */

#pragma once
#include <concepts>
#include <cstdint>
namespace mcal::concepts
{
	/**
	 * @brief Delay concept.
	 *
	 * This concept defines the required interface for a delay
	 * implementation. A delay class must provide methods for
	 * millisecond and microsecond delays.
	 *
	 */
	template <typename T>
	concept Delay = requires(T t, uint32_t duration) {
		{ T::ms(duration) } -> std::same_as<void>;
		{ T::µs(duration) } -> std::same_as<void>;
	};
} // namespace mcal::concepts
