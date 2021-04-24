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

#include <RawImage.h>

namespace upanui {
  RawImage::RawImage(const Image& image) : _imageBuffer(nullptr) {
    _width = image.width();
    _height = image.height();
    auto size = _width * _height;
    _imageBuffer.reset(new uint32_t[size]);
    memcpy(_imageBuffer.get(), image.frameBuffer(), size);
  }

  int dcompare(double a, double b) {
    const int32_t ai = a * 100;
    const int32_t  bi = b * 100;
    return ai < bi ? -1 : ai > bi ? 1 : 0;
  }

  uint32_t dround(double v) {
    const uint32_t a = v * 100;
    auto m = a % 100;
    if (m < 50) {
      return v;
    } else {
      return (uint32_t)v + 1;
    }
  }

  RawImage::RawImage(const Image& image, uint32_t newWidth, uint32_t newHeight) : _imageBuffer(nullptr) {
    _width = newWidth;
    _height = newHeight;
    auto size = _width * _height;
    _imageBuffer.reset(new uint32_t[size]);

    const auto srcWidth = image.width();
    const auto srcHeight = image.height();

    const double fx = srcWidth * 1.0 / _width;
    const double fy = srcHeight * 1.0 / _height;

    const double fa = 1.0 / (fx * fy);

    const auto srcImgBuffer = image.frameBuffer();
    auto destImgBuffer = _imageBuffer.get();

    for(uint32_t y = 0; y < _height; ++y) {
      for(uint32_t x = 0; x < _width; ++x) {
        double dr = 0;
        double dg = 0;
        double db = 0;
        double da = 0;

        uint32_t sy = y * fy;
        double scy = y * fy;

        for(double sfy = fy; dcompare(sfy, 0.0) != 0 && sy < srcHeight;) {
          auto dy = sy + 1 - scy;
          const auto pycmp = dcompare(dy, sfy);
          if (pycmp < 0) {
            ++sy;
            scy = sy;
            sfy -= dy;
          } else if(pycmp == 0) {
            ++sy;
            scy = sy;
            sfy = 0;
          } else {
            dy = sfy;
            scy += dy;
            sfy = 0;
          }

          uint32_t sx = x * fx;
          double scx = x * fx;
          for (double sfx = fx; dcompare(sfx, 0.0) != 0 && sx < srcWidth;) {
            auto dx = sx + 1 - scx;
            const auto pxcmp = dcompare(dx, sfx);
            if (pxcmp < 0) {
              ++sx;
              scx = sx;
              sfx -= dx;
            } else if(pxcmp == 0) {
              ++sx;
              scx = sx;
              sfx = 0;
            } else {
              dx = sfx;
              scx += dx;
              sfx = 0;
            }

            double ipf = dx * dy * fa;
            uint32_t srcRGB = srcImgBuffer[sx + sy * srcWidth];

            da += ((srcRGB >> 24) & 0xFF) * ipf;
            dr += ((srcRGB >> 16) & 0xFF) * ipf;
            dg += ((srcRGB >> 8) & 0xFF) * ipf;
            db += (srcRGB & 0xFF) * ipf;
          }
        }
        destImgBuffer[x + y * _width] = dround(dr) << 16 | dround(dg) << 8 | dround(db) | dround(da) << 24; //0xFF000000;
      }
    }
  }

  RawImage::~RawImage() noexcept {
  }
}
