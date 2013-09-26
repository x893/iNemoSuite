/**
  * @file    iNEMO_AHRS_MemMan_1.c 
  * @author  ART Team IMS-Systems Lab
  * @version V1.2.0 [FW v2.0.0]
  * @date    09/20/2010
  * @brief   This file implements the Memory Manager of the AHRS of iNEMO.
  *          This file should be added to your Project any time you would use the 
  *          standard malloc and free functions.
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
#ifndef __iNEMO_AHRS_MEMMAN_H
#define __iNEMO_AHRS_MEMMAN_H


/* Memory Allocation Functions ---------------------------------------------- */

#include <stdlib.h>

/** @addtogroup iNEMO_AHRS
  * @{
  */

/** @defgroup iNEMO_MEM_MAN_1
  * @{
  */


/**
  * @brief  Memory allocate manager for iNEMO
  * @param  size:memory size to allocate
  * @retval Pointer to the allocated memory or NULL in case of fail
  */
void *iNEMO_Malloc(size_t size)
{ 
  return malloc(size);
}

/**
  * @brief  Memory de-allocate manager for iNEMO.
  * @param  Pointer to the allocated memory.
  * @retval None
  */
void iNEMO_Free(void *p)
{
  free(p);
}

/**
 * @}
 */ /* end of group iNEMO_MEM_MAN_1 */

/**
 * @}
 */ /* end of group iNEMO_AHRS */

#endif 
/* __iNEMO_AHRS_MEMMAN_H */