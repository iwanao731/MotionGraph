#include "ofApp.h"
#include "Motion.h"
#include "BVHConverter.h"

std::vector<std::string> split(const std::string &str, char sep);
void loadMotion(const string filename, Motion &motion);

ofVec2f mousePos;
int motionIndex = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60.f);
    
    // Load Motion Dataset
    ofDirectory dir;
    dir.listDir("CMU");
    for(int i=0; i<dir.size(); i++){
        Motion motion;
        loadMotion(dir.getPath(i), motion);
        motion_graph.addMotion(motion);
    }
    
    motion_graph.constructGraph(Threshold(2000.f), NCoincidents(5));
    motion_graph.exportGraph("graph.txt");
    
    // motion_graph.LoadGraph("graph.txt");
    // motion_graph.saveImage("file.png");
    //mgPlayer.load("graph.txt");
    
    mgPlayer.set(motion_graph);
    mgPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    mgPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    motion_graph.draw(mousePos.x, mousePos.y);
    
    ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
    light.setPosition(cam.getPosition());
    
    ofSetColor(255);
    cam.begin();
    
    mgPlayer.draw();
    
    cam.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetColor(0);
    ofDrawBitmapString("motion number : " + ofToString(mgPlayer.getCurrentMotionIndex()), ofGetWidth()-200, ofGetHeight()-40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ':
        {
            if(mgPlayer.isPlaying())
                mgPlayer.stop();
            else
                mgPlayer.play();
            break;
        }
        case OF_KEY_LEFT:
        {
            motionIndex--;
            if(motionIndex < 0)
                motionIndex = 0;

            mgPlayer.selectMotion(motionIndex);
            mgPlayer.play();
            break;
        }
        case OF_KEY_RIGHT:
        {
            motionIndex++;
            if (motionIndex == mgPlayer.getNumMotions())
                motionIndex = 0;
            
            mgPlayer.selectMotion(motionIndex);
            mgPlayer.play();
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
    mousePos.set((float)x/100.f,y);
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
void loadMotion(const string filename, Motion &motion)
{
    // Load BVH
    mlib::ofxDigitalDanceBvh bvh;
    bvh.load(filename);
    
    // Convert Motion
    motion = BVHConverter::ToMotion(bvh);
    
    // Set Label
    std::vector<std::string> hierarchy = split(filename, '/');
    std::vector<std::string> name = split(hierarchy.back(), '.');
    motion.setLabel(name[0]);
    motion.setFilePath(filename);
    
    motion.printInfo();
}

//--------------------------------------------------------------
std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> v;
    std::stringstream ss(str);
    std::string buffer;
    while( std::getline(ss, buffer, sep) ) {
        v.push_back(buffer);
    }
    return v;
}
