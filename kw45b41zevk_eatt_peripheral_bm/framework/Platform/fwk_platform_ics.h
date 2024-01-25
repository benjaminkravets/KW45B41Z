/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FWK_PLATFORM_ICS_H__
#define __FWK_PLATFORM_ICS_H__

/*!
 * @addtogroup FWK_Platform_module
 * @{
 */
/*!
 * @addtogroup FWK_Platform_ICS
 * The FWK_Platform_ICS module
 *
 * Framework platform inter core service module provides services to manage communication between the 2 device cores.
 * @{
 */

/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */

#include "EmbeddedTypes.h"

/* -------------------------------------------------------------------------- */
/*                                Public macros                               */
/* -------------------------------------------------------------------------- */
#define MAX_TAG_SZ        40
#define MAX_SHA_SZ        20
#define MAX_VARIANT_SZ    25
#define MAX_BUILD_TYPE_SZ 10

#ifndef NBU_VERSION_DBG
#define NBU_VERSION_DBG 0
#endif

/* maximum size for API input parameters in bytes */
#define NBU_API_MAX_PARAM_LENGTH 40U

/* maximum size for API output parameters including status in bytes.
   should be same as the one defined in the NBU core  */
#define NBU_API_MAX_RETURN_PARAM_LENGTH 38U

/* -------------------------------------------------------------------------- */
/*                           Public type definitions                          */
/* -------------------------------------------------------------------------- */

/*! \brief  NBU core build information.
 *
 * Data structure containing NBU build information.
 * WARNING: this must be in sync with equivalent NBU structure
 */
typedef PACKED_STRUCT NbuInfo_tag
{
    uint8_t versionNumber[3];
    uint8_t repo_digest[MAX_SHA_SZ];
    char    repo_tag[MAX_TAG_SZ];
    char    variant[MAX_VARIANT_SZ];
    char    build_type[MAX_BUILD_TYPE_SZ];
    uint8_t versionBuildNo;
}
NbuInfo_t;

/*! \brief  FWK ICS message type.
 *
 *  \details enumarated values for FWK ICS messages
 */
typedef enum
{
    gFwkSrvNbu2HostFirst_c = 0U,
    gFwkSrvNbuInitDone_c,
    gFwkSrvNbuVersionIndication_c,
    gFwkSrvNbuApiIndication_c,
    gFwkSrvNbuMemFullIndication_c,
    gFwkSrvHostSetLowPowerConstraint_c,
    gFwkSrvHostReleaseLowPowerConstraint_c,
    gFwkSrvFroNotification_c,
    gFwkSrvNbu2HostLast_c,
    gFwkSrvHost2NbuFirst_c = 0x80U,
    gFwkSrvNbuVersionRequest_c,
    gFwkSrvXtal32MTrimIndication_c,
    gFwkSrvNbuApiRequest_c,
    gFwkTemperatureIndication_c, /*!< Receive Temperature value */
    gFwkSrvHostChipRevision_c,   /*!< Receive Chip Revision value */
    gFwkSrvNbuSecureModeRequest_c,
    gFwkSrvNbuWakeupDelayLpoCycle_c, /*!< BLE timer wakeup delay in number of 3.2kHz period */
    gFwkSrvNbuUpdateFrequencyConstraintFromHost,
    gFwkSrvNbuSetRfSfcConfig_c,
    gFwkSrvFroEnableNotification_c,
    gFwkSrvHost2NbuLast_c,
} eFwkSrvMsgType;

typedef int32_t (*fwksrv_lowpower_constraint_func_t)(int32_t power_mode);

typedef struct
{
    fwksrv_lowpower_constraint_func_t fwkSrvSetLowPowerConstraint;
    fwksrv_lowpower_constraint_func_t fwkSrvReleaseLowPowerConstraint;
} FwkSrv_LowPowerConstraintCallbacks_t;

typedef void (*nbu_memory_error_callback_t)(void *param);

typedef void (*PLATFORM_FroDebugCallback_t)(uint16_t freq, int16_t ppm_mean, int16_t ppm);

