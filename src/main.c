/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  main.c
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/

#include "../inc/common.h"
//#include "convert_char_2_hex.h"
//#include "convert_iso8859_2_gsm7.h"
//#include "gsm7_packing_unpacking.h"

/* Only to Debug. */
#define SOURCE_STRING "48656C6C6F2C576F726C6421"    /* Hello,World! */
//#define SOURCE_STRING "4769744875622069732061207765622D626173656420476974207265706F7369746F727920686F7374696E6720736572766963652E"    /* GitHub is a web-based Git repository hosting service. */

struct command_param_info
{
	u_int is_string;
	byte *string;
};

struct command_param_info g_command_param = {0};

/*===========================================================================
  Function:  version
===========================================================================*/
/*!
@brief
  Version number of Gsm 7-bit Tools.

@parameters
  out: Out version information to STD_ERROR.

@return
  None.
*/
/*=========================================================================*/
static void version(FILE * out)
{
    fprintf(out, "Gsm 7-bit Tools version %d.%d.%d\n",
        VERSION_MAJOR, VERSION_MINOR, REVISION_VERSION);
}

/*===========================================================================
  Function:  help
===========================================================================*/
/*!
@brief
  Help information of Gsm 7-bit Tools.

@parameters
  None.

@return
  None.
*/
/*=========================================================================*/
static void help()
{
    version(stderr);
    fprintf(stderr,
        "\n"
        " --help                        - show this help message\n"
        " --version                     - show version num\n"
        );
}

/*===========================================================================
  Function:  usage
===========================================================================*/
/*!
@brief
  Isage information of Gsm 7-bit Tools or say help information.

@parameters
  None.

@return
  None.
*/
/*=========================================================================*/
static int usage()
{
    help();
    return SUCCESS;
}

/*===========================================================================
  Function:  commandline
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
static int commandline(struct command_param_info *info, int argc, char **argv)
{

	if (!info) {
		printf("Error, command param info pointer is NULL.");
		return FAIL;
	}

	/* Detect param number. */
    if (argc == 0) {
        return usage();
    }

	if(!strcmp(argv[0], "-s") || !strcmp(argv[0], "--string")) {
		info->is_string = 1;

		if (argc == 2 && (argv + 1) != NULL) {
			info->string = *(argv + 1);
		} else {
			goto err;
		}
	} else if(!strcmp(argv[0], "--help") || !strcmp(argv[0], "help")) {
        help();
        return SUCCESS;
    } else if(!strcmp(argv[0], "--version") || !strcmp(argv[0], "version")) {
        version(stdout);
        return SUCCESS;
    } else {
		goto err;
	}

#ifdef DEBUG
	printf("Debug, is_string=%d, string is %s.\n", info->is_string, info->string);
#endif
    return SUCCESS;

err:
	usage();
	return FAIL;
}

/*===========================================================================
  Function:  main
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
int main(int argc, char **argv)
{
	struct command_param_info *param_info = &g_command_param;
    //char *src_data = SOURCE_STRING;
    char *det_data = NULL;
    byte *gsm7_data = NULL;
    byte *packed_data = NULL;
    byte *unpacked_data = NULL;
    int gsm7_char_num = 0;
    int rc = SUCCESS;

    /* Prase commandline param. */
    rc = commandline(param_info, argc - 1, argv + 1);
    if (rc != SUCCESS) {
        printf("Error, fail to prase command line.\n");
        return FAIL;
    }

	if (param_info->is_string == 1) {
		u_int str_len = 0;

		str_len = strlen(param_info->string);
		if (str_len <= 0) {
			printf("Error, string len is zero.\n");
			return FAIL;
		}

		printf("Debug, string len is %d.\n", str_len);
		
	}

#if 0
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
#endif
    return SUCCESS;
}
