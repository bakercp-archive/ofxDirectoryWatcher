#include "ofApp.h"

void ofApp::exit() {
    ofRemoveListener(watcher.events.onItemAdded,    this, &ofApp::onItemAdded);
    ofRemoveListener(watcher.events.onItemModified, this, &ofApp::onItemModified);
    ofRemoveListener(watcher.events.onItemRemoved,  this, &ofApp::onItemRemoved);
    ofRemoveListener(watcher.events.onItemMovedTo,  this, &ofApp::onItemMovedTo);
    ofRemoveListener(watcher.events.onItemRemoved,  this, &ofApp::onItemRemoved);
}

//------------------------------------------------------------------------------
void ofApp::setup(){
    
    watcher.watch(ofToDataPath(""));
    
    ofAddListener(watcher.events.onItemAdded,    this, &ofApp::onItemAdded);
    ofAddListener(watcher.events.onItemModified, this, &ofApp::onItemModified);
    ofAddListener(watcher.events.onItemRemoved,  this, &ofApp::onItemRemoved);
    ofAddListener(watcher.events.onItemMovedTo,  this, &ofApp::onItemMovedTo);
    ofAddListener(watcher.events.onItemRemoved,  this, &ofApp::onItemRemoved);
    
}

//------------------------------------------------------------------------------
void ofApp::update(){

}

//------------------------------------------------------------------------------
void ofApp::draw(){

}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
