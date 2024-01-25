/*! *********************************************************************************
 * \addtogroup Main
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2021-2022 NXP
* All rights reserved.
*
* \file
*
* This is the source file for the main entry point for a FreeRTOS application.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
#include "app.h"
#include "app_conn.h"
#include "fsl_os_abstraction.h"

/************************************************************************************
 *************************************************************************************
 * Private functions prototypes
 *************************************************************************************
 ************************************************************************************/
static void start_task(void *argument);

/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/
static OSA_TASK_HANDLE_DEFINE(s_startTaskHandle);
static OSA_TASK_DEFINE(start_task, gMainThreadPriority_c, 1, gMainThreadStackSize_c, 0);

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

static void start_task(void *argument)
{
    /* Start Application services (timers, serial manager, low power, led, button, etc..) */
    APP_InitServices();

    /* Start BLE Platform related ressources such as clocks, Link layer and HCI transport to Link Layer */
    (void)APP_InitBle();

    /* Start Host stack */
    BluetoothLEHost_AppInit();

    while(TRUE)
    {
        BluetoothLEHost_HandleMessages();
    }
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
int main(void)
{
    /* Init OSA: should be called before any other OSA API */
    OSA_Init();

    BOARD_InitHardware();

    (void)OSA_TaskCreate((osa_task_handle_t)s_startTaskHandle, OSA_TASK(start_task), NULL);

    /* Start scheduler*/
    OSA_Start();

    /*won't run here*/
    assert(0);
    return 0;
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
