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


#pragma once


#include "Poco/Exception.h"
#include "FileWatcher.h"
#include "ofLog.h"
#include "ofEvents.h"
#include "ofFileUtils.h"


using Poco::Exception;


// will eventually be an alias for Poco::DirectoryWatcher
enum ofxDirectoryEventType
{
    DW_ITEM_ADDED = 1,
    /// A new item has been created and added to the directory.

    DW_ITEM_REMOVED = 2,
    /// An item has been removed from the directory.

    DW_ITEM_MODIFIED = 4,
    /// An item has been modified.

    DW_ITEM_MOVED_FROM = 8,
    /// An item has been renamed or moved. This event delivers the old name.

    DW_ITEM_MOVED_TO = 16,
    /// An item has been renamed or moved. This event delivers the new name.
};


class ofxDirectoryItemEvent {
public:
    ofxDirectoryItemEvent(const ofFile& _item, ofxDirectoryEventType _event) :
    item(_item),
    event(_event)
    {
    }
    
    const ofFile& item;
    ofxDirectoryEventType event;
};


class ofxDirectoryItemMoveEvent : public ofxDirectoryItemEvent {
public:
    ofxDirectoryItemMoveEvent(const ofFile& _item,
                          ofxDirectoryEventType _event,
                          const ofFile& _from,
                          const ofFile& _to)
    : ofxDirectoryItemEvent(_item, _event)
    , from(_from)
    , to(_to)
    {
    }

    const ofFile& from;
    const ofFile& to;
};


class ofxDirectoryEvents {
public:
    ofxDirectoryEvents() { }
    virtual ~ofxDirectoryEvents() { }
    
    ofEvent<const ofxDirectoryItemEvent> onDirectoryItemAdded;
    ofEvent<const ofxDirectoryItemEvent> onDirectoryItemRemoved;
    ofEvent<const ofxDirectoryItemEvent> onDirectoryItemModified;
    ofEvent<const ofxDirectoryItemMoveEvent> onDirectoryItemMovedFrom;
    ofEvent<const ofxDirectoryItemMoveEvent> onDirectoryItemMovedTo;
    ofEvent<const Exception>         onDirectoryScanError;
    
};

//class ofxDirectoryWatcher;
//
//
//class SimpleFileWatchListener : public FileWatchListener {
//public:
//    SimpleFileWatchListener(ofxDirectoryWatcher* p, ofxDirectoryEvents& events)
//    : _p(p)
//    , _events(events)
//    {
//    }
//    
//    virtual ~SimpleFileWatchListener() {}
//    
//    void handleFileAction(WatchID watchid,
//                          const string& dir,
//                          const string& filename,
//                          FileWatcher::Action action) {
//        ofxDirectoryEventType evt = (ofxDirectoryEventType)0;
//        ofFile f(dir + filename);
//
//        // not all events are supported yet
//        if(action == FileWatcher::Add) {
//            evt = DW_ITEM_ADDED;
//            ofxDirectoryItemEvent event(f,evt);
//            ofNotifyEvent(_events.onDirectoryItemAdded,event,_p);
//        } else if(action == FileWatcher::Delete) {
//            evt = DW_ITEM_REMOVED;
//            ofxDirectoryItemEvent event(f,evt);
//            ofNotifyEvent(_events.onDirectoryItemRemoved,event,_p);
//        } else if(action == FileWatcher::Modified) {
//            evt = DW_ITEM_MODIFIED;
//            ofxDirectoryItemEvent event(f,evt);
//            ofNotifyEvent(_events.onDirectoryItemModified,event,_p);
//        } else {
//            ofLogError("SimpleFileWatchListener::handleFileAction") << "Unknown FileWatcher::Action: " << action;
//        }
//    }
//
//private:
//    ofxDirectoryWatcher* _p;
//    ofxDirectoryEvents& _events;
//};


class ofxDirectoryWatcher : public FileWatcher, public FileWatchListener {
public:
    
