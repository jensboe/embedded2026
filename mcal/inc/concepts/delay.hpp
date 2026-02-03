/**
 * @file delay.hpp
 * @brief Concept for delay implementations.
 *
 */

#pragma once
#include <concepts>
#include <cstdint>
#include <mp-units/systems/si/units.h>
namespace mcal::concepts
{
	using namespace mp_units;
	template <typename T>
	concept Delay = requires(T t, quantity<si::micro<si::second>, u_int32_t> duration) {
		{ T::blocking(duration) } -> std::same_as<void>;
	};

} // namespace mcal::concepts
