/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    can_kw45_2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"
#include "peripherals.h"
//#include "projdefs.h"

/* TODO: insert other definitions and declarations here. */
/* LPUART0_IRQn interrupt handler */
uint8_t rx_char;
uint8_t counter = 0;
#define COMMAND_BUFFER_LENGTH 10
static StreamBufferHandle_t xStreamBuffer0 = NULL;

void delay(uint32_t n) {
	volatile uint32_t i;
	for (i = 0; i < n; i++) {
		asm("nop");
	}
}
/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
	uint32_t intStatus;
	/* Reading all interrupt flags of status registers */
	intStatus = LPUART_GetStatusFlags(LPUART0);
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	/* Flags can be cleared by reading the status register and reading/writing data registers.
	 See the reference manual for details of each flag.
	 The LPUART_ClearStatusFlags() function can be also used for clearing of flags in case the content of data/FIFO regsiter is not used.
	 For example:
	 status_t status;
	 status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);
	 */
	/* Place your code here */
	//FIFO bit 22 RXEMPT is not working, pole until not null
	status_t status;
	status = LPUART_ClearStatusFlags(LPUART0, intStatus);


//	rm counter = 0;
//	do {
//		counter += 1;
//		rx_char = ((uint32_t) (LPUART0->DATA));
//	} while (!rx_char);

//	while (!(LPUART0->DATA & LPUART_DATA_RXEMPT_MASK)) {
//		rx_char = ((uint32_t) (LPUART0->DATA));
//	} rm


	rx_char = ((uint32_t) (LPUART0->DATA));



	GPIO_PortToggle(GPIOA, 1u << 19U);
	xStreamBufferSendFromISR(xStreamBuffer0, &rx_char, 1,
			xHigherPriorityTaskWoken);

	/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
	 Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}
static void commandReceiverTask() {

	PRINTF("Hello World\r\n");
	uint8_t command_char;

	while (1) {
		//delay(1000000);
		uint8_t transmitted_bytes = xStreamBufferReceive(xStreamBuffer0,
				&command_char, 1, portMAX_DELAY);
		GPIO_PortToggle(GPIOA, 1u << 19U);
		PRINTF("Hello World!\r\n");
		PRINTF("%i, %c, %i, %i received\r\n", counter, command_char, command_char, transmitted_bytes);

	}
}

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
	//don't let interrupt priority == 0
	NVIC_SetPriority(LPUART0_IRQn, 10);
	if (xTaskCreate(commandReceiverTask, "Command handler",
	configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		PRINTF("Task creation failed");
		while (1)
			;
	}

	xStreamBuffer0 = xStreamBufferCreate(COMMAND_BUFFER_LENGTH, 1);
	if (xStreamBuffer0 == NULL) {
		while (1)
			;
	}

	vTaskStartScheduler();
	while (1) {
		delay(1000000);
		GPIO_PortToggle(GPIOA, 1u << 19U);
		PRINTF("Hello World\r\n");
		PRINTF("%c %i %i \r\n", rx_char, rx_char, counter);

	}

	//vTaskStartScheduler();

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	/* Enter an infinite loop, just incrementing a counter. */
	while (1) {
		i++;
		/* 'Dummy' NOP to allow source level single stepping of
		 tight while() loop */
		__asm volatile ("nop");
	}
	return 0;
}
