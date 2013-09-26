/**
  * @file    test.c 
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Define the test task. It is the highest priority task. It turns on the LED and checks the LSE.
  *          If it is ok turns off the LED and wait for 500ms. Then it turns on the LED and the test on the microSD.
  *          If the test end with success the user led is turned on for about 2 seconds, otherwise the
  *          the user led blink for a while.
  *          In each case the task exit gracefully and control passes to iNemo application.
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



#include "FreeRTOS.h"
#include "task.h"
#include "iNEMO_lib.h"
#include "test.h"


/** @addtogroup iNEMO_task
  * @{
  */

/** @defgroup Test_Program
  * @{
  */


#define TEST_WAIT_TIME_MS 5000

static void testTaskFunc(void *pvParameters);

/**
 * Implement a generic interface for an user defined task. It is called by the prvSetupHardware
 * function to setup all hardware resource used by the task.
 *
 * @param pvParameters not used
 */
void testInitTask(void *pvParameters)
{
}

/**
 * Implement a generic interface for an user defined task. It is called by the main
 * to allocate the task's software resources needed by FreeRTOS.
 *
 * @param pvParameters not used.
 */
void testStartTask(void *pvParameters)
{
	xTaskCreate(testTaskFunc, "test", TEST_TASK_STACK_SIZE, NULL, TEST_TASK_PRIORITY, NULL);
}

/**
 * The task control function.
 *
 * @param pvParameters non used.
 */
void testTaskFunc(void *pvParameters)
{
  volatile TestStatus status_SDIO = FAILED;
  /*Start the RTC Test*/
   iNEMO_Led_On(LED1);     
  /*Added for RTC test iNEMO*/  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);
  /* Reset Backup Domain */
  BKP_DeInit();
  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}  
  vTaskDelay(500 / portTICK_RATE_MS);
  iNEMO_Led_Off(LED1);
  /*End of RTC test for iNEMO*/    

  /*Start the SD_CARD Test*/
  vTaskDelay(1000 / portTICK_RATE_MS);
  status_SDIO = Test_SDIO();
  if(status_SDIO==PASSED)
  {
    /* keep the user led on for 2 seconds.*/
    iNEMO_Led_On(LED1); 
    vTaskDelay(2000 / portTICK_RATE_MS);
  }
  else
  {
    /* blink the led for a while*/
    for (int i=0; i<5; ++i)
    {
     iNEMO_Led_Toggle(LED1);
      vTaskDelay(500 / portTICK_RATE_MS);
    }
  }
  iNEMO_Led_Off(LED1);
  vTaskDelete(NULL);
}

/**
  * @}
  */ /* end of group Test_Program */

/**
  * @}
  */ /* end of group iNEMO_task */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/