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

#pragma once

#include "lunaengine.h"
#include "lunatextureregion.h"

namespace luna2d{

class LUNAFrameBuffer : public LUNAAsset
{
	LUNA_USERDATA_DERIVED(LUNAAsset, LUNAFrameBuffer)

public:
	LUNAFrameBuffer(int viewPortWidth, int viewPortHeight, LUNAColorType colorType);
	~LUNAFrameBuffer();

private:
	GLuint id = 0;
	GLint prevId = 0;
	int viewportWidth, viewportHeight;
	std::shared_ptr<LUNATexture> texture;

public:
	GLuint GetId();
	int GetViewportWidth();
	int GetViewportHeight();
	std::shared_ptr<LUNATexture> GetTexture();
	std::shared_ptr<LUNATextureRegion> GetTextureRegion();
	std::shared_ptr<LUNAImage> ReadPixels();
	void Bind();
	void Unbind();

// Recreate framebuffer and reload attached texture when application lost OpenGL context
// SEE: "lunaassets.h"
#if LUNA_PLATFORM == LUNA_PLATFORM_ANDROID
private:
	bool needCache = false;

public:
	virtual void Reload();
	virtual void Cache();
#endif
};

}
