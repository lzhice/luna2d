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

package com.stepanp.luna2d;

public class LunaNative
{
	static
	{
		System.loadLibrary("openal");
		System.loadLibrary("luna2d");
	}
	
	public static native boolean isInitialized();
	public static native void initialize(int screenWidth, int screenHeight, 
			String appName, String apkPath, String appFolderPath, String cachePath);
	public static native void deinitialize();
	public static native void reloadAssets();
	public static native void mainLoop();
	
	// Touch events
	public static native void onTouchDown(float x, float y, int touchIndex);
	public static native void onTouchMoved(float x, float y, int touchIndex);
	public static native void onTouchUp(float x, float y, int touchIndex);

	// Pause/resume
	public static native void onPause();
	public static native void onResume();
}
