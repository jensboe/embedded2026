/**
 * @file mcal.hpp
 * @brief Main include file for mcal.
 */

#pragma once
#include "concepts/concepts.hpp"
/**
 * @brief Home of the Microcontroller Abstraction Layer.
 *
 */
namespace mcal
{
	/**
	 * @brief Common defintion of a clock source type
	 *
	 */
	struct clock
	{
		/**
		 * @brief Sources
		 *
		 */
		enum class sources
		{
			none = 0, //!< Dummy, not existing
			crystal,  //!< Crystal that need some internal resonator circuitry
			clock,	  //!< Something external provides a clear clock
		};
		uint32_t frequency_hz; //!< Frequency
		sources source;		   //!< Clock source
	};
} // namespace mcal
