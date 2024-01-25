/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_PLATFORM_H_
#define _BOARD_PLATFORM_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! \brief Change Default trimming value for 32MHz crystal,
      will be used by hardware_init.c file during initialization */
/* BOARD_32MHZ_XTAL_TRIM_DEFAULT macro is deprecated
   please use BOARD_32MHZ_XTAL_CDAC_VALUE now */
#define BOARD_32MHZ_XTAL_CDAC_VALUE 12U

/*! \brief Change Default amplifier current selected for 32MHz crystal,
      will be used by hardware_init.c file during initialization */
//#define BOARD_32MHZ_XTAL_ISEL_VALUE    7U

/*! \brief Default load capacitance config for 32KHz crystal,
      can be overidden from board.h,
      user shall define this flag in board.h file to set an other default value
      Values must be adjusted to minimize the jitter on the crystal. This is to avoid
      a shift of 31.25us on the link layer timebase in NBU.
*/
//#define BOARD_32KHZ_XTAL_CLOAD_DEFAULT 8U

/*! \brief Default coarse adjustement config for 32KHz crystal,
      can be overidden from board.h,
      user shall define this flag in board.h file to set an other default value
      Values must be adjusted depending the equivalent series resistance (ESR) of the crystal on the board
*/
//#define BOARD_32KHZ_XTAL_COARSE_ADJ_DEFAULT 1

/*! \brief Number of half slot before LL interrupt to wakeup the 32MHz of the NBU */
//#define BOARD_LL_32MHz_WAKEUP_ADVANCE_HSLOT 2

/*! \brief Delay from the 32MHz wake up of the LL to wake up the radio domain in number of 32.768kHz clock. This */
//#define BOARD_RADIO_DOMAIN_WAKE_UP_DELAY 0x10U

/*! \brief Calibration settings for the FRO32K */
//#define BOARD_FRO32K_PPM_TARGET 200U
//#define BOARD_FRO32K_FILTER_SIZE 4U

#if (!defined(BOARD_32MHZ_XTAL_CDAC_VALUE)) && (defined(BOARD_32MHZ_XTAL_TRIM_DEFAULT))
/* BOARD_32MHZ_XTAL_TRIM_DEFAULT macro is deprecated
   please use BOARD_32MHZ_XTAL_CDAC_VALUE now */
#define BOARD_32MHZ_XTAL_CDAC_VALUE BOARD_32MHZ_XTAL_TRIM_DEFAULT
#endif

#endif /* _BOARD_PLATFORM_H_ */
