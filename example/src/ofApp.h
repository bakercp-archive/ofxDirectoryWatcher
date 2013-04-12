#pragma once

#include "ofMain.h"

#include "ofxDirectoryWatcher.h"

class ofApp : public ofBaseApp {

public:
    void exit();
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void onItemAdded(const ofxDirectoryEvent& evt) {
        ofLogNotice("ofApp::onItemAdded") << "Added: " << evt.item.getAbsolutePath();
    }
    
    void onItemRemoved(const ofxDirectoryEvent& evt) {
        ofLogNotice("ofApp::onItemRemoved") << "Removed: " << evt.item.getAbsolutePath();
    }
    
    void onItemModified(const ofxDirectoryEvent& evt) {
        ofLogNotice("ofApp::onItemModified") << "Modified: " << evt.item.getAbsolutePath();
    }
    
    void onItemMovedFrom(const ofxDirectoryEvent& evt) {
        ofLogNotice("ofApp::onItemMovedFrom") << "Moved From: " << evt.item.getAbsolutePath();
    }
    
    void onItemMovedTo(const ofxDirectoryEvent& evt) {
        ofLogNotice("ofApp::onItemMovedTo") << "Moved To: " << evt.item.getAbsolutePath();
    }
    
    void onScanError(const Exception& exc) {
        ofLogError("ofApp::onScanError") << "Error: " << exc.displayText();
    }
    
    ofxDirectoryWatcher watcher;
};
