/**
*
* @file     GUI_Layer.h
* @author   IMS Systems Lab - ART Team
* @version V2.2
* @date    01/11/2011
* @brief    Entry point for GUI layer and relative API
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
*
*/

/**
 *  Define to prevent recursive inclusion
*/
#ifndef __GUI_LAYER_H
#define __GUI_LAYER_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/**
 *  \include
*/

#include "stm32f10x.h"
#include "iNEMO_lib.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

// Exported variables
extern u32 count_out;
extern u8 buffer_rx[VIRTUAL_COM_PORT_DATA_SIZE];

/**
 * \addtogroup GUI_Layer
 * \{
 */


/**
* @defgroup FRAME_CONTROL_DEFINE
* @{
*/
#define CTRL_type            0x00 /*!< control frame */
#define DATA_type            0x40 /*!< data frame */
#define ACK_type             0x80 /*!< Ack frame */
#define NACK_type            0xC0 /*!< NACK frame */

#define ACK_req              0x20 /*!< Ack required */
#define ACK_NOTreq           0x00 /*!< NACK required */

#define Last_Frag            0x00 /*!<  Last Fragment */
#define More_Frag            0x10 /*!< More Fragment */

#define Version_1            0x00 /*!< Frame Version */

#define QoS_Normal           0x00 /*!< Data no Ack Last Fragment */
#define Qos_Medium           0x01 /*!< Data with Ack More Fragment */
#define QoS_High             0x02 /*!< Ack no payload */


#define Ctrl_Check(type,ack,frag,vers,QoS) (type | ack | frag | vers | QoS) /*!< macro to build control byte */
#define CTRL_wACK_LF  Ctrl_Check(CTRL_type, ACK_req ,Last_Frag ,Version_1 ,QoS_Normal)  /*!< macro to build control frame with ack , last fragment */
#define CTRL_noACK_LF  Ctrl_Check(CTRL_type, ACK_NOTreq ,Last_Frag ,Version_1 ,QoS_Normal) /*!< macro to build control frame without ack , last fragment */
#define DATA Ctrl_Check(DATA_type, ACK_NOTreq ,Last_Frag ,Version_1 ,QoS_Normal) /*!< macro to build data frame with ack , last fragment */
#define ACK   Ctrl_Check(ACK_type, ACK_NOTreq, Last_Frag ,Version_1 ,QoS_Normal) /*!< macro to build Ack frame */
#define NACK   Ctrl_Check(NACK_type, ACK_NOTreq ,Last_Frag ,Version_1 ,QoS_Normal) /*!< macro to build NACK frame with ack  */
#define TRACE Ctrl_Check(DATA_type, ACK_NOTreq ,Last_Frag ,Version_1 ,Qos_Medium) /*!< macro to build data frame with ack , last fragment, QOS Medium */


/**
* @}
*/ /* end of group FRAME_CONTROL_DEFINE */


/**
* @defgroup ERROR_CODE
* @{
*/

#define  CmdUnsupported     0x01
#define  ValueOutOfRange    0x02
#define  NotExecutable      0x03
#define  WrongSyntax        0x04
#define  iNEMONotConnected   0x05

/**
* @}
*/ /* end of group ERROR_CODE */


/**
* @defgroup MESSAGE_ID
* @{
*/

/**
* @defgroup COMMUNICATION_CONTROL_FRAME
* @{
*/

#define iNEMO_Connect                 0x00
#define iNEMO_Disconnect              0x01
#define iNEMO_Reset_Board             0x02
#define iNEMO_Enter_DFU_Mode          0x03
#define iNEMO_Trace                   0x07
#define iNEMO_Led                     0x08


/**
* @}
*/ /* end of group COMMUNICATION_CONTROL_FRAME */

/**
* @defgroup BOARD_INFO_FRAME
* @{
*/ 


#define iNEMO_Get_Device_Mode         0x10
#define iNEMO_Get_MCU_ID              0x12
#define iNEMO_Get_FW_Version          0x13
#define iNEMO_Get_HW_Version          0x14
#define iNEMO_Identify                0x15
#define iNEMO_Get_AHRS_Library        0x17
#define iNEMO_Get_Libraries           0x18

/**
* @}
*/ /* end of group BOARD_INFO_FRAME */

/**
* @defgroup SENSOR_SETTING_FRAME
* @{
*/

#define iNEMO_Set_Sensor_Parameter             0x20
#define iNEMO_Get_Sensor_Parameter             0x21
#define iNEMO_Restore_Default_Parameter                0x22

