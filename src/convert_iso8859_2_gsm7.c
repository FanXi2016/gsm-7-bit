/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  convert_iso8859_2_gsm7.c
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/

#include "convert_iso8859_2_gsm7.h"

/* This table maps the ISO 8859-1 character set to the GSM 7-bit character set
** of 3GPP TS 23.038.  Characters mapped to ESC (0x1b) cannot be represented in
** this alphabet.  Some may be representable using the basic character set
** extension of 3GPP TS 23.038, but we are currently not doing that mapping.
*/
#define ESC 0x1b
static const char iso8859_to_gsm7[] = 
{
/* 0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */
 ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC,0x0a, ESC, ESC,0x0d, ESC, ESC, /* 0 */
 ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, /* 1 */ 
0x20,0x21,0x22,0x23,0x02,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f, /* 2 */
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f, /* 3 */
0x00,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f, /* 4 */
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a, ESC, ESC, ESC, ESC,0x11, /* 5 */
0x2f,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f, /* 6 */
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a, ESC, ESC, ESC, ESC, ESC, /* 7 */
 ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, /* 8 */
 ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, /* 9 */
0x20,0x40, ESC,0x01,0x24,0x03, ESC,0x5f, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, /* a */
 ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC, ESC,0x60, /* b */
 ESC, ESC, ESC, ESC,0x5b,0x0e,0x1c,0x09, ESC,0x1f, ESC, ESC, ESC, ESC, ESC, ESC, /* c */
 ESC,0x5d, ESC, ESC, ESC, ESC,0x5c, ESC,0x0b, ESC, ESC, ESC,0x5e, ESC, ESC,0x1e, /* d */
0x7f, ESC, ESC, ESC,0x7b,0x0f,0x1d, ESC,0x04,0x05, ESC, ESC,0x07, ESC, ESC, ESC, /* e */
 ESC,0x7d,0x08, ESC, ESC, ESC,0x7c, ESC,0x0c,0x06, ESC, ESC,0x7e, ESC, ESC, ESC  /* f */
};

/*===========================================================================
  Function:  convert_iso8859_to_gsm7
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
int convert_iso8859_to_gsm7(byte *iso8859_data, u_int iso8859_len, byte *gsm7_data, u_int gsm7_len, u_int *convert_char_num)
{
    char gsm7_char = 0;
    int iso8859_idx = 0;
    int gsm7_idx = 0;

    if (!iso8859_data || !gsm7_data) {
        printf("Error, The iso8859 data and gsm7 data pointer is NULL.\n");
        return FAIL;
    }

    while (iso8859_idx < iso8859_len)
    {
        if (iso8859_idx >= gsm7_len) {
            printf("Error, The gsm7 data buffer was not long enough fo the conversion.\n");
            return FAIL;
        }
        
        /* Convert from ISO8859 to GSM7 */
        gsm7_char = iso8859_to_gsm7[iso8859_data[iso8859_idx]];
        if (gsm7_char == ESC) {
            gsm7_char = '?';
        }

        gsm7_data[gsm7_idx++] = gsm7_char;
        iso8859_idx++;
    }

    if (convert_char_num) {
        *convert_char_num = gsm7_idx;
    }

#ifdef DEBUG
    int index = 0;
    for (index = 0; index < *convert_char_num; index++) {
        printf("Debug, gsm7_data[%d]=0x%x.\n", index, *(gsm7_data + index));
    }
    printf("\n");
#endif
    return SUCCESS;
}
