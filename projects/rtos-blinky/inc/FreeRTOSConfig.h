/**
 * @file FreeRTOSConfig.h
 * @brief FreeRTOS configuration header for STM32F4 Blinky project.
 *
 */

#pragma once

/** @name Kernel Scheduling
 * @{
 */
#define configUSE_PREEMPTION 1						   ///< Preemptive scheduling enabled
#define configCPU_CLOCK_HZ (100000000UL)			   ///< CPU clock used for timing
#define configTICK_RATE_HZ ((TickType_t)1000)		   ///< Tick frequency in Hz
#define configMAX_PRIORITIES 5						   ///< Maximum number of task priorities
#define configMINIMAL_STACK_SIZE ((unsigned short)128) ///< Idle task stack size
#define configTOTAL_HEAP_SIZE ((size_t)(8 * 1024))	   ///< Heap size for dynamic allocation
#define configMAX_TASK_NAME_LEN 16					   ///< Maximum length of task names
/** @} */

/** @name Handler Mapping
 *  @brief Mapping der FreeRTOS Kernel‑Handler auf die STM32F4 Vektor‑Symbole.
 * @{
 */
#define configCHECK_HANDLER_INSTALLATION 1	///< Enable handler installation checks
#define vPortSVCHandler SVC_Handler			///< Map FreeRTOS SVC handler
#define xPortPendSVHandler PendSV_Handler	///< Map FreeRTOS PendSV handler
#define xPortSysTickHandler SysTick_Handler ///< Map FreeRTOS SysTick handler
/** @} */

/** @name Hooks & Tick Configuration
 * @{
 */
#define configUSE_IDLE_HOOK 0	 ///< Idle hook disabled
#define configUSE_TICK_HOOK 0	 ///< Tick hook disabled
#define configUSE_16_BIT_TICKS 0 ///< Use 32‑bit tick counter
/** @} */

/** @name Timer Service
 * @{
 */
#define configUSE_QUEUE_SETS 0			 ///< Queue sets disabled
#define configUSE_TIMERS 0				 ///< Software timers disabled
#define configTIMER_TASK_PRIORITY 2		 ///< Timer task priority
#define configTIMER_QUEUE_LENGTH 5		 ///< Timer command queue length
#define configTIMER_TASK_STACK_DEPTH 256 ///< Timer task stack size
/** @} */

/** @name Memory Allocation
 * @{
 */
#define configSUPPORT_DYNAMIC_ALLOCATION 0	  ///< Dynamic allocation disabled
#define configSUPPORT_STATIC_ALLOCATION 1	  ///< Static allocation enabled
#define configKERNEL_PROVIDED_STATIC_MEMORY 1 ///< Kernel provides static memory
/** @} */

/** @name Interrupt Priorities
 * @{
 */
#define configPRIO_BITS 4							   ///< NVIC priority bits
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15	   ///< Lowest IRQ priority
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5 ///< Max syscall IRQ prio

#define configKERNEL_INTERRUPT_PRIORITY                                                                                \
	(configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS)) ///< Kernel IRQ prio

#define configMAX_SYSCALL_INTERRUPT_PRIORITY                                                                           \
	(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS)) ///< Max syscall IRQ prio
/** @} */

/** @name Assertions
 * @{
 */
#define configASSERT(x)                                                                                                \
	if ((x) == 0)                                                                                                      \
	{                                                                                                                  \
		taskDISABLE_INTERRUPTS();                                                                                      \
		for (;;)                                                                                                       \
			;                                                                                                          \
	} ///< Kernel assertion handler
/** @} */

/** @name Optional Features
 * @{
 */
#define configUSE_TASK_NOTIFICATIONS 1	 ///< Task notifications enabled
#define configUSE_MUTEXES 0				 ///< Mutexes disabled
#define configUSE_RECURSIVE_MUTEXES 0	 ///< Recursive mutexes disabled
#define configUSE_COUNTING_SEMAPHORES 0	 ///< Counting semaphores disabled
#define configUSE_QUEUE_SETS 0			 ///< Queue sets disabled
#define configUSE_APPLICATION_TASK_TAG 0 ///< Application task tags disabled

#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 0
#define INCLUDE_vTaskSuspend 0
#define INCLUDE_xTaskDelayUntil 0
#define INCLUDE_vTaskDelay 1 ///< vTaskDelay enabled
#define INCLUDE_xTaskGetSchedulerState 0
#define INCLUDE_xTaskGetCurrentTaskHandle 1 ///< Current task handle enabled
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_eTaskGetState 0
#define INCLUDE_xTimerPendFunctionCall 0
#define INCLUDE_xTaskAbortDelay 0
#define INCLUDE_xTaskGetHandle 0
#define INCLUDE_xTaskResumeFromISR 0
/** @} */
