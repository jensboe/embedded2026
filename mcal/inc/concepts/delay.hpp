/**
 * @file delay.hpp
 * @brief Concept definition for delay implementations.
 */

#pragma once

#include <concepts>
#include <cstdint>

#include <mp-units/systems/si.h>

namespace mcal::concepts
{
	/**
	 * @brief Shorthand for microsecond duration.
	 *
	 */
	using microseconds_t = mp_units::quantity<mp_units::si::micro<mp_units::si::second>, std::uint32_t>;

	/**
	 * @brief Concept for blocking delay providers.
	 *
	 * Requires a static blocking delay function with microsecond resolution.
	 */
	template <typename T>
	concept Delay = requires(microseconds_t duration) {
		{ T::blocking(duration) } -> std::same_as<void>;
	};

} // namespace mcal::concepts
