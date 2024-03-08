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

//CAN frame and transfer buffers
flexcan_frame_t frame;
flexcan_mb_transfer_t txXfer, rxXfer;

//Status flag to indicate that work needs done after IRQ and LED sequence vars
uint8_t datacheck = 0;
uint8_t led_blink_delay;
uint8_t led_blink_count;



//Systick counter for delay block function
volatile uint32_t g_systickCounter;

#define RX_MESSAGE_BUFFER_NUM (0)
#define TX_MESSAGE_BUFFER_NUM (1)


/* CAN0_IRQn interrupt handler */
void CAN0_FLEXCAN_IRQHANDLER(void) {
  /*  Place your code here */
  PRINTF("irq called \r\n");

  FLEXCAN_TransferReceiveBlocking(CAN0, rxXfer.mbIdx, &frame);

  led_blink_delay = frame.dataByte0;
  led_blink_count = frame.dataByte1;



  datacheck = 1;

  uint64_t flags2;

  flags2 = FLEXCAN_GetMbStatusFlags(CAN0_PERIPHERAL, 1);
  PRINTF("%i \r\n", flags2);
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


void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

//Delay n milliseconds
void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
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

    //CAN handle and variable initialization
    txIdentifier = 0x123;
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

    /* Set systick reload value to generate 1ms interrupt */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    while(1) {

        i++ ;

        //FLEXCAN_TransferSendNonBlocking(CAN0, &flexcanHandle, &txXfer);
        //FLEXCAN_TransferReceiveNonBlocking(CAN0, &flexcanHandle, &rxXfer);
        //FLEXCAN_TransferReceiveBlocking(CAN0, rxXfer.mbIdx, &frame);

        //GETCHAR();
        //FLEXCAN_TransferSendBlocking(CAN0, txXfer.mbIdx, &frame);



        if (datacheck){

            for(int z = 0; z < led_blink_count; z++){
                SysTick_DelayTicks(led_blink_delay);
                GPIO_PortToggle(GPIOA, 1u << 19U);
            }

            PRINTF("%i \r\n", led_blink_count);
            PRINTF("%i \r\n", led_blink_delay);

            datacheck = 0;

            //FLEXCAN_TransferSendNonBlocking(CAN0, &flexcanHandle, &txXfer);

        }







        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
