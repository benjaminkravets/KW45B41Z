/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    spi_kw45_1.c
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

#define TRANSFER_SIZE 64U

AT_NONCACHEABLE_SECTION_INIT(uint8_t master_receive_data[TRANSFER_SIZE]) = {0};
AT_NONCACHEABLE_SECTION_INIT(uint8_t master_transfer_data[TRANSFER_SIZE]) = {0};
AT_NONCACHEABLE_SECTION_INIT(lpspi_master_edma_handle_t g_m_edma_handle) = {0};

SemaphoreHandle_t edma_transfer_complete;

static void spi_handler_entry(void *argument);

void spi_transfer_complete(LPSPI_Type *base, lpspi_master_edma_handle_t *handle,
						   status_t status, void *userData)
{
	if (status == kStatus_Success)
	{
		PRINTF("\r\n SPI transfer successful \r\n");
		xSemaphoreGive(edma_transfer_complete);

	}
}
static void spi_handler_entry(void *argument)
{

	uint32_t transmission_count = 0;
	lpspi_transfer_t master_transfer; //spi transfer handle, defines tx/rx buffer, data size, and settings for CS, etc.
	master_transfer.configFlags = kLPSPI_MasterPcs0 | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
	master_transfer.dataSize = TRANSFER_SIZE;

	while (1)
	{

		for (uint8_t j = 0; j < TRANSFER_SIZE; j++)
		{
			master_transfer_data[j] = j + transmission_count;
		}
		transmission_count += 1;

		vTaskDelay(pdMS_TO_TICKS(1000));

		master_transfer.txData = master_transfer_data;
		master_transfer.rxData = NULL;

		LPSPI_MasterTransferEDMA(LPSPI0, &LPSPI0_handle, &master_transfer);

		xSemaphoreTake(edma_transfer_complete, pdMS_TO_TICKS(500));

        PRINTF("\r\n Sent: ");

		for (uint8_t z = 0; z < TRANSFER_SIZE; z++)
		{
			PRINTF(" %i", master_transfer_data[z]);
		}
		PRINTF("\r\n");

		master_transfer.rxData = master_receive_data;
		master_transfer.txData = NULL;

		LPSPI_MasterTransferEDMA(LPSPI0, &LPSPI0_handle, &master_transfer);

		xSemaphoreTake(edma_transfer_complete, pdMS_TO_TICKS(500));

        PRINTF("\r\n Received: ");

		for (uint8_t z = 0; z < TRANSFER_SIZE; z++)
		{
			PRINTF(" %i", master_receive_data[z]);
		}
		PRINTF("\r\n");
	}
}

/*
 * @brief   Application entry point.
 */

int main(void)
{

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	BaseType_t task_created = xTaskCreate(spi_handler_entry,			// function
										  "SPI handler",				// debug task code
										  configMINIMAL_STACK_SIZE * 8, // stack size
										  NULL,							// function parameters (unused)
										  1,							// priority
										  NULL);						// task handle - unused

	if (task_created != pdPASS)
	{
		PRINTF("Task alloc failed \r\n");
	}
	else
	{
		PRINTF("Task created \r\n");
	}
	edma_transfer_complete = xSemaphoreCreateBinary();

	if (edma_transfer_complete == NULL)
	{
		PRINTF("Semaphore alloc failed \r\n");
	}
	else
	{
		PRINTF("Semaphore created \r\n");
	}

	vTaskStartScheduler();
	/* Enter an infinite loop, just incrementing a counter. */

	while (1)
	{
		i++;
		/* 'Dummy' NOP to allow source level single stepping of
		 tight while() loop */
		__asm volatile("nop");
	}
	return 0;
}
