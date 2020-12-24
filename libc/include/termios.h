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
#ifndef _TERMIOS_H_
#define _TERMIOS_H_

typedef unsigned tcflag_t ;
typedef unsigned char cc_t ;

#define NCCS 20

#if defined __cplusplus
extern "C" {
#endif

typedef enum
{
	ECHO,
	ECHONL,

	ICRNL,
	INLCR,
	IGNCR,

	ONLCR
} termios_consts ;

struct termios
{
	tcflag_t c_iflag ; // input modes
	tcflag_t c_oflag ; // output modes
	tcflag_t c_cflag ; // control modes
	tcflag_t c_lflag ; // local modes
	cc_t c_cc[NCCS] ; // control chars
} ;

#if defined __cplusplus
}
#endif

#endif
