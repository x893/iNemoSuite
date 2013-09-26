/**
  * @file    flash_if.c 
  * @author  MCD Application Team
  * @version V3.2.1
  * @date    04/07/2010
  * @brief  specific media access Layer for internal flash.
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


/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"
#include "iNEMO_dfu_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/** @addtogroup Flash_Interface
  * @{
  */

/** @defgroup Flash_Interface_Functions
  * @{
  */

/**
  * @brief  Initializes the Media on the STM32.
  * @param  None.
  * @retval Media Status.
  */

uint16_t FLASH_If_Init(void)
{
  return MAL_OK;
}

/**
  * @brief  Erase sector.
  * @param  SectorAddress: Address of flash sector to erase.
  * @retval Media Status.
  */

uint16_t FLASH_If_Erase(uint32_t SectorAddress)
{
  FLASH_ErasePage(SectorAddress);
  return MAL_OK;
}


/**
  * @brief  Write sectors.
  * @param  SectorAddress: Address of flash sector to write.
  * @param  DataLength: Length of data to write.
  * @retval Media Status.
  */

uint16_t FLASH_If_Write(uint32_t SectorAddress, uint32_t DataLength)
{
  uint32_t idx = 0;
  
  if  (DataLength & 0x3) /* Not an aligned data */
  {
    for (idx = DataLength; idx < ((DataLength & 0xFFFC) + 4); idx++)
    {
      MAL_Buffer[idx] = 0xFF;
    }
  }
  /* Data received are Word multiple */

  for (idx = 0; idx <  DataLength; idx = idx + 4)
  {
    FLASH_ProgramWord(SectorAddress, *(uint32_t *)(MAL_Buffer + idx));
    SectorAddress += 4;
  }
  return MAL_OK;
}

/**
  * @brief  Read sectors.
  * @param  SectorAddress: Address of flash sector to read.
  * @param  DataLength: Length of data to read.
  * @retval Buffer address pointer.
  */

uint8_t *FLASH_If_Read (uint32_t SectorAddress, uint32_t DataLength)
{
  return  (uint8_t*)(SectorAddress);
}


/**
  * @}
  */ /* end of group Flash_Interface_Functions */

/**
  * @}
  */ /* end of group Flash_Interface */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
