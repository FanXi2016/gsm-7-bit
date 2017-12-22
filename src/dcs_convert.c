/***************************************************************************
* File:  dcs_convert.c
* Author:  XI Fan <xifan2012@gmail.com>
* Description: 
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2017/12/21      XI Fan             Create Module.
****************************************************************************/

#include "dcs_log.h"
#include "dcs_comdef.h"

#include "dcs_convert.h"

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
int dcs_convert_pack_gsm7(uint8 *septet, uint32 septet_len, uint8 *packed_ptr)
{
    uint32 packed_idx = 0;
    uint32 septet_idx = 0;
    uint8 shift = 0;

    if (!septet || !packed_ptr) {
        DCS_ERR("Err, The septet and packed_ptr is NULL.\n");
        return -1;
    }

    while (septet_idx < septet_len) {
        shift = septet_idx & 0x07;

        *(packed_ptr + packed_idx) = ((*(septet + septet_idx) >> shift) | (*(septet + septet_idx + 1) << (7 - shift)));

        if (shift == 6) {
            septet_idx++;
        }
        septet_idx++;
        packed_idx++;
    }

    return 0;
}

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
int dcs_convert_unpack_gsm7(uint8 *octent, uint32 octent_len, uint8 *unpacked_ptr)
{
    byte prev_char = 0;
    byte curr_char = 0;
    uint32 unpacked_idx = 0;
    uint32 octent_idx = 0;
    uint8 shift = 0;
    
    if (!octent || !unpacked_ptr) {
        DCS_ERR("Err, The octent and unpacked_ptr is NULL.\n");
        return FAIL;
    }

    while (octent_idx < octent_len) {
        shift = unpacked_idx & 0x07;
        curr_char = *(octent + octent_idx);

        *(unpacked_ptr + unpacked_idx) = ((curr_char << shift) | (prev_char >> (8 - shift))) & 0x7F;

        if (shift == 6) {
            unpacked_idx++;
            *(unpacked_ptr + unpacked_idx) = curr_char >> 1;
        }

        octent_idx++;
        unpacked_idx++;
        prev_char = curr_char;
    }

    return SUCCESS;
}
