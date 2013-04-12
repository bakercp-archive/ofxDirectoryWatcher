// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofxDirectoryWatcher.h"


////------------------------------------------------------------------------------
//ofxDirectoryWatcher::ofxDirectoryWatcher(const string& path,
//                                         int eventMask,
//                                         int scanInterval)
//{
//    
//}
//
////------------------------------------------------------------------------------
//ofxDirectoryWatcher::ofxDirectoryWatcher(const ofDirectory& direcotry,
//                                         int eventMask,
//                                         int scanInterval)
//{
//    
//}

ofxDirectoryWatcher::ofxDirectoryWatcher() :
_bIsWatching(false),
_directory(ofDirectory(""))
{
    
}


//------------------------------------------------------------------------------
ofxDirectoryWatcher::~ofxDirectoryWatcher() {
    
}

//------------------------------------------------------------------------------
void ofxDirectoryWatcher::watch(const string& directory,
                                int eventMask,
                                int scanInterval) {
    
    currentWatch = addWatch(directory,
                            new SimpleFileWatchListener(this,events));
}

//------------------------------------------------------------------------------
void ofxDirectoryWatcher::watch(const ofDirectory& directory,
                                int eventMask,
                                int scanInterval) {
    
}

//------------------------------------------------------------------------------
const ofDirectory& ofxDirectoryWatcher::getDirectory() const
{
    return _directory;
}

////------------------------------------------------------------------------------
//int ofxDirectoryWatcher::getEventMask() const
//{
//    return _eventMask;
//}
