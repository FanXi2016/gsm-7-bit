/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  convert_char_2_hex.c
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/

#include "convert_char_2_hex.h"

/*===========================================================================
  Function:  convert_char_to_hex
===========================================================================*/
/*!
@brief
  None.

@parameters
  None.

@return
  None.
*/
/*=========================================================================*/
int convert_char_to_hex(char *src_data, int src_len, char *det_data, int det_len)
{
    char convert_char = 0;
    int src_idx = 0;
    int det_idx = 0;

    if (!src_data || !det_data) {
        printf("Error, The source data and detect data pointer is NULL.\n");
        return FAIL;
    }

    while (src_idx < src_len)
    {
        if (det_idx >= det_len) {
            printf("Error, The destination buffer was not long enough fo the conversion.\n");
            return FAIL;
        }

        if (*(src_data + src_idx) >= '0' && *(src_data + src_idx) <= '9') {
            convert_char = *(src_data + src_idx) - '0';
        } else if (*(src_data + src_idx) >= 'a' && *(src_data + src_idx) <= 'f') {
            convert_char = *(src_data + src_idx) - 'a' + 10;
        } else if (*(src_data + src_idx) >= 'A' && *(src_data + src_idx) <= 'F') {
            convert_char = *(src_data + src_idx) - 'A' + 10;
        } else {
            printf("Error, Have illegality char [%c].\n", *(src_data + src_idx));
            return FAIL;
        }

        if ((src_idx % 2) == 0) {
            *(det_data + det_idx) = convert_char << 4;
        } else {
            *(det_data + det_idx) |= convert_char;
        }

        det_idx += (src_idx % 2);
        src_idx++;
    }

#ifdef DEBUG
    int index = 0;
    for (index = 0; index < det_idx; index++) {
        printf("DEBUG, det_data[%d]=0x%x.\n", index, *(det_data + index));
    }
#endif

    printf("Info, Convert data is: %s.\n", det_data);
    return SUCCESS;
}