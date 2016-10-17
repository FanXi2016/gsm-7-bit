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

#include "common.h"
#include "convert_char_2_hex.h"
#include "convert_iso8859_2_gsm7.h"
#include "gsm7_packing_unpacking.h"

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
        " -s, --string <input string>           - convert input string to packed gsm-7bit code\n"
        "     --help                            - show this help message\n"
        "     --version                         - show version num\n"
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
	printf("Debug, is_string=%d, string is: %s\n", info->is_string, info->string);
    printf("\n");
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
	u_int str_len = 0;
	byte *hex_data = NULL;
	byte *gsm7_data = NULL;
	byte *packed_data = NULL;
	u_int gsm7_char_num = 0;
    int rc = SUCCESS;

    /* Prase commandline param. */
    rc = commandline(param_info, argc - 1, argv + 1);
    if (rc != SUCCESS) {
        printf("Error, fail to prase command line.\n");
        return FAIL;
    }

	if (param_info->is_string == 1) {

		str_len = strlen(param_info->string);
		if (str_len <= 0) {
			printf("Error, string len is zero.\n");
			return FAIL;
		}

		hex_data = (byte *)malloc(str_len * sizeof(byte));
		memset(hex_data, '\0', str_len);
		rc = convert_string_to_hex(param_info->string, str_len, hex_data, str_len);
		if (rc != SUCCESS) {
			printf("Error, fail to convert string to hex.\n");
			goto err_hex_data;
		}

		gsm7_data = (byte *)malloc(str_len * sizeof(byte));
		memset(gsm7_data, '\0', str_len);
		/* Convert ISO8859-1/ASCII code to Gsm 7-bit code. */
		rc = convert_iso8859_to_gsm7(hex_data, str_len, gsm7_data, str_len, &gsm7_char_num);
		if (rc != SUCCESS) {
			printf("Error, Fail to process convert char to hex.\n");
			goto err_gsm7_data;
		}

		packed_data = (byte *)malloc(str_len);
	    memset(packed_data, '\0', str_len);
		/* Packing Gsm 7-bit. */
		rc = pack_gsm7_string(packed_data, str_len, gsm7_data, str_len);
		if (rc != SUCCESS) {
			printf("Error, Fail to process packed gsm7 chars.\n");
			goto err_packed_data;
		}

	}

	return SUCCESS;

err_packed_data:
	free(packed_data);
err_gsm7_data:
	free(gsm7_data);
err_hex_data:
	free(hex_data);
err:
	return FAIL;
}
