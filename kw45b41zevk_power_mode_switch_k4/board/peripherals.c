/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v11.0
processor: KW45B41Z83xxxA
package_id: KW45B41Z83AFTA
mcu_data: ksdk2_0
processor_version: 0.12.3
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 706dc89e-c6b5-49d0-b5be-eb0804fc636a
  called_from_default_init: true
  selectedCore: cm33
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table:
      - 0: []
      - 1: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * DEMO_WUU initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DEMO_WUU'
- type: 'wuu'
- mode: 'General'
- custom_name_enabled: 'true'
- type_id: 'wuu_9e591349506d059ebdfbc993a1b4a700'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'WUU0'
- config_sets:
  - fsl_wuu:
    - wuu_module_config: []
    - wuu_external_pin_config: []
    - interrupts:
      - enableInterrupt: 'true'
      - interrupt:
        - IRQn: 'WUU0_IRQn'
        - enable_interrrupt: 'enabled'
        - enable_priority: 'false'
        - priority: '0'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void DEMO_WUU_init(void) {
  /* Enable interrupt WUU0_IRQn request in the NVIC. */
  EnableIRQ(DEMO_WUU_IRQN);
}

/***********************************************************************************************************************
 * DEMO_LPTMR initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DEMO_LPTMR'
- type: 'lptmr'
- mode: 'LPTMR_GENERAL'
- custom_name_enabled: 'true'
- type_id: 'lptmr_48552e76e8733b28a9c768b6d8d4fefa'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPTMR0'
- config_sets:
  - fsl_lptmr:
    - lptmr_config:
      - timerMode: 'kLPTMR_TimerModeTimeCounter'
      - pinSelect: 'ALT.0'
      - pinPolarity: 'kLPTMR_PinPolarityActiveHigh'
      - enableFreeRunning: 'false'
      - bypassPrescaler: 'true'
      - prescalerClockSource: 'kLPTMR_PrescalerClock_2'
      - clockSource: 'custom:1000'
      - value: 'kLPTMR_Prescale_Glitch_0'
      - timerPeriod: '1000000 us'
    - enableDma: 'false'
    - enableInterrupt: 'true'
    - interrupt:
      - IRQn: 'LPTMR0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lptmr_config_t DEMO_LPTMR_config = {
  .timerMode = kLPTMR_TimerModeTimeCounter,
  .pinSelect = kLPTMR_PinSelectInput_0,
  .pinPolarity = kLPTMR_PinPolarityActiveHigh,
  .enableFreeRunning = false,
  .bypassPrescaler = true,
  .prescalerClockSource = kLPTMR_PrescalerClock_2,
  .value = kLPTMR_Prescale_Glitch_0
};

static void DEMO_LPTMR_init(void) {
  /* Initialize the LPTMR */
  LPTMR_Init(DEMO_LPTMR_PERIPHERAL, &DEMO_LPTMR_config);
  /* Set LPTMR period */
  LPTMR_SetTimerPeriod(DEMO_LPTMR_PERIPHERAL, DEMO_LPTMR_TICKS);
  /* Configure timer interrupt */
  LPTMR_EnableInterrupts(DEMO_LPTMR_PERIPHERAL, kLPTMR_TimerInterruptEnable);
  /* Enable interrupt LPTMR0_IRQn request in the NVIC. */
  EnableIRQ(DEMO_LPTMR_IRQN);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  DEMO_WUU_init();
  DEMO_LPTMR_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
