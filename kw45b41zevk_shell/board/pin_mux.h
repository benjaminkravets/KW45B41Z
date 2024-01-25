/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*! @name PORTA19 (number 14), LED_GREEN
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_GREEN_GPIO GPIOA                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_GREEN_GPIO_PIN_MASK (1U << 19U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_LED_GREEN_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_GREEN_PIN 19U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_GREEN_PIN_MASK (1U << 19U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PORTA20 (number 17), LED_BLUE
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOA                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_BLUE_GPIO_PIN_MASK (1U << 20U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_LED_BLUE_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_BLUE_PIN 20U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_BLUE_PIN_MASK (1U << 20U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PORTA21 (number 18), LED_RED
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_RED_GPIO GPIOA                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_RED_GPIO_PIN_MASK (1U << 21U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_LED_RED_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_RED_PIN 21U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_RED_PIN_MASK (1U << 21U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
