#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "convert_char_2_hex_data.h"

#define SOURCE_STRING "48656C6C6F2C576F726C6421"    /* Hello,World! */
//#define SOURCE_STRING "4769744875622069732061207765622D626173656420476974207265706F7369746F727920686F7374696E6720736572766963652E"    /* GitHub is a web-based Git repository hosting service. */

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

static int pack_gsm7_string(byte *packed_str, int size_packed_str, byte *gsm7_str, int size_gsm7_str)
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

static int unpack_gsm7_string(byte *unpacked_str, int size_unpacked_str, byte *gsm7_str, int size_gsm7_str)
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

static int convert_char_to_hex(char *src_data, int src_len, char *det_data, int det_len)
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

static int convert_iso8859_to_gsm7(char *iso8859_data, int iso8859_len, char *gsm7_data, int gsm7_len, int *convert_char_num)
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
        printf("DEBUG, gsm7_data[%d]=0x%x.\n", index, *(gsm7_data + index));
    }
#endif
    return SUCCESS;
}

int main(int argc, char *argv[])
{
    char *src_data = SOURCE_STRING;
    char *det_data = NULL;
    byte *gsm7_data = NULL;
    byte *packed_data = NULL;
    byte *unpacked_data = NULL;
    int gsm7_char_num = 0;
    int str_len = 0;
    int rc = SUCCESS;

    str_len = strlen(SOURCE_STRING);
    if (str_len <= 0) {
        printf("Error, String len is zero.\n");
        return FAIL;
    }

    det_data = (char *)malloc(str_len * sizeof(char));
    memset(det_data, '\0', str_len);

    printf("Info, string len is:%d, string is:%s.\n", str_len, src_data);
    rc = convert_char_to_hex(src_data, str_len, det_data, str_len);
    if (rc != SUCCESS) {
        printf("Error, Fail to process convert char to hex.\n");
        return FAIL;
    }

    printf("Info, det string len is:%d, string is:%s.\n", (int)strlen(det_data), det_data);
    gsm7_data = (byte *)malloc(strlen(det_data) * sizeof(byte));
    memset(gsm7_data, '\0', strlen(det_data));
    rc = convert_iso8859_to_gsm7(det_data, strlen(det_data), gsm7_data, strlen(det_data), &gsm7_char_num);
    if (rc != SUCCESS) {
        printf("Error, Fail to process convert char to hex.\n");
        return FAIL;
    }

    printf("Info, gsm7 string len is:%d, string is:%s.\n", (int)strlen(det_data), gsm7_data);
    packed_data = (byte *)malloc(strlen(gsm7_data));
    memset(packed_data, '\0', strlen(gsm7_data));
    rc = pack_gsm7_string(packed_data, strlen(packed_data), gsm7_data, strlen(gsm7_data));
    if (rc != SUCCESS) {
        printf("Error, Fail to process packed gsm7 chars.\n");
        return FAIL;
    }

    unpacked_data = (byte *)malloc(strlen(packed_data));
    memset(unpacked_data, '\0', strlen(packed_data));
    rc = unpack_gsm7_string(unpacked_data, strlen(unpacked_data), packed_data, strlen(packed_data));
    if (rc != SUCCESS) {
        printf("Error, Fail to process unpacked gsm7 chars.\n");
        return FAIL;
    }

    free(unpacked_data);
    free(gsm7_data);
    free(det_data);
    return SUCCESS;
}
