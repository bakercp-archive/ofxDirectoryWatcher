#include "ofApp.h"

void ofApp::exit() {
    watcher.UnregisterBrowseServiceEvents(this);
}

//------------------------------------------------------------------------------
void ofApp::setup(){

    watcher.RegisterBrowseServiceEvents(this);

    string folderToWatch = ofToDataPath("",true);
    bool   bListAllFilesImmediately = true;

    watcher.setup(folderToWatch,bListAllFilesImmediately);
}

//------------------------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofFill();

    int y = TXT_HEIGHT;
    for(size_t i = 0; i < messages.size(); i++) {
        ofSetColor(ofMap(i, 0, messages.size(), 255, 90));
        ofDrawBitmapString(messages[i], 10, y);
        y += TXT_HEIGHT;
    }
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

    int height = ofGetHeight();
    int numLines = (int)(height / TXT_HEIGHT);

    messages.push_front(msg.message);

    while(messages.size() > numLines) {
        messages.pop_back();
    }

}
