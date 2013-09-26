/**
  * @file    utils.c 
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   This file includes some utility functions
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



/**
 * \include
 */
#include "utils.h"

/**
* \defgroup Utils
* \{
*/

/** \addtogroup Utils_Function
 *  \{
*/

/**
 * \brief  Compute two integer value a and b such that n = a * b. It used to
 *                  setup the timer to generate an IRQ whit a specified frequency n.
 * \param  n : the specified frequency
 * \param  a : prescaler factor
 * \param  b : period factor
 * \retval None
*/

void prvFindFactors(u32 n, u16 *a, u16 *b)
{
	/** This function is copied from the ST STR7 library and is
	 * copyright STMicroelectronics.  Reproduced with permission.
	*/

	u16 b0;
	u16 a0;
	long err, err_min=n;


	*a = a0 = ((n-1)/0xffff) + 1;
	*b = b0 = n / *a;

	for (; *a < 0xffff-1; (*a)++)
	{
		*b = n / *a;
		err = (long)*a * (long)*b - (long)n;
		if (abs(err) > (*a / 2))
		{
			(*b)++;
			err = (long)*a * (long)*b - (long)n;
		}
		if (abs(err) < abs(err_min))
		{
			err_min = err;
			a0 = *a;
			b0 = *b;
			if (err == 0) break;
		}
	}

	*a = a0;
	*b = b0;
}

/**
 * \brief  Inserts a delay time
 * \param  nCount: specifies the delay time length
 * \retval None
*/

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/**
 *  \brief Copy one buffer to another
 *  \param pBufferOrigin
 *  \param pBufferDestination
 *  \param NBOfBytes : number of bytes to copy
 *  \retval None
 */
void CopyBuffer(unsigned char* pBufferOrigin, unsigned char* pBufferDestination,  u8 NBOfBytes)
{
  while(NBOfBytes!=0)
  {
    NBOfBytes--;
    *pBufferDestination=*pBufferOrigin;
    pBufferDestination++;
    pBufferOrigin++;
  }
}

/**
 *  \brief Put in a buffer as u8 an s16.
 *  \param refvalue : s16 recipient
 *  \param pBufferDestination : u8 buffer destination
 *  \retval None
 */

void s16_to_u8_buffer(s16* refvalue, unsigned char* pBufferDestination)
{
  u16 tmp=0x00;
  tmp = (u16)(*refvalue);
  *pBufferDestination=(u8)(tmp>>8);
  pBufferDestination++;
  *pBufferDestination=(u8)tmp;

}

/**
 *  \brief Put in a buffer as u8 an u16.
 *  \param refvalue : u16 recipient
 *  \param pBufferDestination : u8 buffer destination
 *  \retval None
 */
void u16_to_u8_buffer(u16* refvalue, unsigned char* pBufferDestination)
{
  u16 tmp=0x00;
  tmp = (u16)(*refvalue);
  *pBufferDestination=(u8)(tmp>>8);
  pBufferDestination++;
  *pBufferDestination=(u8)tmp;
}

/**
 *  \brief Compares two buffers
 *  \param pBuffer1 : buffers to be compared
 *  \param pBuffer2 : buffers to be compared
 *  \retval TestStatus :  PASSED if  pBuffer1 is identical to pBuffer2; or FAILED if pBuffer1 id differs from pBuffer2
 */

TestStatus Buffercmp(u32* pBuffer1, u32* pBuffer2, u16 BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

/**
 *  \brief Fills buffer with user predefined data
 *  \param pBuffer : pointer on the Buffer to fill
 *  \param BufferLenght : size of the buffer to fill
 *  \param Offset : first value to fill on the Buffer
 *  \retval None
 */

void Fill_Buffer(u32 *pBuffer, u16 BufferLenght, u32 Offset)
{
  u16 index = 0;

  /* Put in global buffer same values */
  for (index = 0; index < BufferLenght; index++ )
  {
    pBuffer[index] = index + Offset;
  }
}
/**
 *  \brief Checks if a buffer has all its values are equal to zero
 *  \param pBuffer :  buffer to be compared.
 *  \param BufferLenght : buffer's length
 *  \retval TestStatus : PASSED pBuffer values are zero
 *                 		 FAILED At least one value from pBuffer buffer is diffrent
 *                          from zero.
 */

TestStatus eBuffercmp(u32* pBuffer, u16 BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer != 0x00)
    {
      return FAILED;
    }

    pBuffer++;
  }

  return PASSED;
}

/**
  * brief: Copy the four byte of a float, into a buffer starting from a position
  * @param pBuffer
  * @param t : the float to copy into the buffer
  * @retval None
  */

void Float_To_Buffer(float t, u8* pBuffer)
{
 char* s;
 s=(char*)(&t);

 for(int i=3;i>=0;i--)
 {
  pBuffer[i]=(char) (*s);
  s++;
 }
}

/**
  * brief: Copy four byte of a buffer into a float.
  * @param t : the float to copy into the buffer
  * @param pBuffer
  * @retval None
  */
void Buffer_To_Float(u8* pBuffer, float t)
{
 char* s;
 s=(char*)(&t);
 for(int i=0;i<4;i++)
 {
  *s=pBuffer[i];
   s++;
 }
}
/**
 * }
 */ /* end of group Utils_Function */

/**
 * @}
 */ /* end of group Utils */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
