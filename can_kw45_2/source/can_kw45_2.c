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
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "stdint.h"
/* TODO: insert other definitions and declarations here. */
/* LPUART0_IRQn interrupt handler */
uint8_t rx_char = 'a';
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
  intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL);

  /* Flags can be cleared by reading the status register and reading/writing data registers.
    See the reference manual for details of each flag.
    The LPUART_ClearStatusFlags() function can be also used for clearing of flags in case the content of data/FIFO regsiter is not used.
    For example:
        status_t status;
        status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);
  */

  /* Place your code here */

  status_t status;
  status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);

  GPIO_PortToggle(GPIOA, 1u << 19U);
//  if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART0_PERIPHERAL)){
//	  rx_char = LPUART_ReadByte(LPUART0_PERIPHERAL);
//  }
  while(!((1 << 22U)&LPUART0_PERIPHERAL->FIFO)){
	  rx_char = LPUART_ReadByte(LPUART0_PERIPHERAL);
  }
  //if ((kLPUART_RxDataRe))

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
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

    while(1){
    	delay(5000000);
    	GPIO_PortToggle(GPIOA, 1u << 19U);
        PRINTF("Hello World\r\n");
        PRINTF("%c %i \r\n", rx_char, rx_char);


    }

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
