/**
 * @file units.hpp
 * @brief Common SI unit and quantity aliases used across the project.
 *
 * This header provides constexpr unit objects and strongly typed quantity
 * aliases based on mp-units 2.0. These definitions are intended to simplify
 * the use of physical units in embedded code while maintaining full type safety.
 *
 */
#pragma once
#include <cstdint>
#include <mp-units/systems/si.h>

namespace utils
{
	/**
	 * @brief SI unit constants used across the project.
	 *
	 * These are mp-units 2.0 unit objects intended for defining quantities.
	 */
	namespace unit
	{
		/** @brief Hertz (frequency). */
		inline constexpr auto Hz = mp_units::si::hertz;

		/** @brief Megahertz (10^6 Hz). */
		inline constexpr auto MHz = mp_units::si::mega<mp_units::si::hertz>;

		/** @brief Second (time). */
		inline constexpr auto s = mp_units::si::second;

		/** @brief Millisecond (10^-3 s). */
		inline constexpr auto ms = mp_units::si::milli<mp_units::si::second>;

		/** @brief Microsecond (10^-6 s). */
		inline constexpr auto us = mp_units::si::micro<mp_units::si::second>;

		/** @brief Volt (electric potential). */
		inline constexpr auto V = mp_units::si::volt;

		/** @brief Millivolt (10^-3 V). */
		inline constexpr auto mV = mp_units::si::milli<mp_units::si::volt>;
	} // namespace unit

	/**
	 * @brief Strongly typed quantity aliases using uint32_t as representation.
	 */
	namespace quantity
	{
		/** @brief Frequency in hertz. */
		using Hz_t = mp_units::quantity<unit::Hz, std::uint32_t>;

		/** @brief Time in seconds. */
		using s_t = mp_units::quantity<unit::s, std::uint32_t>;

		/** @brief Time in microseconds. */
		using us_t = mp_units::quantity<unit::us, std::uint32_t>;

		/** @brief Voltage in millivolt. */
		using mv_t = mp_units::quantity<unit::mV, std::uint32_t>;
	} // namespace quantity
} // namespace utils
