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

#include <LayerCanvas.h>
#include <cdisplay.h>
#include <CanvasBuilder.h>

namespace upanui {
  LayerCanvas::LayerCanvas() {
    FramebufferInfo fb;
    get_framebuffer_info(&fb);

    _width = fb._width;
    _height = fb._height;

    _frameBuffer.reset(new uint32_t[_width * _height]);
  }

  LayerCanvas::~LayerCanvas() noexcept {
    for(auto c : _canvasLayers) {
      delete c;
    }
  }

  void LayerCanvas::addCanvas(const CanvasBuilder& builder) {
    _canvasLayers.push_back(&builder.create(*this));
  }
}