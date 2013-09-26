/**
  ******************************************************************************
  * @file    iNEMO_dfu_mal.c
  * @author  ART Team IMS-Systems Lab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief  Generic media access Layer
  *
  * @details
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
#include "iNEMO_dfu_mal.h"
#include "usb_lib.h"
#include "usb_type.h"
#include "iNEMO_usb_desc.h"
#include "flash_if.h"

/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/** @addtogroup DFU_MAL
  * @{
  */

/** @defgroup DFU_MAL_Functions
  * @{
  */



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t (*pMAL_Init) (void);
uint16_t (*pMAL_Erase) (uint32_t SectorAddress);
uint16_t (*pMAL_Write) (uint32_t SectorAddress, uint32_t DataLength);
uint8_t  *(*pMAL_Read)  (uint32_t SectorAddress, uint32_t DataLength);
uint8_t  MAL_Buffer[wTransferSize]; /*!< RAM Buffer for Downloaded Data */

extern ONE_DESCRIPTOR DFU_String_Descriptor[5];

/* The only memory supported in iNEMO is the internal flash*/

static const uint16_t  TimingTable[1][2] =
  {
    {  100 , 104 }, /*!< Internal Flash */
  };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes the Media on the STM32.
  * @param  None.
  * @retval Media Status.
  */

uint16_t MAL_Init(void)
{

  FLASH_If_Init(); /*!< Internal Flash */

  return MAL_OK;
}


/**
  * @brief  Erase sectors.
  * @param  SectorAddress: Address of flash sector to read.
  * @param  DataLength: Length of data to read.
  * @retval Buffer address pointer.
  */

uint16_t MAL_Erase(uint32_t SectorAddress)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Erase = FLASH_If_Erase;
      break;
      
    default:
      return MAL_FAIL;
  }
  return pMAL_Erase(SectorAddress);
}


/**
  * @brief  Write sectors.
  * @param  SectorAddress: Address of flash sector to read.
  * @param  DataLength: Length of data to read.
  * @retval Buffer address pointer.
  */

uint16_t MAL_Write (uint32_t SectorAddress, uint32_t DataLength)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Write = FLASH_If_Write;
      break;

    default:
      return MAL_FAIL;
  }
  return pMAL_Write(SectorAddress, DataLength);
}


/**
  * @brief  Read sectors.
  * @param  SectorAddress: Address of flash sector to read.
  * @param  DataLength: Length of data to read.
  * @retval Buffer address pointer.
  */

uint8_t *MAL_Read (uint32_t SectorAddress, uint32_t DataLength)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Read = FLASH_If_Read;
      break;

    default:
      return 0;
  }
  return pMAL_Read (SectorAddress, DataLength);
}


/**
  * @brief  Get Status.
  * @param  SectorAddress: Address of flash sector to read.
  * @param  Cmd: Type of command.
  * @param  buffer: Buffer address pointer.
  * @retval Media Status.
  */

uint16_t MAL_GetStatus(uint32_t SectorAddress , uint8_t Cmd, uint8_t *buffer)
{
  /* In order to avoid to change the function prototype, the
  evaluation of the x value is left commented. In iNEMO the only memory
  supported is the internal Flash*/
  /* 0x000000000 --> 0, 0x640000000 --> 1, 0x080000000 --> 2 */
//  uint8_t x = (SectorAddress  >> 26) & 0x03 ; 

  uint8_t y = Cmd & 0x01;
  
  SET_POLLING_TIMING(TimingTable[0][y]);  /*!< x: Erase Write Timing y: Media*/
  return MAL_OK;
}


/**
  * @}
  */ /* end of group DFU_MAL_Functions */

/**
  * @}
  */ /* end of group DFU_MAL */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
