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
#include "fsl_flexcan.h"

/* TODO: insert other definitions and declarations here. */
/* LPUART0_IRQn interrupt handler */
uint8_t uart_rx_char;
uint8_t counter = 0;
#define COMMAND_BUFFER_LENGTH 10
#define RX_BUFFER_LENGTH 64

//#define LOGGING

static StreamBufferHandle_t xStreamBuffer0;
static StreamBufferHandle_t xStreamBuffer1;


flexcan_handle_t flexcan_handle;
flexcan_frame_t tx_frame;
flexcan_frame_t rx_frame[1];
flexcan_fd_frame_t rx_frame_fd[1];

flexcan_mb_transfer_t tx_mb_frame;
flexcan_fifo_transfer_t rx_fifo_frame;

uint32_t TxComplete = 0;
uint32_t RxComplete = 0;

void * EnRxTableId;

void delay(uint32_t n) {
	volatile uint32_t i;
	for (i = 0; i < n; i++) {
		asm("nop");
	}
}

/* LPIT0_IRQn interrupt handler */
void LPIT0_IRQHANDLER(void) {
  /*  Place your code here */
  uint32_t flags = LPIT_GetStatusFlags(LPIT0_PERIPHERAL);
  LPIT_ClearStatusFlags(LPIT0_PERIPHERAL, flags);
  LPIT_GetStatusFlags(LPIT0_PERIPHERAL);
  GPIO_PortToggle(GPIOA, 1u << 19U);

  uint8_t command = 'a';
  xStreamBufferSend(xStreamBuffer0, &command, 1, portMAX_DELAY);

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
	uint32_t intStatus;
	/* Reading all interrupt flags of status registers */
	intStatus = LPUART_GetStatusFlags(LPUART0);
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uart_rx_char = ((uint32_t) (LPUART0->DATA));
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
	switch (status) {
	case kStatus_FLEXCAN_TxIdle:
		TxComplete = 1;
		break;
	case kStatus_FLEXCAN_RxFifoIdle:
		RxComplete = 1;
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte0, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte1, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte2, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte3, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte4, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte5, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte6, 1, 1000);
		xStreamBufferSend(xStreamBuffer1, &rx_frame_fd->dataByte7, 1, 1000);

//		//This can be used instead of per byte accesses
//		uint8_t init[8] = {3, 2, 1, 0, 7, 6, 5, 4};
//		uint8_t * dataBytes = &tx_frame.dataByte3;
//		for (uint32_t x = 0; x < 8; x++) {
//			xStreamBufferSend(xStreamBuffer1, &dataBytes[init[x]], 1, 1000);
//		}

	default:
		break;

	}
}

static void CanSenderReceiverTask() {
	status_t ret = 0;
	uint8_t command_char;
	while (1) {
		uint8_t transmitted_bytes = xStreamBufferReceive(xStreamBuffer0,
				&command_char, 1, portMAX_DELAY);
		//PRINTF("%i, %c, %i, %i received\r\n", counter, command_char, command_char, transmitted_bytes);

		for (uint32_t i = 0; i < 8; i++) {
			tx_frame.id = FLEXCAN_ID_STD(0x123);
			tx_frame.format = (uint8_t) kFLEXCAN_FrameFormatStandard;
			tx_frame.type = (uint8_t) kFLEXCAN_FrameTypeData;
			tx_frame.length = (uint8_t) 8;

			tx_frame.dataByte0 = 0 + i * 8;
			tx_frame.dataByte1 = 1 + i * 8;
			tx_frame.dataByte2 = 2 + i * 8;
			tx_frame.dataByte3 = 3 + i * 8;
			tx_frame.dataByte4 = 4 + i * 8;
			tx_frame.dataByte5 = 5 + i * 8;
			tx_frame.dataByte6 = 6 + i * 8;
			tx_frame.dataByte7 = 7 + i * 8;

//			//This can be used instead of per byte accesses
//			uint8_t init[8] = {3, 2, 1, 0, 7, 6, 5, 4};
//			for (uint32_t x = 0; x < 8; x++) {
//				((uint8_t*)&tx_frame.dataByte3)[init[x]] = x + i * 8;
//			}

			tx_mb_frame.mbIdx = (uint8_t) 1;
			tx_mb_frame.frame = &tx_frame;

			FLEXCAN_TransferSendNonBlocking(CAN0, &flexcan_handle, &tx_mb_frame);

			while (!TxComplete) {
			}
			#ifdef LOGGING
				PRINTF("%i Packet Sent \r\n", xTaskGetTickCount());
			#endif
			TxComplete = 0;

		}

		rx_fifo_frame.frame = &rx_frame[0];
		rx_fifo_frame.framefd = &rx_frame_fd[0];
		rx_fifo_frame.frameNum = 1;
		for(uint32_t i = 0; i < 8; i++){
			ret = FLEXCAN_TransferReceiveEnhancedFifoNonBlocking(CAN0, &flexcan_handle, &rx_fifo_frame);
			while (!RxComplete){

			}
		}
	}
}

static void CanPrintTask() {
	uint8_t rx_char;
	while(1){
		xStreamBufferReceive(xStreamBuffer1, &rx_char, 1, portMAX_DELAY);
		#ifdef LOGGING
			PRINTF("Received: %i ", rx_char);
		#endif
	}
}

	/*
	 * @brief   Application entry point.
	 */
	int main(void) {
		uint32_t test[] = {FLEXCAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(0x321, 0, 0x3F, 0),
                		   FLEXCAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(0x321, 0, 0x3F, 0),
						   FLEXCAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(0x321, 0, 0x3F, 0),
						   FLEXCAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(0x321, 0, 0x3F, 0),
		};
		EnRxTableId = (void *)test;
		//Init streambuffer0 before starting LPIT so that stream buffer is not NULL when used in first handler call (this is not a fix, it just
		//avoids changing IDE generated peripheral initialization code :). This should by solved by starting LPIT after freertos is running or exiting the
		//IRQ handler if a "is first call" condition is met.)

		xStreamBuffer0 = xStreamBufferCreate(COMMAND_BUFFER_LENGTH, 1);
		if (xStreamBuffer0 == NULL) {
			while (1)
				;
		}

		/* Init board hardware. */
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();
#endif
		//don't let interrupt priority == 0
		NVIC_SetPriority(LPUART0_IRQn, 20);

		FLEXCAN_TransferCreateHandle(CAN0, &flexcan_handle, can0_callback, NULL);
		if (xTaskCreate(CanSenderReceiverTask, "CanSenderReceiverTask",
		configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 2,
				NULL) != pdPASS) {
			PRINTF("Task creation failed");
			while (1)
				;
		}

		if (xTaskCreate(CanPrintTask, "CanPrintTask",
		configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 2,
				NULL) != pdPASS) {
			PRINTF("Task creation failed");
			while (1)
				;
		}

		xStreamBuffer1 = xStreamBufferCreate(RX_BUFFER_LENGTH, 1);
		if (xStreamBuffer1 == NULL) {
			while (1)
				;
		}

		vTaskStartScheduler();


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
