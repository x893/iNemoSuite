/**
  * @file    usb_pwr.c 
  * @author  MCD Application Team & SystemsLab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief   Connection/disconnection & power management.
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

/** @defgroup Virtual_Com_Power_Management
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t bDeviceState = UNCONNECTED; /* USB device status */
__IO bool fSuspendEnabled = TRUE;  /* true when suspend is possible */

struct
{
  __IO RESUME_STATE eState;
  __IO uint8_t bESOFcnt;
}ResumeS;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**
  * @brief  USB power ON Routine
  * @param  None
  * @retval USB_SUCCESS
  */

RESULT PowerOn(void)
{
#ifndef STM32F10X_CL
  uint16_t wRegVal;

  /*** cable plugged-in ? ***/
  USB_Cable_Config(ENABLE);

  /*** CNTR_PWDN = 0 ***/
  wRegVal = CNTR_FRES;
  _SetCNTR(wRegVal);

  /*** CNTR_FRES = 0 ***/
  wInterrupt_Mask = 0;
  _SetCNTR(wInterrupt_Mask);
  /*** Clear pending interrupts ***/
  _SetISTR(0);
  /*** Set interrupt mask ***/
  wInterrupt_Mask = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;
  _SetCNTR(wInterrupt_Mask);
#endif /* STM32F10X_CL */

  return USB_SUCCESS;
}


/**
  * @brief  Handles switch-off conditions
  * @param  None
  * @retval USB_SUCCESS
  */

RESULT PowerOff()
{
#ifndef STM32F10X_CL
  /* disable all ints and force USB reset */
  _SetCNTR(CNTR_FRES);
  /* clear interrupt status register */
  _SetISTR(0);
  /* Disable the Pull-Up*/
  USB_Cable_Config(DISABLE);
  /* switch-off device */
  _SetCNTR(CNTR_FRES + CNTR_PDWN);
#endif /* STM32F10X_CL */

  /* sw variables reset */
  /* ... */

  return USB_SUCCESS;
}


/**
  * @brief  Sets suspend mode operating conditions
  * @param  None
  * @retval None
  */

void Suspend(void)
{
#ifndef STM32F10X_CL
  uint16_t wCNTR;
  /* suspend preparation */
  /* ... */

  /* macrocell enters suspend mode */
  wCNTR = _GetCNTR();
  wCNTR |= CNTR_FSUSP;
  _SetCNTR(wCNTR);
#endif /* STM32F10X_CL */

  /* ------------------ ONLY WITH BUS-POWERED DEVICES ---------------------- */
  /* power reduction */
  /* ... on connected devices */

#ifndef STM32F10X_CL
  /* force low-power mode in the macrocell */
  wCNTR = _GetCNTR();
  wCNTR |= CNTR_LPMODE;
  _SetCNTR(wCNTR);
#endif /* STM32F10X_CL */

  /* switch-off the clocks */
  /* ... */
  Enter_LowPowerMode();

}


/**
  * @brief  Handles wake-up restoring normal operations
  * @param  None
  * @retval None
  */

void Resume_Init(void)
{
#ifndef STM32F10X_CL
  uint16_t wCNTR;
#endif /* STM32F10X_CL */ 

  /* ------------------ ONLY WITH BUS-POWERED DEVICES ---------------------- */
  /* restart the clocks */
  /* ...  */

#ifndef STM32F10X_CL
  /* CNTR_LPMODE = 0 */
  wCNTR = _GetCNTR();
  wCNTR &= (~CNTR_LPMODE);
  _SetCNTR(wCNTR);
#endif /* STM32F10X_CL */ 

  /* restore full power */
  /* ... on connected devices */
  Leave_LowPowerMode();

#ifndef STM32F10X_CL
  /* reset FSUSP bit */
  _SetCNTR(IMR_MSK);
#endif /* STM32F10X_CL */

  /* reverse suspend preparation */
  /* ... */

}


/**
  * @brief  This is the state machine handling resume operations and
  *         timing sequence. The control is based on the Resume structure
  *         variables and on the ESOF interrupt calling this subroutine
  *         without changing machine state.
  * @param  A state machine value (RESUME_STATE)
  *         RESUME_ESOF doesn't change ResumeS.eState allowing
  *         decrementing of the ESOF counter in different states.
  * @retval None
  */

void Resume(RESUME_STATE eResumeSetVal)
{
#ifndef STM32F10X_CL
  uint16_t wCNTR;
#endif /* STM32F10X_CL */

  if (eResumeSetVal != RESUME_ESOF)
    ResumeS.eState = eResumeSetVal;

  switch (ResumeS.eState)
  {
    case RESUME_EXTERNAL:
      Resume_Init();
      ResumeS.eState = RESUME_OFF;
      break;
    case RESUME_INTERNAL:
      Resume_Init();
      ResumeS.eState = RESUME_START;
      break;
    case RESUME_LATER:
      ResumeS.bESOFcnt = 2;
      ResumeS.eState = RESUME_WAIT;
      break;
    case RESUME_WAIT:
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0)
        ResumeS.eState = RESUME_START;
      break;
    case RESUME_START:
     #ifdef STM32F10X_CL
      OTGD_FS_SetRemoteWakeup();
     #else 
      wCNTR = _GetCNTR();
      wCNTR |= CNTR_RESUME;
      _SetCNTR(wCNTR);
     #endif /* STM32F10X_CL */
      ResumeS.eState = RESUME_ON;
      ResumeS.bESOFcnt = 10;
      break;
    case RESUME_ON:
    #ifndef STM32F10X_CL      
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0)
      {
     #endif /* STM32F10X_CL */    
       #ifdef STM32F10X_CL
        OTGD_FS_ResetRemoteWakeup();
       #else
        wCNTR = _GetCNTR();
        wCNTR &= (~CNTR_RESUME);
        _SetCNTR(wCNTR);
       #endif /* STM32F10X_CL */
        ResumeS.eState = RESUME_OFF;
     #ifndef STM32F10X_CL
      }
     #endif /* STM32F10X_CL */
      break;
    case RESUME_OFF:
    case RESUME_ESOF:
    default:
      ResumeS.eState = RESUME_OFF;
      break;
  }
}

/**
  * @}
  */ /* end of group Virtual_Com_Power_Management */

/**
  * @}
  */ /* end of group iNEMO_Virtual_Com */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
