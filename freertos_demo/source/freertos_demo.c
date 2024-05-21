/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    freertos_demo.c
 * @brief   Application entry point.
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "KW45B41Z83.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
static void prvQueueReceiveTask(void *pvParameters);

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    if (xTaskCreate(/* The function that implements the task. */
                    prvQueueReceiveTask,
                    /* Text name for the task, just to help debugging. */
                    "Rx",
                    /* The size (in words) of the stack that should be created
                    for the task. */
                    configMINIMAL_STACK_SIZE + 166,
                    /* A parameter that can be passed into the task.  Not used
                    in this simple demo. */
                    NULL,
                    /* The priority to assign to the task.  tskIDLE_PRIORITY
                    (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
                    is the highest priority. */
					tskIDLE_PRIORITY + 2,
                    /* Used to obtain a handle to the created task.  Not used in
                    this simple demo, so set to NULL. */
                    NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    vTaskStartScheduler();
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

static void prvQueueReceiveTask(void *pvParameters)
{


    while(1) {
    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    	GPIO_PortToggle(GPIOA, 1u << 19U);
        PRINTF("Hello World\r\n");

    }
}
