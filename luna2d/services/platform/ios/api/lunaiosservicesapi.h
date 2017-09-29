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

#import <Foundation/Foundation.h>
#import "lunaioscustomappdelegate.h"

@interface LUNAIosServicesApi : NSObject

// Check for config has value with given name
+(BOOL) hasConfigValue: (NSString*) name;

// Get string value from config
+(NSString*) getConfigString: (NSString*) name;

// Get int value from config
+(int) getConfigInt: (NSString*) name;

// Get float value from config
+(float) getConfigFloat: (NSString*) name;

// Get bool value from config
+(BOOL) getConfigBool: (NSString*) name;

// Get array value from config
+(NSArray*) getConfigArray: (NSString*) name;

// Add delegate to handle events from UIApplication
+(void) addCustomAppDelegate: (id<LUNAIosCustomAppDelegate>) delegate;

// Pause/resume engine with showing loading indicator during pause
+(void) setPauseWithLoadingIndicator: (BOOL) pause;

@end
