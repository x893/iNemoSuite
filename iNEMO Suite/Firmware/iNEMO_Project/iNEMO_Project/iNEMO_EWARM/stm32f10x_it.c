/**
  * @file    stm32f10x_it.c 
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief    Main Interrupt Service Routines.
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
#include "stm32f10x_it.h"
#include "iNEMO_lib.h"

/** @defgroup Interrupt_Service_Routines
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Cortex_M3_Exceptions_Handlers
  * @{
  */


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
      //User_Led_On();
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
 //       User_Led_On();
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
        //User_Led_On();
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
          //  User_Led_On();

  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
        //User_Led_On();
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{

}
/**
  * @}
  */ /* end of group Cortex_M3_Exceptions_Handlers */




/** @defgroup STM32F10x_Peripherals_Interrupt_Handlers
  * @{
  */


/**
  * @brief  This function handles SDIO global interrupt request.
  * @param  None
  * @retval : None
  */

void SDIO_IRQHandler(void)
{
#ifdef _SDIO
  /* Process All SDIO Interrupt Sources */
  SD_ProcessIRQSrc();
#endif
}

/**
  * @brief  This function handles External interrupt Line 1 request.
  * @param  None
  * @retval : None
  */


void EXTI1_IRQHandler(void)
{
#ifdef OS_INT_ENABLE
	//write here the ISR for the OS_INT of the STLM75

	// Clear the IRQ pending bit
	EXTI_ClearITPendingBit(STLM75_INT_EXTI_Line);
#endif
}


/**
  * @brief  This function handles External interrupt Line 3 request.
  * @param  None
  * @retval : None
  */

void EXTI3_IRQHandler(void)
{

}


/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval : None
  */

void EXTI9_5_IRQHandler(void)
{
#ifdef INT1_PAD_ENABLE
	//write here the ISR for the INT2_PAD of the LPS001DL

	// Clear the IRQ pending bit
	EXTI_ClearITPendingBit(LPS001DL_INT1_EXTI_Line);
#endif

#ifdef _MAG_DRDY
	//write here the ISR for the _MAG_DRDY of the LSM303DLH

	// Clear the IRQ pending bit
	EXTI_ClearITPendingBit(MAG_DRDY_EXTI_Line);
#endif

}

/**
  * @}
  */ /* end of group STM32F10x_Peripherals_Interrupt_Handlers */

/**
  * @}
  */ /* end of group Interrupt_Service_Routines */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
