#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION 1
#define configCPU_CLOCK_HZ (100000000UL)
#define configTICK_RATE_HZ ((TickType_t)1000)
#define configMAX_PRIORITIES 5
#define configMINIMAL_STACK_SIZE ((unsigned short)128)
#define configTOTAL_HEAP_SIZE ((size_t)(8 * 1024))
#define configMAX_TASK_NAME_LEN 16

#define configCHECK_HANDLER_INSTALLATION 1
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configUSE_16_BIT_TICKS 0

#define configUSE_QUEUE_SETS 0
#define configUSE_TIMERS 0
#define configTIMER_TASK_PRIORITY 2
#define configTIMER_QUEUE_LENGTH 5
#define configTIMER_TASK_STACK_DEPTH 256
#define configSUPPORT_DYNAMIC_ALLOCATION 0
#define configSUPPORT_STATIC_ALLOCATION 1
#define configKERNEL_PROVIDED_STATIC_MEMORY 1
#define configPRIO_BITS 4 /* STM32F4 = 16 Priority Levels */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

#define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

// Check config
#define configASSERT(x)                                                                                                \
	if ((x) == 0)                                                                                                      \
	{                                                                                                                  \
		taskDISABLE_INTERRUPTS();                                                                                      \
		for (;;)                                                                                                       \
			;                                                                                                          \
	}

// Features
#define configUSE_TASK_NOTIFICATIONS 1
#define configUSE_MUTEXES 0
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_COUNTING_SEMAPHORES 0
#define configUSE_QUEUE_SETS 0
#define configUSE_APPLICATION_TASK_TAG 0
#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 0
#define INCLUDE_vTaskSuspend 0
#define INCLUDE_xTaskDelayUntil 0
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetSchedulerState 0
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_eTaskGetState 0
#define INCLUDE_xTimerPendFunctionCall 0
#define INCLUDE_xTaskAbortDelay 0
#define INCLUDE_xTaskGetHandle 0
#define INCLUDE_xTaskResumeFromISR 0
#endif /* FREERTOS_CONFIG_H */
