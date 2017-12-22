/***************************************************************************
* File:  dcs_convert.h
* Author:  XI Fan <xifan2012@gmail.com>
* Description: 
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2017/12/21      XI Fan             Create Module.
****************************************************************************/

#ifndef _DCS_CONVERT_H_
#define _DCS_CONVERT_H_

/** @brief dcs_convert_pack_gsm7
*
*  Convert coding scheme, pack 8bit to gsm-7bit.
*
*  @param[in] septet: 8bit encode data.
*  @param[in] septet_len: length of 8bit encode data.
*  @param[out] packed_ptr: gsm-7bit encode data, packed from 8bit.
*
*  @return[int]: function failed or success.
*/
extern int dcs_convert_pack_gsm7(uint8 *septet, uint32 septet_len, uint8 *packed_ptr);


/** @brief dcs_convert_unpack_gsm7
*
*  Convert coding scheme, unpack gsm-7bit to 8bit.
*
*  @param[in] octent: gsm-7bit encode data.
*  @param[in] octent_len: length of gsm-7bit encode data.
*  @param[out] unpacked_ptr: 8bit encode data, unpacked from gsm-7bit.
*
*  @return[int]: function failed or success.
*/
extern int dcs_convert_unpack_gsm7(uint8 *octent, uint32 octent_len, uint8 *unpacked_ptr);

#endif /* _DCS_CONVERT_H_ */
