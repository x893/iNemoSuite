/**
  * @file    usb_endp.c 
  * @author  MCD Application Team & SystemsLab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief   Endpoint routines.
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
#include "virtual_com.h"

/** @addtogroup iNEMO_Virtual_Com
  * @{
  */

/** @defgroup Endpoint_Routines
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 buffer_rx[VIRTUAL_COM_PORT_DATA_SIZE];
u32 count_out = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  EP3_Out callback
  * @param  None
  * @retval None
  */

void EP3_OUT_Callback(void)
{
  count_out = GetEPRxCount(ENDP3);
  PMAToUserBufferCopy(buffer_rx, ENDP3_RXADDR, count_out);
  SetEPRxValid(ENDP3);

}

/**
  * @brief  EP1_IN callback
  * @param  None
  * @retval None
  */


void EP1_IN_Callback(void)
{

}

/**
  * @}
  */ /* end of group Endpoint_Routines */

/**
  * @}
  */ /* end of group iNEMO_Virtual_Com */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

