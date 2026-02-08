/**
 * @file main.cpp
 * @brief Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.
 */

#include "bsp.h"
#include "mcal.hpp"
#include "utils.hpp"
#include <FreeRTOS.h>
#include <cstdio>
#include <task.h>
/**
 * @brief Use the Nucleo F446ZE board with 100 MHz system clock.
 */
using board = bsp::nucleo_f446ze<100 * utils::unit::MHz>;

/*-----------------------------------------------------------*/

static void blue_button(void *parameters)
{
	(void)parameters;
	for (;;)
	{
		if (board::B1::read())
		{
			board::LD_Blue::set();
		}
		else
		{
			board::LD_Blue::clear();
		}
		vTaskDelay(2);
	}
}

static void blink_green(void *parameters)
{
	(void)parameters;

	for (;;)
	{
		board::LD_Green::set();
		vTaskDelay(104);
		board::LD_Green::clear();
		vTaskDelay(104);
	}
}

/**
 * @brief Main entry point.
 */
int main() noexcept
{
	board::init();
	static StaticTask_t blueTaskTCB;
	static StackType_t blueTaskStack[configMINIMAL_STACK_SIZE];
	static StaticTask_t greenTaskTCB;
	static StackType_t greenTaskStack[configMINIMAL_STACK_SIZE];

	(void)xTaskCreateStatic(blue_button, "Blue button", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1U,
							&(blueTaskStack[0]), &(blueTaskTCB));
	(void)xTaskCreateStatic(blink_green, "Green blinky", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1U,
							&(greenTaskStack[0]), &(greenTaskTCB));
	vTaskStartScheduler();
	return 0;
}
