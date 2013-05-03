#pragma once

#include <deque>
#include "ofMain.h"
#include "ofxDirectoryWatcher.h"


class ofApp : public ofBaseApp {
public:
    enum {
        TXT_HEIGHT = 14
    };

    void exit();
    void setup();
    void draw();

    void gotMessage(ofMessage msg);

    void onDirectoryItemAdded(const ofxDirectoryItemEvent& evt) {
        ofSendMessage("Added: " + evt.item.getAbsolutePath());
    }
    
    void onDirectoryItemRemoved(const ofxDirectoryItemEvent& evt) {
        ofSendMessage("Removed: " + evt.item.getAbsolutePath());
    }
    
    void onDirectoryItemModified(const ofxDirectoryItemEvent& evt) {
        ofSendMessage("Modified: " + evt.item.getAbsolutePath());
    }
    
    void onDirectoryItemMovedFrom(const ofxDirectoryItemMoveEvent& evt) {
        ofLogNotice("ofApp::onItemMovedFrom") << "Moved From: " << evt.item.getAbsolutePath();
    }
    
    void onDirectoryItemMovedTo(const ofxDirectoryItemMoveEvent& evt) {
        ofLogNotice("ofApp::onItemMovedTo") << "Moved To: " << evt.item.getAbsolutePath();
    }
    
    void onDirectoryScanError(const Exception& exc) {
        ofLogError("ofApp::onScanError") << "Error: " << exc.displayText();
    }
    
    ofxDirectoryWatcher watcher;

    std::deque<string> messages;

};
