/*! *********************************************************************************
 * \defgroup EATT Peripheral
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2021-2022 NXP
* All rights reserved.
*
* \file
*
* This file is the interface file for the EATT peripheral application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef EATT_PERIPHERAL_H
#define EATT_PERIPHERAL_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "fsl_component_button.h"

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/
/* Profile Parameters */
#define gFastConnMinAdvInterval_c               32      /* 20 ms */
#define gFastConnMaxAdvInterval_c               48      /* 30 ms */

#define gReducedPowerMinAdvInterval_c           1600    /* 1 s */
#define gReducedPowerMaxAdvInterval_c           4000    /* 2.5 s */

#define gFastConnAdvTime_c                      30      /* s */
#define gReducedPowerAdvTime_c                  300     /* s */

#if gAppUseBonding_d
#define gFastConnFilterAcceptListAdvTime_c      10      /* s */
#else
#define gFastConnFilterAcceptListAdvTime_c      0
#endif

#define gBleSig_AService_d                      0xA00A
#define gBleSig_BService_d                      0xB00B

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern gapAdvertisingData_t             gAppAdvertisingData;
extern gapScanResponseData_t            gAppScanRspData;
extern gapAdvertisingParameters_t       gAdvParams;
extern gapPairingParameters_t           gPairingParameters;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void BleApp_Start(void);

#ifdef __cplusplus
}
#endif


#endif /* ADV_EXT_PERIPHERAL_H */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
