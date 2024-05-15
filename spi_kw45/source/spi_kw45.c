/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    spi_kw45.c
 * @brief   Application entry point.
 */
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

AT_NONCACHEABLE_SECTION_INIT(uint8_t master_transfer_data[TRANSFER_SIZE]) = {0};
volatile uint32_t g_systickCounter = 20;
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

    uint32_t transmission_count = 0;


    lpspi_transfer_t master_transfer;


    master_transfer.configFlags = kLPSPI_MasterPcs0 | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap ;

    uint8_t lpspi_return = 0;
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1){

        for (uint8_t j = 0; j < TRANSFER_SIZE; j++){
        	master_transfer_data[j] = j + transmission_count;
        }
        transmission_count += 1;

        GETCHAR();
        PRINTF("Hello World\r\n");
        //uint8_t ret = LPSPI_MasterTransferEDMA(LPSPI0, &LPSPI0_config, &master_transfer);
        master_transfer.txData = master_transfer_data;
        master_transfer.rxData = NULL;
        master_transfer.dataSize = TRANSFER_SIZE;
        lpspi_return = LPSPI_MasterTransferBlocking(LPSPI0, &master_transfer);
        PRINTF("%i \r\n", lpspi_return);


		master_transfer.txData = NULL;
		master_transfer.rxData = master_transfer_data;
		master_transfer.dataSize = TRANSFER_SIZE;
		lpspi_return = LPSPI_MasterTransferBlocking(LPSPI0, &master_transfer);


    }
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
