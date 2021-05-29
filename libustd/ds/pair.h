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
#pragma once

#include <utility.h>

namespace upan {

template <typename F, typename S>
class pair
{
	public:
		pair(const F& f, const S& s) : first(f), second(s) { }
    pair(F&& f, S&& s) : first(move(f)), second(move(s)) { }
		F first;
		S second;
};

template <typename F, typename S>
__inline__ pair<F, S> make_pair(F f, S s)
{
  return pair<F, S>(f, s);
}

};