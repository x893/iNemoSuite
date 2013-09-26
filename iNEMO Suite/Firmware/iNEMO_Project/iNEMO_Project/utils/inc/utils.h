/**
  * @file    utils.h 
  * @author  ART Team IMS-Systems Lab
  * @version V2.0.0
  * @date    09/20/2010
  * @brief   Header for utils.c
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




/** \def
 *  Define to prevent recursive inclusion
 */
#ifndef __UTILS_H
#define __UTILS_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/**
 * \include
 * */
#include "stm32f10x.h"


/** \addtogroup Utils
 *  \{
*/

/** @enum TestStatus
*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/**\def
 *  Computes the absolute value of its argument \a x.
*/
#define abs(a) ((a)>0?(a):-(a))

/**\def
 *  Define the UID Address and a pointer to it.
*/
#define U_ID_Base_Register_Address   (0x1FFFF7E8)
#define MCU_ID ((const unsigned char *)(U_ID_Base_Register_Address))



/** \addtogroup Utils_Function
 *  \{
*/
void prvFindFactors(u32 n, u16 *a, u16 *b);
void Delay(vu32 nCount);
void CopyBuffer(unsigned char* pBufferOrigin, unsigned char* pBufferDestination,  u8 NBOfBytes);
void s16_to_u8_buffer(s16* refvalue, unsigned char* pBufferDestination);
void u16_to_u8_buffer(u16* refvalue, unsigned char* pBufferDestination);
void Fill_Buffer(u32 *pBuffer, u16 BufferLenght, u32 Offset);
TestStatus Buffercmp(u32* pBuffer1, u32* pBuffer2, u16 BufferLength);
TestStatus eBuffercmp(u32* pBuffer, u16 BufferLength);
void Float_To_Buffer(float t, u8* pBuffer);
void Buffer_To_Float(u8* pBuffer,float t);

/**
 * \}
 */ /* end of group Utils_Function */ 

/**
 * \}
 */ /* end of group Utils */ 
#endif /* __UTILS_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
