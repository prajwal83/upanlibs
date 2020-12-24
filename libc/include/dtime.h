/*
 *	Upanix - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *                                                                          
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                          
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                          
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */
#ifndef _DTIME_H_
#define _DTIME_H_

#if defined __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef unsigned time_t ;
typedef int clock_t ;

typedef struct
{
	byte bSecond ;
	byte bMinute ;
	byte bHour ;

	byte bDayOfWeek ;
	byte bDayOfMonth ;
	byte bMonth ;
	byte bCentury ;
	byte bYear ;
} RTCTime ;

struct tm
{
	int tm_sec;         /* seconds */
	int tm_min;         /* minutes */
	int tm_hour;        /* hours */

	int tm_wday;        /* day of the week */
	int tm_mday;        /* day of the month */
	int tm_mon;         /* month */
	int tm_year;        /* year */
//	int tm_yday;        /* day in the year */
//	int tm_isdst;       /* daylight saving time */
} ;

extern void SysUtil_GetDateTime(RTCTime* pRTCTime) ;
#define dtime(prtc) SysUtil_GetDateTime(prtc)

time_t time(time_t * t) ;
int localtime(struct tm* t, const time_t* time) ;

struct timeval
{
	time_t tSec ;
//  unsigned uimSec ;
} PACKED ;

#define HRS_IN_DAY (86400)
extern void SysUtil_GetDateTime(RTCTime* pRTCTime) ;

#define dtime(prtc) SysUtil_GetDateTime(prtc)

int gettimeofday(struct timeval*) ;

// As per POSIX...
#define CLOCKS_PER_SEC 1000000
clock_t clock() ;


#if defined __cplusplus
}
#endif


#endif
