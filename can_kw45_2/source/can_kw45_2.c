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
uint8_t uart_rx_char;
uint8_t counter = 0;
#define COMMAND_BUFFER_LENGTH 10
static StreamBufferHandle_t xStreamBuffer0 = NULL;

flexcan_handle_t flexcanHandle;
flexcan_frame_t tx_frame;
flexcan_mb_transfer_t txXfer;

volatile bool tx_complete = false;

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
	status_t status;
	status = LPUART_ClearStatusFlags(LPUART0, intStatus);
	uart_rx_char = ((uint32_t) (LPUART0->DATA));

	//GPIO_PortToggle(GPIOA, 1u << 19U);
	xStreamBufferSendFromISR(xStreamBuffer0, &uart_rx_char, 1,
			xHigherPriorityTaskWoken);

	/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
	 Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

void can0_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status,
		uint64_t result, void *userData) {
	//GPIO_PortToggle(GPIOA, 1u << 19U);
	switch (status) {
	case kStatus_FLEXCAN_TxIdle:
		tx_complete = 1;
	default:
		break;

	}
}

static void CanSenderTask() {

	PRINTF("Hello World\r\n");
	uint8_t command_char;
	FLEXCAN_TransferCreateHandle(CAN0, &flexcanHandle, can0_callback, NULL);
	//GETCHAR();
	while (1) {
		uint8_t transmitted_bytes = xStreamBufferReceive(xStreamBuffer0,
				&command_char, 1, portMAX_DELAY);
		PRINTF("Hello World!\r\n");
		PRINTF("%i, %c, %i, %i received\r\n", counter, command_char,
				command_char, transmitted_bytes);

		for (uint32_t i = 0; i < 5; i++) {
			tx_frame.id = FLEXCAN_ID_STD(0x123);
			tx_frame.format = (uint8_t) kFLEXCAN_FrameFormatStandard;
			tx_frame.type = (uint8_t) kFLEXCAN_FrameTypeData;
			tx_frame.length = (uint8_t) 8;

			tx_frame.dataByte0 = i;
			tx_frame.dataByte1 = 98;
			tx_frame.dataByte2 = 99;
			tx_frame.dataByte3 = 100;
			tx_frame.dataByte4 = 101;
			tx_frame.dataByte5 = 102;
			tx_frame.dataByte6 = 103;
			tx_frame.dataByte7 = 104;

			txXfer.mbIdx = (uint8_t) 1;
			txXfer.frame = &tx_frame;

			FLEXCAN_TransferSendNonBlocking(CAN0, &flexcanHandle, &txXfer);

			while (!tx_complete) {
			}
			tx_complete = 0;
		}
	}
}

static void DebugReceiveTask() {
	while(1){
		delay(5000000);
		GPIO_PortToggle(GPIOA, 1u << 19U);

		uint8_t command = 'a';
		xStreamBufferSend(xStreamBuffer0, &command, 1, portMAX_DELAY);
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
		if (xTaskCreate(CanSenderTask, "UART handler",
		configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 2,
				NULL) != pdPASS) {
			PRINTF("Task creation failed");
			while (1)
				;
		}

		if (xTaskCreate(DebugReceiveTask, "Debug UART handler",
		configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 1,
				NULL) != pdPASS) {
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
			PRINTF("%c %i %i \r\n", uart_rx_char, uart_rx_char, counter);

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
