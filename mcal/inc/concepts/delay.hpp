/**
 * @file delay.hpp
 * @brief Concept definition for delay implementations.
 */

#pragma once

#include <concepts>
#include <cstdint>

#include "mcal.hpp"
#include "units.hpp"

namespace mcal::concepts
{
	/**
	 * @brief Concept for blocking delay providers.
	 *
	 * Requires a static blocking delay function with us resolution.
	 */
	template <typename T>
	concept Delay = requires(utils::quantity::us_t duration) {
		{ T::blocking(duration) } -> std::same_as<void>;
	};

} // namespace mcal::concepts
