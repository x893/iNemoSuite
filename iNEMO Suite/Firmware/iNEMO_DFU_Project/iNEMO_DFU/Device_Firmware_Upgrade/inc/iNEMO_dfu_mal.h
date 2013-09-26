/**
*
* @file    iNEMO_dfu_mal.h
* @author  ART Team IMS-Systems Lab
* @version V3.2.1
* @date    09/20/2010
* @brief   Header for iNEMO_dfu_mal.c file.
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
*
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INEMO_DFU_MAL_H
#define __INEMO_DFU_MAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "iNEMO_usb_desc.h"

/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/** @defgroup DFU_MAL
  * @{
  */

/** @defgroup DFU_MAL_Prototypes
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MAL_OK   0
#define MAL_FAIL 1
#define MAX_USED_MEDIA 3
#define MAL_MASK 0xFC000000

#define INTERNAL_FLASH_BASE 0x08000000


/* utils macro ---------------------------------------------------------------*/
#define _1st_BYTE(x)  (uint8_t)((x)&0xFF)             /*!< 1st addressing cycle */
#define _2nd_BYTE(x)  (uint8_t)(((x)&0xFF00)>>8)      /*!< 2nd addressing cycle */
#define _3rd_BYTE(x)  (uint8_t)(((x)&0xFF0000)>>16)   /*!< 3rd addressing cycle */
#define _4th_BYTE(x)  (uint8_t)(((x)&0xFF000000)>>24) /*!< 4th addressing cycle */
/* Exported macro ------------------------------------------------------------*/
#define SET_POLLING_TIMING(x)   buffer[1] = _1st_BYTE(x);\
                                buffer[2] = _2nd_BYTE(x);\
                                buffer[3] = _3rd_BYTE(x);  

/* Exported functions ------------------------------------------------------- */

uint16_t MAL_Init (void);
uint16_t MAL_Erase (uint32_t SectorAddress);
uint16_t MAL_Write (uint32_t SectorAddress, uint32_t DataLength);
uint8_t  *MAL_Read (uint32_t SectorAddress, uint32_t DataLength);
uint16_t MAL_GetStatus(uint32_t SectorAddress ,uint8_t Cmd, uint8_t *buffer);

extern uint8_t  MAL_Buffer[wTransferSize]; /*!< RAM Buffer for Downloaded Data */


/**
  * @}
  */ /* end of group DFU_MAL_Prototypes */

/**
  * @}
  */ /* end of group DFU_MAL */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */

#endif /* __INEMO_DFU_MAL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
