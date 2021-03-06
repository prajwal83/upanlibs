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

#include <stdint.h>

namespace upan {
    namespace atomic {
      class op {
      public:
        static uint32_t swap(__volatile__ uint32_t &iLock, uint32_t val);
        static uint32_t add(__volatile__ uint32_t &var, uint32_t val);
      };

      template <class T>
      class integral {
      public:
        integral(T val) : _val(static_cast<uint32_t>(val)) {}

        T set(T val) {
          return static_cast<T>(op::swap(_val, static_cast<uint32_t>(val)));
        }

        T get() {
          return static_cast<T>(op::add(_val, 0));
        }

        T inc() {
          return static_cast<T>(op::add(_val, 1));
        }

        T dec() {
          return static_cast<T>(op::add(_val, -1));
        }

        T add(uint32_t val) {
          return static_cast<T>(op::add(_val, val));
        }
      private:
        __volatile__ uint32_t _val;
      };
    }
}