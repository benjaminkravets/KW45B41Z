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
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

void delay(uint32_t n)
{
	volatile uint32_t i;
	for (i = 0; i < n; i++)
	{
		asm("nop");
	}
}

void tokenator(uint8_t stok[]){

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

	PRINTF("Hello World\r\n");

	//bring_up_uart();

//    int8_t get[255] = {0};
//    PRINTF("KW45>Enter sequence \r\n");
//
//    while(1){
//    	PRINTF("KW45> ");
//    	uint32_t scanned = SCANF("%s", &get);
//    	PRINTF("%s \r\n", &get);
//    }
//

	uint8_t rx_buffer[256];
	uint8_t cur_char;
	uint32_t cursor = 0;


	while (1) {
		cur_char = GETCHAR();
		PRINTF("%c", cur_char);

		rx_buffer[cursor] = cur_char;
		cursor += 1;

		if (cur_char == 13){
			PRINTF("\r\n ENTER \r\n");
			for(int32_t i = 0; i < cursor; i++){
				PRINTF("%c",rx_buffer[i]);
			}
			PRINTF("\r\nKW45>");
			memset(rx_buffer, 0, sizeof(rx_buffer));
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
