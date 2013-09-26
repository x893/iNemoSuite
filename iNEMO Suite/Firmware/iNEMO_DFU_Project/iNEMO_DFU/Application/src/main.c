/**
  * @file    main.c 
  * @author  ART Team IMS-Systems Lab
  * @version V2.0.0
  * @date    09/20/2010
  * @brief   iNEMO Device Firmware Upgrade (DFU) main program body.
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
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "iNEMO_usb_prop.h"
#include "usb_pwr.h"
#include "iNEMO_dfu_mal.h"
#include "iNEMO_dfu.h"
#include "iNEMO_usb_common.h"


/** @defgroup iNEMO_DFU_Program
  * @{
  */

/** @defgroup iNEMO_DFU_Application
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;


/* Private function prototypes -----------------------------------------------*/
void Set_System(void);


/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */ 
  
DFU_Button_Config();
  
#ifdef Enable_SW_Mode
  /* Check if the Key push-button on iNEMO Board is pressed or the Option Byte is 0*/
   if ( (DFU_Button_Read() != 0x00) && (Option_Byte_Read() != 0x01))
#else
  /* Check if the Key push-button on iNEMO Board is pressed */
   if (DFU_Button_Read() != 0x00)
#endif     
  { /* Test if user code is programmed starting from address 0x8003000 */
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    { /* Jump to user application */

      JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) ApplicationAddress);
      Jump_To_Application();
    }
  } /*!< Otherwise enters DFU mode to allow user to program his application */

#ifdef Enable_SW_Mode
  /*Delete the Option Byte*/
  if(Option_Byte_Read()==0x01)
  {
    Leave_DFU_SW_Mode();
  }
#endif 
  
  
  /* Enter DFU mode */
  DeviceState = STATE_dfuERROR;
  DeviceStatus[0] = STATUS_ERRFIRMWARE;
  DeviceStatus[4] = DeviceState;

  Set_System();
  Set_USBClock();
  USB_Init();

  /* Main loop */
  while (1)
  {}
}



/**
  * @brief  Configures USB Cable.
  * @param  None
  * @retval None
  */
void Set_System(void)
{
  /* Unlock the internal flash */
  FLASH_Unlock();

  /* Configure the USB Disconnect Pin */
  iNEMO_USB_Disconnet_Pin_Config();
  
  /*Disable the USB Cable*/
  USB_Cable_Config(DISABLE);

  
  /* Init the media interface */
  MAL_Init();
  
  /*Enable the USB Cable*/
  USB_Cable_Config(ENABLE);

}


#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/**
  * @}
  */ /* end of group iNEMO_DFU_Application */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