/**
* @}
*/ /* end of group SENSOR_SETTING_FRAME */


/**
* @defgroup ACQUISITION_SENSOR_DATA_FRAME
* @{
*/

#define iNEMO_SetOutMode              0x50
#define iNEMO_GetOutMode              0x51
#define iNEMO_Start_Acquisition       0x52
#define iNEMO_Stop_Acquisition        0x53

/**
* @}
*/ /* end of group ACQUISITION_SENSOR_DATA_FRAME */


/**
* @defgroup DEMOS_FRAME
* @{
*/


/**
* @} 
*//* end of group DEMOS_FRAME */

/**
* @}
*/ /* end of group MESSAGE_ID */



/**
 * @defgroup GUI_Layer_Define
 * @{
 */


//  FREQUENCY ACQUISITION VALUES

#define LOW_FREQUENCY         0x00    /*!< 1 HZ frequency acquisition */
#define MEDIUM_FREQUENCY_1    0x01    /*!< 10 HZ frequency acquisition */
#define MEDIUM_FREQUENCY_2    0x02    /*!< 25 HZ frequency acquisition */
#define HIGH_FREQUENCY        0x03    /*!< 50 HZ frequency acquisition */


// FRAME TYPE for PC

/**
* @defgroup FW_HW_Version
* @{
*/

#define iNEMO_FIRMWARE_VERSION	    "iNEMO Firmware_Version_2.2"
#define SIZE_FWversion  strlen(iNEMO_FIRMWARE_VERSION)

#define iNEMO_HARDWARE_VERSION	    "iNEMO V2 Hardware_Version_1"
#define SIZE_HWversion  strlen(iNEMO_HARDWARE_VERSION)

/**
* @}
*/ /* end of group FW_HW_Version */


/**
* @defgroup Libraries_Version
* @{
*/
#ifdef AHRS_MOD
#define iNEMO_AHRS_VERSION	    "iNEMO AHRS ENABLE V1.2.0"
#define iNEMO_AHRS_LIBRARY          0x01
#else
#define iNEMO_AHRS_VERSION          "iNEMO AHRS NOT AVAILABLE"
#define iNEMO_AHRS_LIBRARY	    0x00
#endif
#define SIZE_AHRSlibrary  strlen(iNEMO_AHRS_VERSION)

#ifdef COMPASS_MOD
#define iNEMO_COMPASS_LIBRARY        0x02
#else
#define iNEMO_COMPASS_LIBRARY	     0x00
#endif

#ifdef ALTIMETER_MOD
#define iNEMO_ALTIMETER_LIBRARY      0x04
#else
#define iNEMO_ALTIMETER_LIBRARY	     0x00
#endif

#ifdef TRACE_MOD
#define iNEMO_TRACE_LIBRARY          0x08
#else
#define iNEMO_TRACE_LIBRARY	     0x00
#endif

#ifdef FAT_MOD
#define iNEMO_FAT_LIBRARY            0x10
#else
#define iNEMO_FAT_LIBRARY	     0x00
#endif


#define AVAILABLE_LIBRARIES     (iNEMO_AHRS_LIBRARY | iNEMO_COMPASS_LIBRARY | \
                                  iNEMO_ALTIMETER_LIBRARY | iNEMO_TRACE_LIBRARY |\
                                  iNEMO_FAT_LIBRARY) /*!< macro to build available libraries */

/**
* @} 
*/  /* end of group Libraries_Version */

/**
* @}
*/ /* end of group GUI_Layer_Define */

/**
* @defgroup GUI_Layer_API
* @{
*/ 

void Send_Ack(unsigned char frame, u8 length, u8* payload);
void Send_Nack(unsigned char frame, u8 error_code);
void Send_Data(unsigned char frame, u8 length, u8* payload);
void Send_Trace(unsigned char frame, u8 length, u8* payload);
void Set_Timer(unsigned char number);
void ParseGuiFrame(u32 nFrameSize, iNEMO_DATA * pdata);
void DataProcess(u8 outmode, iNEMO_DATA *pData);

void SetAhrs(bool bEnable);
void SetRawData(bool bEnable);
bool GetAhrs();
bool GetRawData();
void SetOutMode(u8 outmode);
u8 GetOutMode();
void SetTraceEnabled(bool bEnable);
bool GetTraceEnabled();

/**
 * @}
 */ /* end of group GUI_Layer_API */

/**
 * \}
 */ /* end of group GUI_Layer */

#endif /*__GUI_LAYER_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
