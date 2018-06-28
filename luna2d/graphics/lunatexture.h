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

#include "lunagl.h"
#include "lunaglhelpers.h"
#include "lunaimage.h"
#include "lunaassets.h"

namespace luna2d{

class LUNATexture : public LUNAAsset
{
	LUNA_USERDATA_DERIVED(LUNAAsset, LUNATexture)

public:
	// Construct texture from image data
	LUNATexture(const LUNAImage& image);

	// Construct empty texture
	LUNATexture(int width, int height, LUNAColorType colorType);

	virtual ~LUNATexture();

private:
	int width, height;
	LUNAColorType colorType;
	GLuint id = 0;

private:
	void InitFromImageData(const std::vector<unsigned char>& data);

public:
	// Get sizes in pixels
	int GetWidth() const;
	int GetHeight() const;

	// Get sizes in game points (scaled to virtual resoultion)
	float GetWidthPoints() const;
	float GetHeightPoints() const;

	GLuint GetId() const;
	bool IsValid() const; // Check for texture is valid. Can be invalid after loss GL context

	void SetNearestFilter();
	void SetLinearFilter();

	void Bind() const;
	void Unbind() const;

// Reload texture when application lost OpenGL context
// SEE: "lunaassets.h"
#if LUNA_PLATFORM == LUNA_PLATFORM_ANDROID
private:
	std::string reloadPath; // Path to reload texture data
	int cacheId = 0;

public:
	const std::string& GetReloadPath()
	{
		return reloadPath;
	}

	inline void SetReloadPath(const std::string& path)
	{
		reloadPath = path;
		LUNAEngine::SharedAssets()->SetAssetReloadable(this, true); // Add this texture to reloadable assets
	}

	inline virtual void Reload()
	{
		if(reloadPath.empty()) return;

		// Generated textures reloads direcly from cached data
		if(cacheId != 0)
		{
			auto data = LUNAEngine::SharedFiles()->ReadCompressedFile(reloadPath, LUNAFileLocation::APP_FOLDER);
			if(!data.empty())
			{
				InitFromImageData(data);
				return;
			}
		}

		// Usual textures reload from assets
		else
		{
			std::string ext = LUNAEngine::SharedFiles()->GetExtension(reloadPath);
			std::unique_ptr<LUNAImageFormat> format;

			// Select image format to decode
			if(ext == "png") format = std::unique_ptr<LUNAPngFormat>(new LUNAPngFormat());

			// Reload texture from path
			if(format)
			{
				LUNAImage image(reloadPath, *format, LUNAFileLocation::ASSETS);
				if(!image.IsEmpty())
				{
					InitFromImageData(image.GetData());
					return;
				}
			}
		}

		LUNA_LOGE("Cannot reload texture from path \"%s\"", reloadPath.c_str());
	}

	inline void Cache(const std::vector<unsigned char>& data, bool makeReloadable = true)
	{
		cacheId = LUNAEngine::SharedAssets()->CacheTexture(data, cacheId);
		reloadPath = ".luna2d_gentexture_" + std::to_string(cacheId);
		if(makeReloadable) LUNAEngine::SharedAssets()->SetAssetReloadable(this, true);
	}
#endif

};

}
