//-----------------------------------------------------------------------------
// luna2d engine
// Copyright 2014-2017 Stepan Prokofjev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "lunacolor.h"

using namespace luna2d;

LUNAColor::LUNAColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

LUNAColor::LUNAColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

unsigned char LUNAColor::GetR() const
{
	return r * 255;
}

unsigned char LUNAColor::GetG() const
{
	return g * 255;
}

unsigned char LUNAColor::GetB() const
{
	return b * 255;
}

unsigned char LUNAColor::GetA() const
{
	return a * 255;
}

// Get color as uint32_t
uint32_t LUNAColor::GetUint32() const
{
	uint32_t color = 0;

	color |= GetR() << 24;
	color |= GetG() << 16;
	color |= GetB() << 8;
	color |= GetA();

	return color;
}

// Convert value from byte format(0-255) to float format(0.0f-1.0f)
float LUNAColor::ByteToFloat(unsigned char value)
{
	return value / 255.0f;
}

// Values from 0 to 255
LUNAColor LUNAColor::Rgb(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return LUNAColor(ByteToFloat(r), ByteToFloat(g), ByteToFloat(b), ByteToFloat(a));
}

// Values from 0.0f to 1.0f
LUNAColor LUNAColor::RgbFloat(float r, float g, float b, float a)
{
	return LUNAColor(r, g, b, a);
}

// From hex format(0xRRGGBB), alpha is optional
LUNAColor LUNAColor::Hex(int hex, float a)
{
	unsigned char byteA = (hex >> 16) & 0xFF;
	unsigned char byteB = (hex >> 8) & 0xFF;
	unsigned char byteC = hex & 0xFF;

	return LUNAColor(ByteToFloat(byteA), ByteToFloat(byteB), ByteToFloat(byteC), a);
}

// From hex string "#RRGGBB" or "RRGGBB", alpha is optional
LUNAColor LUNAColor::HexString(const std::string hexStr, float a)
{
	if(hexStr.size() != 6 && hexStr.size() != 7) return {};

	int first = 0;

	if(hexStr.size() == 7)
	{
		if(hexStr[0] == '#') first = 1;
		else return {};
	}

	return LUNAColor::Hex(std::strtol(hexStr.c_str() + first, nullptr, 16), a);
}

// From uint32_t
LUNAColor LUNAColor::Uint32(uint32_t color)
{
	unsigned char r = (color >> 24) & 0xFF;
	unsigned char g = (color >> 16) & 0xFF;
	unsigned char b = (color >> 8) & 0xFF;
	unsigned char a = color & 0xFF;

	return LUNAColor(ByteToFloat(r), ByteToFloat(g), ByteToFloat(b), ByteToFloat(a));
}

// Initialize requently used colors
LUNAColor LUNAColor::WHITE = RgbFloat(1, 1, 1);
LUNAColor LUNAColor::BLACK = RgbFloat(0, 0, 0);
LUNAColor LUNAColor::GRAY = RgbFloat(0.5f, 0.5f, 0.5f);
LUNAColor LUNAColor::RED = RgbFloat(1, 0, 0);
LUNAColor LUNAColor::GREEN = RgbFloat(0, 1, 0);
LUNAColor LUNAColor::BLUE = RgbFloat(0, 0, 1);
LUNAColor LUNAColor::YELLOW = RgbFloat(1, 1, 0);
LUNAColor LUNAColor::CYAN = RgbFloat(0, 1, 1);
LUNAColor LUNAColor::PURPLE = RgbFloat(1, 0, 1);
LUNAColor LUNAColor::TRANSPARENT = RgbFloat(1, 1, 1, 0.0f);
