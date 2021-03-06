/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  convert_iso8859_2_gsm7.h
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/
#ifndef _CONVERT_ISO8859_2_GSM7_H_
#define _CONVERT_ISO8859_2_GSM7_H_

#include "common.h"

int convert_iso8859_to_gsm7(byte *iso8859_data, u_int iso8859_len, byte *gsm7_data, u_int gsm7_len, u_int *convert_char_num);


#endif /* _CONVERT_ISO8859_2_GSM7_H_ */
