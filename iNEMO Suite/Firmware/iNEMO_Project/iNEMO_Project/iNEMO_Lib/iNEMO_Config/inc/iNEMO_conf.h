/**
  * @file    iNEMO_conf.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Entry point for iNEMO platform configuration.
  *          Comment the line below to disable the specific sensor and features inclusion 
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



/* Define to prevent recursive inclusion  */
#ifndef __iNEMO_CONF_H
#define __iNEMO_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/**
 * @addtogroup iNEMO_Config
 * @{
 */


/**
*  \brief This defines allows to choose the functions to make 
*         some functions atomic or enter in critical section.
*         In this case we are using the FreeRTOS API
*/
#define FREERTOS


#ifdef FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

#ifdef FREERTOS
#define iNEMO_ENTER_CRITICAL()  taskENTER_CRITICAL()
#define iNEMO_EXIT_CRITICAL()   taskEXIT_CRITICAL()
#elif defined (USER_SCHEDULER)
#define iNEMO_ENTER_CRITICAL()  userENTER_CRITICAL()
#define iNEMO_EXIT_CRITICAL()   userEXIT_CRITICAL()
#elif defined (NO_SCHEDULER)
#define iNEMO_ENTER_CRITICAL()  
#define iNEMO_EXIT_CRITICAL()   
#endif

/* Comment the line below to disable the specific sensor and features inclusion */

/* AHRS Library Available*/
#define AHRS_MOD

/* TRACE Available*/
#define TRACE_MOD

/**Enable 6-axis module  ACC+MAGNETOMETER */
#define _6X

/**Enable Gyroscope PR and Y */
#define  _GYRO_RPY

/**Enable PRESSURE sensor */
#define _PRESS
// /*Enable PRESSURE sensor interrupt1*/
//#define INT1_PAD_ENABLE


/**Enable TEMPERATURE sensor */
#define _TEMP
/*Enable TEMPERATURE sensor */
//#define OS_INT_ENABLE

/** Virtual_COM */
#define _VCOM

/** SDIO */
#define _SDIO

/** USER_LED */
#define _ULED

/** Push_Button */
#define _PBUTT

/**
 * @}
 */ /* end of group iNEMO_Config */ 

#endif /*__iNEMO_CONF_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
