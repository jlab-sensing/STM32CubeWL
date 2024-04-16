/**
  ******************************************************************************
  * @file    LmhpPackagesRegistration.c
  * @author  MCD Application Team
  * @brief   Implements the Packages Registration Agent
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020(-2021) STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "LmhpPackagesRegistration.h"
#include "LmHandler.h"
#if (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 1))
#include "LmhpClockSync.h"
#include "LmhpRemoteMcastSetup.h"
#include "LmhpFragmentation.h"
#include "frag_decoder_if.h"
#include "LmhpFirmwareManagement.h"
#elif (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 0))
#if (defined (LORAWAN_ENABLE_CLOCK_SYNC) && (LORAWAN_ENABLE_CLOCK_SYNC == 1))
#include "LmhpClockSync.h"
#endif
#if (defined (LORAWAN_ENABLE_REMOTE_MCAST_SETUP) && (LORAWAN_ENABLE_REMOTE_MCAST_SETUP == 1))
#include "LmhpRemoteMcastSetup.h"
#endif
#if (defined (LORAWAN_ENABLE_FRAGMENTATION) && (LORAWAN_ENABLE_FRAGMENTATION == 1))
#include "LmhpFragmentation.h"
#include "frag_decoder_if.h"
#endif
#endif /* LORAWAN_DATA_DISTRIB_MGT */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Exported functions ---------------------------------------------------------*/
LmHandlerErrorStatus_t LmhpPackagesRegistrationInit( Version_t *fwVersion )
{
#if (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 1))
    if( LmHandlerPackageRegister( PACKAGE_ID_CLOCK_SYNC, NULL ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
    else if( LmHandlerPackageRegister( PACKAGE_ID_REMOTE_MCAST_SETUP, NULL ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
    else if( LmHandlerPackageRegister( PACKAGE_ID_FRAGMENTATION,
                                       ( LmhpFragmentationParams_t * )&FRAG_DECODER_IF_FragmentationParams ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#if (LORAWAN_PACKAGES_VERSION == 2)
    else if( LmHandlerPackageRegister( PACKAGE_ID_FIRMWARE_MANAGEMENT, fwVersion ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#endif /* LORAWAN_PACKAGES_VERSION */
#elif (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 0))
#if (defined (LORAWAN_ENABLE_CLOCK_SYNC) && (LORAWAN_ENABLE_CLOCK_SYNC == 1))
    if( LmHandlerPackageRegister( PACKAGE_ID_CLOCK_SYNC, NULL ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#endif
#if (defined (LORAWAN_ENABLE_REMOTE_MCAST_SETUP) && (LORAWAN_ENABLE_REMOTE_MCAST_SETUP == 1))
    else if( LmHandlerPackageRegister( PACKAGE_ID_REMOTE_MCAST_SETUP, NULL ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#endif
#if (defined (LORAWAN_ENABLE_FRAGMENTATION) && (LORAWAN_ENABLE_FRAGMENTATION == 1))
    else if( LmHandlerPackageRegister( PACKAGE_ID_FRAGMENTATION,
                                       ( LmhpFragmentationParams_t * )&FRAG_DECODER_IF_FragmentationParams ) != LORAMAC_HANDLER_SUCCESS )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#endif
#endif /* LORAWAN_DATA_DISTRIB_MGT */

    return LORAMAC_HANDLER_SUCCESS;
}

LmHandlerErrorStatus_t LmhpPackagesRegister( uint8_t id, LmhPackage_t **package )
{
    if( package == NULL )
    {
        return LORAMAC_HANDLER_ERROR;
    }
#if (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 1))
    switch( id )
    {
        case PACKAGE_ID_CLOCK_SYNC:
            {
                *package = LmhpClockSyncPackageFactory();
                break;
            }
        case PACKAGE_ID_REMOTE_MCAST_SETUP:
            {
                *package = LmhpRemoteMcastSetupPackageFactory();
                break;
            }
        case PACKAGE_ID_FRAGMENTATION:
            {
                *package = LmhpFragmentationPackageFactory();
                break;
            }
        case PACKAGE_ID_FIRMWARE_MANAGEMENT:
            {
                *package = LmhpFirmwareManagementPackageFactory();
                break;
            }
    }
    return LORAMAC_HANDLER_SUCCESS;
#elif (defined (LORAWAN_DATA_DISTRIB_MGT) && (LORAWAN_DATA_DISTRIB_MGT == 0))
    switch( id )
    {
#if (defined (LORAWAN_ENABLE_CLOCK_SYNC) && (LORAWAN_ENABLE_CLOCK_SYNC == 1))
        case PACKAGE_ID_CLOCK_SYNC:
            {
                *package = LmhpClockSyncPackageFactory();
                break;
            }
#endif
#if (defined (LORAWAN_ENABLE_REMOTE_MCAST_SETUP) && (LORAWAN_ENABLE_REMOTE_MCAST_SETUP == 1))
        case PACKAGE_ID_REMOTE_MCAST_SETUP:
            {
                *package = LmhpRemoteMcastSetupPackageFactory();
                break;
            }
#endif
#if (defined (LORAWAN_ENABLE_FRAGMENTATION) && (LORAWAN_ENABLE_FRAGMENTATION == 1))
        case PACKAGE_ID_FRAGMENTATION:
            {
                *package = LmhpFragmentationPackageFactory();
                break;
            }
#endif
    }
    return LORAMAC_HANDLER_SUCCESS;
    
#else
    return LORAMAC_HANDLER_ERROR;
#endif /* LORAWAN_DATA_DISTRIB_MGT */
}
