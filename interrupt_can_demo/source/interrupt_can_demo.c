/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    interrupt_can_demo.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

flexcan_handle_t flexcanHandle;
flexcan_frame_t tx_frame;
flexcan_mb_transfer_t txXfer;

void delay(uint32_t n) {
	volatile uint32_t i;
	for (i = 0; i < n; i++) {
		asm("nop");
	}
}

/* CAN0_IRQn interrupt handler */
void CAN0_FLEXCAN_IRQHANDLER(void) {
  /*  Place your code here */
  uint32_t flags = FLEXCAN_GetStatusFlags(CAN0);
  FLEXCAN_ClearStatusFlags(CAN0, flags);
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

void can0_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData)
{
	GPIO_PortToggle(GPIOA, 1u << 19U);
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

    FLEXCAN_TransferCreateHandle(CAN0, &flexcanHandle, can0_callback, NULL);



    //while(1){
        tx_frame.id		= FLEXCAN_ID_STD(0x123);
        tx_frame.format	= (uint8_t)kFLEXCAN_FrameFormatStandard;
        tx_frame.type	= (uint8_t)kFLEXCAN_FrameTypeData;
        tx_frame.length	= (uint8_t)8;
        tx_frame.dataByte3 = 0;
        tx_frame.dataByte4 = 0;
        tx_frame.dataByte5 = 0;
        tx_frame.dataByte6 = 0;
        tx_frame.dataByte7 = 0;

        tx_frame.dataByte0 = 0x65;
        tx_frame.dataByte1 = 0x97;


        txXfer.mbIdx = (uint8_t)1;
        txXfer.frame = &tx_frame;
    	FLEXCAN_TransferSendNonBlocking(CAN0, &flexcanHandle, &txXfer);
    	//delay(1000000);
    //}

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
