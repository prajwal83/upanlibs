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
#ifndef _UPAN_UNIQ_PTR_H_
#define _UPAN_UNIQ_PTR_H_

#include <string.h>
#include <StringUtil.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

namespace upan {

template <typename T>
class uniq_ptr
{
  private:
    uniq_ptr(const uniq_ptr&) = delete;
    uniq_ptr& operator=(const uniq_ptr&) = delete;
    
    void destroy()
    {
      if(_owner)
      {
        delete _ptr;
        _ptr = nullptr;
      }
    }

  public:
    uniq_ptr(T* ptr) : _ptr(ptr), _owner(true)
    {
    }

    ~uniq_ptr()
    {
      destroy();
    }

    void disown() { _owner = false; }

    T* get() { return _ptr; }
    T* operator->() { return get(); }
    T& operator*() { return *get(); }

    T* release()
    {
      auto r = _ptr;
      _ptr = nullptr;
      return r;
    }

    void reset(T* newPtr)
    {
      if(_ptr != newPtr)
      {
        destroy();
        _ptr = newPtr;
      }
    }

  private:
    T* _ptr;
    bool _owner;
};

template <typename T>
class uniq_ptr<T[]>
{
  private:
    uniq_ptr(const uniq_ptr&) = delete;
    uniq_ptr& operator=(const uniq_ptr&) = delete;

    void destroy()
    {
      if(_owner)
      {
        delete[] _ptr;
        _ptr = nullptr;
      }
    }

  public:
    uniq_ptr(T* ptr) : _ptr(ptr), _owner(true)
    {
    }

    ~uniq_ptr()
    {
      destroy();
    }

    void disown() { _owner = false; }

    T* get() { return _ptr; }
    T& operator[](int index) { return _ptr[index]; }
    const T& operator[](int index) const { return _ptr[index]; }

    T* release()
    {
      auto r = _ptr;
      _ptr = nullptr;
      return r;
    }

    void reset(T* newPtr)
    {
      if(_ptr != newPtr)
      {
        destroy();
        _ptr = newPtr;
      }
    }

  private:
    T* _ptr;
    bool _owner;
};

};

#endif
