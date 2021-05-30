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

#include <timer_thread.h>
#include <mosstd.h>
#include <exception.h>

namespace upan {
  timer_thread::timer_thread(uint32_t interval_ms)
    : _timer_interval_ms(interval_ms),
      _state(not_running),
      _error(upan::option<upan::error>::empty()) {
  }

  timer_thread::~timer_thread() {
    stop();
  }

  void timer_callback(void* obj) {
    auto t = static_cast<timer_thread*>(obj);
    try {
      while (t->state() != timer_thread::stopped) {
        if (t->state() == timer_thread::running) {
          t->on_timer_trigger();
        }
        sleepms(t->interval());
      }
    } catch(const exception& e) {
      t->set_error(e.Error());
    }
    t->stop();
  }

  void timer_thread::run() {
    mutex_guard g(_timer_mutex);
    switch(_state.get()) {
      case not_running:
        _state.set(running);
        exect(timer_callback, this);
        break;
      case paused:
        _state.set(running);
        break;
      case running:
        throw exception(XLOC, "timer is already running");
      case stopped:
        throw exception(XLOC, "timer has stopped - can't run again");
      default:
        throw exception(XLOC, "timer is in unknown state: %d", _state);
    }
  }

  void timer_thread::pause() {
    mutex_guard g(_timer_mutex);
    switch(_state.get()) {
      case running:
        _state.set(paused);
        break;
      case paused:
        break;
      case not_running:
        throw exception(XLOC, "timer is not running - can't pause");
      case stopped:
        throw exception(XLOC, "timer has stopped - can't pause");
      default:
        throw exception(XLOC, "timer is in unknown state: %d", _state);
    }
  }

  void timer_thread::stop() {
    _state.set(stopped);
  }

  void timer_thread::set_error(const upan::error& e) {
    mutex_guard g(_timer_mutex);
    _error = e;
  }
}