/* -------------------------------------------------------------------------- */
/*                              Public prototypes                             */
/* -------------------------------------------------------------------------- */

/*!
 * \brief Initialization of the PLATFORM Service channel
 *
 * \return int 0 if success, 1 if already initialized, negative value if error.
 */
int PLATFORM_FwkSrvInit(void);

/*!
 * \brief Sends message to peer CPU
 *
 * \param[in] msg_type Message type (from eFwkSrvMsgType enum)
 * \param[in] msg pointer to message buffer
 * \param[in] msg_lg size of the message (in bytes)
 * \return int 0 if success, -1 if out of memory, -2 if sending failed, -4 if NBU not initialized yet
 */
int PLATFORM_FwkSrvSendPacket(eFwkSrvMsgType msg_type, void *msg, uint16_t msg_lg);

/*!
 * \brief Send NbuInfo request to NBU and spin waiting for response.
 *
 * \param[in] nbu_info_p pointer to externally allocated NbuInfo_t
 * \return int 0 if OK, -1 in case of Rpmsg error, -10 if NBU did not respond in time.
 */
int PLATFORM_GetNbuInfo(NbuInfo_t *nbu_info_p);

/*!
 * \brief Send NbuInfo request to NBU and spin waiting for response.
 *
 * \return int 0 if OK, < 0 in case of error: -3 if chip revision invalid
 */
int PLATFORM_SendChipRevision(void);

/*!
 * \brief Call API located on the NBU core. This function will wait until the response
 *        from the NBU is received.
 * \param[out] api_return Return status and results from remote API execution
 * \param[in]  api_id API identifier
 * \param[in]  fmt Argument size specifier ending with 0 (ex. {1U,2U,4U,0U} )
 * \param[in]  tab Array of arguments
 * \param[in]  nb_returns Number of bytes returned API status and optional results
 * \return bool_t 0 if OK otherwise error.\n
 *         In case of success, g_nbu_api_ind_status contains the returned value of the API.
 */
bool_t PLATFORM_NbuApiReq(uint8_t *api_return, uint16_t api_id, const uint8_t *fmt, uint32_t *tab, uint32_t nb_returns);

/*!
 * \brief Registers callback triggered when NBU is running out of memory
 *
 * \param[in] cb function pointer to callback. Can be NULL to unregister
 *            the callback.
 */
void PLATFORM_RegisterNbuMemErrorCallback(nbu_memory_error_callback_t cb);

/*!
 * \brief Registers callback to set/release low power constraint requested by the NBU
 *
 * \param[in] callbacks pointer to the callback structure
 *                      WARNING: It will be used directly by the module so DO NOT allocate the structure on the stack!
 */
void PLATFORM_FwkSrvRegisterLowPowerCallbacks(const FwkSrv_LowPowerConstraintCallbacks_t *callbacks);

/*!
 * \brief Sends a new config to the RF_SFC module
 *
 * \param[in] config pointer to the config to send, see sfc_config_t for details
 * \param[in] size size of the config structure
 */
void PLATFORM_FwkSrvSetRfSfcConfig(void *config, uint16_t size);

/*!
 * \brief Register a callback for notification purpose of the SFC module
 *
 * \details In a first step the notifications needs to be enabled with PLATFORM_EnableFroNotificationInfo()
 *
 * \param[in] cb callback that will be used to handle SFC measurement
 */
void PLATFORM_RegisterFroNotificationCallback(PLATFORM_FroDebugCallback_t cb);

/*!
 * \brief Sends a a message to the RF_SFC module to enable notifications. The RF_SFC module will send a message to the
 *       host to update some values, see PLATFORM_FroDebugCallback_t to know what are these values.
 *
 * \details Needs to register a callback via PLATFORM_RegisterFroNotificationCallback() to use the values send by
 *          the controller
 *
 * \param[in] enable
 */
void PLATFORM_EnableFroNotification(int8_t enable);

/*!
 * @}  end of FWK_Platform_ICS addtogroup
 */
/*!
 * @}  end of FWK_Platform_module addtogroup
 */
#endif /* __FWK_PLATFORM_ICS_H__ */
