/**
  * @file    flash_if.h 
  * @author  MCD Application Team
  * @version V3.2.1
  * @date    07/05/2010
  * @brief   Header for flash_if.c file.
  * @details
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
  * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
  * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_MAL_H
#define __FLASH_IF_MAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @defgroup Device_Firmware_Upgrade
  * @{
  */

/** @defgroup Flash_Interface
  * @{
  */

/** @defgroup Flash_Interface_Prototypes
  * @{
  */

uint16_t FLASH_If_Init(void);
uint16_t FLASH_If_Erase (uint32_t SectorAddress);
uint16_t FLASH_If_Write (uint32_t SectorAddress, uint32_t DataLength);
uint8_t *FLASH_If_Read (uint32_t SectorAddress, uint32_t DataLength);

/**
  * @}
  */ /* end of group Flash_Interface_Prototypes */

/**
  * @}
  */ /* end of group Flash_Interface */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */

#endif /* __FLASH_IF_MAL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
