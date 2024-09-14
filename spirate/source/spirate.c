/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    spirate.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "KW45B41Z83.h"
#include "fsl_debug_console.h"
#include "fsl_lpuart.h"
#include "fsl_lpspi.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define BUFFER_SIZE 256

void delay(uint32_t n) {
	volatile uint32_t i;
	for (i = 0; i < n; i++) {
		asm("nop");
	}
}


void spi_transfer(uint8_t tx_buffer[], uint32_t cursor)
{
	uint8_t rx_buffer[BUFFER_SIZE];

    PRINTF("\r\nSPI SEND: ");
    for (uint32_t i = 0; i < cursor - 1; i++)
    {
        PRINTF("%i ", tx_buffer[i]);
    }
    PRINTF("\r\nReceive %i bytes: ", tx_buffer[cursor-1]);


    for (uint32_t i = 0; i < (cursor + tx_buffer[cursor-1] - 1); i++){
    	PRINTF("%i ", rx_buffer[i]);
    }


	lpspi_transfer_t scooby;
	scooby.txData = tx_buffer;
	scooby.rxData = rx_buffer;
	scooby.dataSize = (cursor + tx_buffer[cursor-1] - 1);
	scooby.configFlags = kLPSPI_MasterPcs3 | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
	if(LPSPI_MasterTransferBlocking(LPSPI1, &scooby) == kStatus_Success)
		PRINTF("\r\n TX success \r\n");
}

void spi_pause(uint32_t pause_for)
{
    PRINTF("PAUSE: %i", pause_for);

    PRINTF("\r\n");
}

void paws(uint8_t command_input[])
{
    uint8_t *next_tok = strtok(command_input, " ");

    while (next_tok != NULL)
    {
        uint8_t tx_buffer[256] = {0};
        uint32_t cursor = 0;

        if (strcmp(next_tok, "SR") == 0)
        {
            next_tok = strtok(NULL, " ");

            while (isdigit(*next_tok))
            {
                tx_buffer[cursor++] = atoi(next_tok);
                next_tok = strtok(NULL, " ");
            }

            spi_transfer(tx_buffer, cursor);

            continue;
        }

        else if (strcmp(next_tok, "P") == 0)
        {
            next_tok = strtok(NULL, " ");

            spi_pause(atoi(next_tok));
        }
        else if (strcmp(next_tok, "E") == 0)
        {
            PRINTF("END\r\n");
        }

        next_tok = strtok(NULL, " ");
    }
}

void spi_sample(size_t tx_size, uint8_t tx_buffer[], uint8_t rx_buffer[]){

	lpspi_transfer_t scooby;
	scooby.txData = tx_buffer;
	scooby.rxData = rx_buffer;
	scooby.dataSize = tx_size;
	scooby.configFlags = kLPSPI_MasterPcs3 | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;


	LPSPI_MasterTransferBlocking(LPSPI1, &scooby);
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

	//PRINTF("Hello World\r\n");

	//bring_up_uart();


	uint8_t comm_buffer[BUFFER_SIZE];
	uint8_t rx_buffer[BUFFER_SIZE];
	uint8_t tx_buffer[BUFFER_SIZE];
	uint8_t cur_char;
	uint32_t cursor = 0;
    //uint8_t foo[] = "SR 1 56 78 255 3 4 P 10000 SR 45 6 8 9 62 2 P 2000 SR 1 32 54 234 E";

	//paws(foo);

//	while(1){
//
////		PRINTF("RX BUFFER: ");
////		for(int i = 0; i < 10; i++){
////			PRINTF("%i ", rx_buffer[i]);
////		}
//
//		spi_sample(20, tx_buffer, rx_buffer);
//		delay(5000000);
//		PRINTF("Sent \r\n");
//
////		PRINTF("RX BUFFER: ");
////		for(int i = 0; i < 10; i++){
////			PRINTF("%i ", rx_buffer[i]);
////		}
//	}

	PRINTF("\r\nKW45>");
	while (1) {
		cur_char = GETCHAR();

		comm_buffer[cursor] = cur_char;
		cursor += 1;

		if (cur_char == 13) {

			paws(comm_buffer);

			PRINTF("\r\nKW45>");
			memset(rx_buffer, 0, BUFFER_SIZE);
			cursor = 0;
		}

	}

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	/* Enter an infinite loop, just incrementing a counter. */
	while (1) {
		i++;
		/* 'Dummy' NOP to allow source level single stepping of
		 tight while() loop */
		__asm volatile ("nop");

		//delay(5000000);
		//GPIO_PortToggle(GPIOA, 1u << 19U);
		//PRINTF("Hi");
	}
	return 0;
}
