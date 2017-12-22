/***************************************************************************
* File:  dcs_log.h
* Author:  XI Fan <xifan2012@gmail.com>
* Description: 
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2017/12/21      XI Fan             Create Module.
****************************************************************************/

#ifndef _DCS_LOG_H_
#define _DCS_LOG_H_


//#define DCS_LOG_PRINTF
#define DCS_LOG_SYSLOG

#if defined (DCS_LOG_PRINTF)
#include <stdio.h>
#elif defined (DCS_LOG_SYSLOG)
#include <sys/syslog.h>
#endif


#ifdef DSC_LOG
#if defined (DCS_LOG_PRINTF)

#define DCS_ERR(...) \
do { \
    //printf("Err,%s", __VA_ARGS__); \
    printf(__VA_ARGS__); \
} while (0)

#define DCS_INFO(...) \
do { \
    //printf("Info,%s", __VA_ARGS__); \
    printf(__VA_ARGS__); \
} while (0)

#define DCS_DEBUG(...) \
do { \
    //printf("Debug,%s", __VA_ARGS__); \
    printf(__VA_ARGS__); \
} while (0)

#elif defined (DCS_LOG_SYSLOG)

#define DCS_ERR(...) \
do { \
    syslog(LOG_ERR,__VA_ARGS__); \
} while (0)

#define DCS_INFO(...) \
do { \
    syslog(LOG_INFO,__VA_ARGS__); \
} while (0)

#define DCS_DEBUG(...) \
do { \
    syslog(LOG_DEBUG,__VA_ARGS__); \
} while (0)

#endif
#else
#define DCS_ERR(tag,...) do {} while(0)
#define DCS_INFO(tag,...) do {} while(0)
#define DCS_DEBUG(tag,...) do {} while(0)
#endif


#endif /* _DCS_LOG_H_ */
