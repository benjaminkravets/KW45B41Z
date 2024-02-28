/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    can_kw45.c
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
//CAN variables
flexcan_handle_t flexcanHandle;
uint32_t txIdentifier;
uint32_t rxIdentifier;
uint8_t DLC;

flexcan_frame_t frame;
flexcan_mb_transfer_t txXfer, rxXfer;

#define RX_MESSAGE_BUFFER_NUM (0)
#define TX_MESSAGE_BUFFER_NUM (1)


/* CAN0_IRQn interrupt handler */
void CAN0_FLEXCAN_IRQHANDLER(void) {
  /*  Place your code here */
  PRINTF("irq called \r\n");
  uint32_t flags;
  PRINTF("%i \r\n", flags);
  flags = FLEXCAN_GetStatusFlags(CAN0_PERIPHERAL);
  FLEXCAN_ClearStatusFlags(CAN0_PERIPHERAL, flags);
  FLEXCAN_GetStatusFlags(CAN0_PERIPHERAL);
  PRINTF("%i \r\n", flags);


  GPIO_PortToggle(GPIOA, 1u << 19);

  uint32_t flags2;
  PRINTF("%i \r\n", flags2);
  flags2 = FLEXCAN_GetMbStatusFlags(CAN0_PERIPHERAL, rxIdentifier);
  FLEXCAN_ClearMbStatusFlags(CAN0_PERIPHERAL, flags2);
  FLEXCAN_GetMbStatusFlags(CAN0_PERIPHERAL, flags2);
  PRINTF("%i \r\n", flags2);

  PRINTF("irq end \r\n");/* CAN0_IRQn interrupt handler */


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

    //CAN handle and variable initialization
    txIdentifier = 0x321;
    rxIdentifier = 0x446;
    DLC = 8;
    FLEXCAN_TransferCreateHandle(CAN0_PERIPHERAL, &flexcanHandle, NULL, NULL);
    FLEXCAN_SetRxMbGlobalMask(CAN0_PERIPHERAL, FLEXCAN_RX_MB_STD_MASK(rxIdentifier, 0, 0));

    frame.id = FLEXCAN_ID_STD(txIdentifier);
    frame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;
    frame.type = (uint8_t)kFLEXCAN_FrameTypeData;
    frame.length = (uint8_t)DLC;

    txXfer.mbIdx = (uint8_t)TX_MESSAGE_BUFFER_NUM;
    rxXfer.mbIdx = (uint8_t)RX_MESSAGE_BUFFER_NUM;
    txXfer.frame = &frame;
    rxXfer.frame = &frame;



#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    FLEXCAN_TransferReceiveNonBlocking(CAN0, &flexcanHandle, &rxXfer);
    //FLEXCAN_TransferReceiveBlocking(CAN0, &rxXfer.mbIdx, &frame);
    while(1) {

        //i++ ;
        //GETCHAR();
        //GPIO_PortToggle(GPIOA, 1u << 19);
        //FLEXCAN_TransferSendNonBlocking(CAN0, &flexcanHandle, &txXfer);
        //FLEXCAN_TransferReceiveNonBlocking(CAN0, &flexcanHandle, &rxXfer);

        //FLEXCAN_TransferReceiveBlocking(CAN0, rxXfer.mbIdx, &frame);


        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