    enum DirectoryEventMask {
		DW_FILTER_ENABLE_ALL = 31,
        /// Enables all event types.
        
		DW_FILTER_DISABLE_ALL = 0
        /// Disables all event types.
	};

    enum {
		DW_DEFAULT_SCAN_INTERVAL = 5 /// Default scan interval for platforms that don't provide a native notification mechanism.
	};

    ofxDirectoryWatcher();
    
    void setup(const string& directory,
               bool bListItemsOnStartup = false,
               int eventMask = DW_FILTER_ENABLE_ALL,
               int scanInterval = DW_DEFAULT_SCAN_INTERVAL);

    void setup(const ofDirectory& directory,
               bool bListItemsOnStartup = false,
               int eventMask = DW_FILTER_ENABLE_ALL,
               int scanInterval = DW_DEFAULT_SCAN_INTERVAL);
    
    virtual ~ofxDirectoryWatcher();

    const ofDirectory& getDirectory() const;
	int getEventMask() const;
    
    ofxDirectoryEvents events;

    template<class ListenerClass>
    void RegisterBrowseServiceEvents(ListenerClass * listener){
        ofAddListener(events.onDirectoryItemAdded,       listener, &ListenerClass::onDirectoryItemAdded);
        ofAddListener(events.onDirectoryItemRemoved,     listener, &ListenerClass::onDirectoryItemRemoved);
        ofAddListener(events.onDirectoryItemModified,    listener, &ListenerClass::onDirectoryItemModified);
        ofAddListener(events.onDirectoryItemMovedFrom,   listener, &ListenerClass::onDirectoryItemMovedFrom);
        ofAddListener(events.onDirectoryItemMovedTo,     listener, &ListenerClass::onDirectoryItemMovedTo);
        ofAddListener(events.onDirectoryScanError,       listener, &ListenerClass::onDirectoryScanError);
    }

    template<class ListenerClass>
    void UnregisterBrowseServiceEvents(ListenerClass * listener){
        ofRemoveListener(events.onDirectoryItemAdded,       listener, &ListenerClass::onDirectoryItemAdded);
        ofRemoveListener(events.onDirectoryItemRemoved,     listener, &ListenerClass::onDirectoryItemRemoved);
        ofRemoveListener(events.onDirectoryItemModified,    listener, &ListenerClass::onDirectoryItemModified);
        ofRemoveListener(events.onDirectoryItemMovedFrom,   listener, &ListenerClass::onDirectoryItemMovedFrom);
        ofRemoveListener(events.onDirectoryItemMovedTo,     listener, &ListenerClass::onDirectoryItemMovedTo);
        ofRemoveListener(events.onDirectoryScanError,       listener, &ListenerClass::onDirectoryScanError);
    }

protected:
    
    void handleFileAction(WatchID watchid,
                          const string& dir,
                          const string& filename,
                          FileWatcher::Action action) {
        
        ofxDirectoryEventType evt = (ofxDirectoryEventType)0;
        ofFile f(filename);

        // not all events are supported yet
        if(action == FileWatcher::Add) {
            evt = DW_ITEM_ADDED;
            ofxDirectoryItemEvent event(f,evt);
            ofNotifyEvent(events.onDirectoryItemAdded,event,this);
        } else if(action == FileWatcher::Delete) {
            evt = DW_ITEM_REMOVED;
            ofxDirectoryItemEvent event(f,evt);
            ofNotifyEvent(events.onDirectoryItemRemoved,event,this);
        } else if(action == FileWatcher::Modified) {
            evt = DW_ITEM_MODIFIED;
            ofxDirectoryItemEvent event(f,evt);
            ofNotifyEvent(events.onDirectoryItemModified,event,this);
        } else {
            ofLogError("SimpleFileWatchListener::handleFileAction") << "Unknown FileWatcher::Action: " << action;
        }
    }

private:
    bool _bIsWatching;
    ofDirectory _directory;
    WatchID _currentWatch;
    
};
