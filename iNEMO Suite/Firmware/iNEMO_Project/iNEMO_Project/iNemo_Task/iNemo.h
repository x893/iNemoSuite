/**
  * @file    iNemo.h 
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Header for iNEMO.c
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



#ifndef __INEMO_H_
#define __INEMO_H_

/**
 * @defgroup iNEMO_task
 * @{
 */
/* Task priorities. */
#define IN_TASK_PRIORITY			( tskIDLE_PRIORITY + 1 )

/* The check task uses the sprintf function so requires a little more stack. */
#define IN_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 200)

/**
 * @defgroup iNEMO_task_function
 * @{
 */
void inInitTask(void *pvParameters);
void inStartTask(void *pvParameters);

/**
 * @}
 */ /* end of group iNEMO_task_function */ 

/**
 * @}
 */ /* end of group iNEMO_task */ 

#endif /* __INEMO_H_ */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/