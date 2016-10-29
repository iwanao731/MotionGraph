#include "ofApp.h"
#include "Motion.h"
#include "BVHConverter.h"

#define BUILD_GRAPH
#define MGPLAY
#define SMG_VIEWER
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(150);
    ofSetFrameRate(60.f);
    mMotionIndex = 0;
    bGraphDraw = true;
    
#ifdef BUILD_GRAPH
    // Load Motion Dataset
    ofDirectory dir;
    dir.listDir("CMU");
//    dir.listDir("Male1");
    
    for(int i=0; i<dir.size(); i++){
        Motion motion;
        loadMotion(dir.getPath(i), motion);
        mMotionGraph.addMotion(motion);
    }

    mMotionGraph.constructGraph(Threshold(500.f), NCoincidents(5));    // 500, 5 is easy for DEBUG
    mMotionGraph.exportGraph("sample");
    mMotionGraph.clear();
#endif

#ifdef MGPLAY
    // load graph and motion
    mMGPlayer.load("sample");
    mMGPlayer.setLoop(false);
    mMGPlayer.play();
#endif
  
#ifdef SMG_VIEWER
    // secondary motion graph
    SMG.loadGraph("sample_graph.txt");
    SMG.constructeGraph(0, 0);
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
#ifdef MGPLAY
    mMGPlayer.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){

#ifdef MGPLAY
    if(bGraphDraw) {
        ofSetColor(255);
        mMGPlayer.drawGraph(ofGetMouseX()/100.f, ofGetMouseY());
    }
    
    ofEnableDepthTest();
    ofEnableLighting();
    mLight.enable();
    mLight.setPosition(mCam.getPosition());
    
    ofSetColor(255);
    mCam.begin();
    
    // floor
    ofDrawGrid(100, 20, false, false, true, false);

    mMGPlayer.draw();
    
    mCam.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetColor(0);
    ofDrawBitmapString("motion number : " + ofToString(mMGPlayer.getCurrentMotionIndex()), ofGetWidth()-300, 40);
    ofDrawBitmapString("graph previwer (g) : " + ofToString(bGraphDraw == true ? "true" : "false"), ofGetWidth()-300, 60);
    ofDrawBitmapString("full screen (f)", ofGetWidth()-300, 80);
    ofDrawBitmapString("reset position (r)", ofGetWidth()-300, 100);
    ofDrawBitmapString("change motion (key <- or ->) ", ofGetWidth()-300, 120);
    ofDrawBitmapString("start / stop (space) : " + ofToString(mMGPlayer.isPlaying() == true ? "playing" : "stop"), ofGetWidth()-300, 140);
#endif
    
#ifdef SMG_VIEWER
    SMG.drawTree(ofGetMouseX()/100.f, ofGetMouseY()/100.f);
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
#ifdef MGPLAY
        case 'r':
            mMGPlayer.resetPosition();
            break;
        case ' ':
        {
            if(mMGPlayer.isPlaying())
                mMGPlayer.stop();
            else
                mMGPlayer.play();
            break;
        }
        case 'g':
            bGraphDraw = !bGraphDraw;
            break;
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
#endif
        case 'f':
            ofToggleFullscreen();
            break;
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