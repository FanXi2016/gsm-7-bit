/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  gsm7_packing_unpacking.h
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/
#ifndef _GSM7_PACKING_UNPACKING_H_
#define _GSM7_PACKING_UNPACKING_H_

#include "common.h"

int pack_gsm7_string(byte *packed_str, u_int size_packed_str, byte *gsm7_str, u_int size_gsm7_str);
int unpack_gsm7_string(byte *unpacked_str, int size_unpacked_str, byte *gsm7_str, int size_gsm7_str);

#endif /* _CONVERT_ISO8859_2_GSM7_H_ */
