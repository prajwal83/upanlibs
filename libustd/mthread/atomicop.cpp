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

#include <atomicop.h>

namespace upan {
  uint32_t atomic::swap(__volatile__ uint32_t &iLock, uint32_t val) {
    __asm__ __volatile__ ("lock xchgl %0, %1"
    : "=r" ( val )
    : "m"( iLock ), "0" (val)
    : "memory" );

    return val;
  }

  void atomic::add(__volatile__ uint32_t &var, uint32_t val) {
    __asm__ __volatile__ ("lock xaddl %0, %1"
    : "=r"(val)
    : "m"( var ), "0" (val)
    : "memory", "cc");
  }
}