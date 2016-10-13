/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  gsm7_packing_unpacking.c
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/

#include "gsm7_packing_unpacking.h"

/*===========================================================================
  Function:  pack_gsm7_string
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
int pack_gsm7_string(byte *packed_str, int size_packed_str, byte *gsm7_str, int size_gsm7_str)
{
    int packed_idx = 0;
    int gsm7_idx = 0;
    char shift = 0;

    if (!packed_str || !gsm7_str) {
        printf("Error, The packed strings and gsm7 strings pointer is NULL.\n");
        return FAIL;
    }

    while (gsm7_idx < size_gsm7_str)
    {
        shift = gsm7_idx & 0x07;

        *(packed_str + packed_idx) = ((*(gsm7_str + gsm7_idx) >> shift) | (*(gsm7_str + gsm7_idx + 1) << (7 - shift)));
/*
#ifdef DEBUG
        printf("DEBUG, (*(gsm7_str + gsm7_idx) >> shift)=0x%x.\n", (*(gsm7_str + gsm7_idx) >> shift));
        printf("DEBUG, (*(gsm7_str + gsm7_idx + 1) << (7 - shift))=0x%x.\n", (*(gsm7_str + gsm7_idx + 1) << (7 - shift)));
#endif
*/
        if (shift == 6) {
            gsm7_idx++;
        }
        gsm7_idx++;
        packed_idx++;
    }

#ifdef DEBUG
    int index = 0;
    for (index = 0; index < packed_idx; index++) {
        printf("DEBUG, packed_str[%d]=0x%x.\n", index, packed_str[index]);
    }
#endif

    return SUCCESS;
}

/*===========================================================================
  Function:  pack_gsm7_string
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
int unpack_gsm7_string(byte *unpacked_str, int size_unpacked_str, byte *gsm7_str, int size_gsm7_str)
{
    byte prev_char = 0;
    byte curr_char = 0;
    int unpacked_idx = 0;
    int gsm7_idx = 0;
    char shift = 0;

    if (!unpacked_str || !gsm7_str) {
        printf("Error, The unpacked strings and gsm7 strings pointer is NULL.\n");
        return FAIL;
    }

    while (gsm7_idx < size_gsm7_str)
    {
        shift = unpacked_idx & 0x07;
        curr_char = *(gsm7_str + gsm7_idx);
/*
#ifdef DEBUG
        printf("DEBUG, shift=%d, prev_char=0x%x, curr_char=0x%x.\n", shift, prev_char, curr_char);
#endif
*/
        *(unpacked_str + unpacked_idx) = ((curr_char << shift) | (prev_char >> (8 - shift))) & 0x7F;

        if (shift == 6) {
            unpacked_idx++;
            *(unpacked_str + unpacked_idx) = curr_char >> 1;
        }

        gsm7_idx++;
        unpacked_idx++;
        prev_char = curr_char;
    }

#ifdef DEBUG
    int index = 0;
    for (index = 0; index < unpacked_idx; index++) {
        printf("DEBUG, unpacked_str[%d]=0x%x.\n", index, unpacked_str[index]);
    }
#endif

    return SUCCESS;
}
