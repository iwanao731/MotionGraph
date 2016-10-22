#include "ofApp.h"
#include "Motion.h"
#include "BVHConverter.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60.f);
    
    mMotionIndex = 0;
    
    // Load Motion Dataset
    ofDirectory dir;
    dir.listDir("CMU");
    for(int i=0; i<dir.size(); i++){
        Motion motion;
        loadMotion(dir.getPath(i), motion);
        mMotionGraph.addMotion(motion);
    }
    
    mMotionGraph.constructGraph(Threshold(2000.f), NCoincidents(5));
    mMotionGraph.exportGraph("graph.txt");
    
    mMotionGraph.LoadGraph("graph.txt");
    // motion_graph.saveImage("file.png");
    //mgPlayer.load("graph.txt");
    
    mMGPlayer.set(mMotionGraph);
    mMGPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    mMGPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mMotionGraph.draw(ofGetMouseX()/100.f, ofGetMouseY());
    
    ofEnableDepthTest();
    ofEnableLighting();
    mLight.enable();
    mLight.setPosition(mCam.getPosition());
    
    ofSetColor(255);
    mCam.begin();
    
    mMGPlayer.draw();
    
    mCam.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetColor(0);
    ofDrawBitmapString("motion number : " + ofToString(mMGPlayer.getCurrentMotionIndex()), ofGetWidth()-200, ofGetHeight()-40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ':
        {
            if(mMGPlayer.isPlaying())
                mMGPlayer.stop();
            else
                mMGPlayer.play();
            break;
        }
        case OF_KEY_LEFT:
        {
            mMotionIndex--;
            if(mMotionIndex < 0)
                mMotionIndex = 0;

            mMGPlayer.selectMotion(mMotionIndex);
            mMGPlayer.play();
            break;
        }
        case OF_KEY_RIGHT:
        {
            mMotionIndex++;
            if (mMotionIndex == mMGPlayer.getNumMotions())
                mMotionIndex = 0;
            
            mMGPlayer.selectMotion(mMotionIndex);
            mMGPlayer.play();
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::loadMotion(const string& filepath, Motion &motion)
{
    // Load BVH
    mlib::ofxDigitalDanceBvh bvh;
    bvh.load(filepath);
    
    // Convert Motion
    Euclid::BvhToMotion(bvh, motion);
    
    // Set Label and path
    ofFilePath path;
    std::string name = path.removeExt(path.getFileName(filepath));
    motion.setLabel(name);
    motion.setFilePath(filepath);
    motion.printInfo();
}