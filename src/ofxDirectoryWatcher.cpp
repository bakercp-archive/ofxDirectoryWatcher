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

//------------------------------------------------------------------------------
ofxDirectoryWatcher::ofxDirectoryWatcher()
: _bIsWatching(false)
, _directory(ofDirectory(""))
{
}


//------------------------------------------------------------------------------
ofxDirectoryWatcher::~ofxDirectoryWatcher()
{
}

//------------------------------------------------------------------------------
void ofxDirectoryWatcher::setup(const string& directory,
                                bool bListItemsOnStartup,
                                int eventMask,
                                int scanInterval)
{

    setup(ofDirectory(directory),
          bListItemsOnStartup,
          eventMask,
          scanInterval);
}

//------------------------------------------------------------------------------
void ofxDirectoryWatcher::setup(const ofDirectory& directory,
                                bool bListItemsOnStartup,
                                int eventMask,
                                int scanInterval)
{
    try {

        if(!_bIsWatching) {
            _bIsWatching = true;
            _currentWatch = addWatch(directory.getAbsolutePath(),this);
            if(bListItemsOnStartup) {
                ofDirectory myDirectory(directory);
                size_t numFiles = myDirectory.listDir();
                for(size_t i = 0; i < numFiles; i++) {
                    ofFile f = myDirectory[i];
                    ofxDirectoryItemEvent event(f,DW_ITEM_ADDED);
                    ofNotifyEvent(events.onDirectoryItemAdded,event,this);
                }
            }
        } else {
            ofLogError("ofxDirectoryWatcher::watch") << "Already watching " << directory.getAbsolutePath();
        }
    } catch(const Poco::FileNotFoundException& exc) {
        ofNotifyEvent(events.onDirectoryScanError,exc,this);
        _bIsWatching = false;
    }
}

//------------------------------------------------------------------------------
const ofDirectory& ofxDirectoryWatcher::getDirectory() const
{
    return _directory;
}
