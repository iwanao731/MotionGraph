//
//  MotionGraphPlayer.h
//  
//
//  Created by NAOYAIWAMOTO on 19/10/2016.
//
//

#ifndef ____MotionGraphPlayer__
#define ____MotionGraphPlayer__

#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include "MotionGraph.h"
#include "ofxDigitalDanceBvh.h"

using namespace mlib;
using namespace Euclid;

struct MotionInfo {
    int mFrame;
    int mMotionIndex;
    ofQuaternion quat;
    ofVec3f trans;
};

class MotionGraphPlayer
{
public:
    MotionGraphPlayer();
    ~MotionGraphPlayer();

    void set(const MotionGraph& motionGraph);
    void load(const std::string& filename);
    void update();
    void play();
    void stop();
    void draw();
    void drawGraph(const float& wScale, const float& hScale);
    void resetPosition();
    const bool isPlaying() const;
    
    // setter
    const void setLoop(bool flag) const;
    
    // geter
    const int getNumMotions() const;
    const int getCurrentMotionIndex() const;
    
    void selectMotion(const int index);

private:
    bool mPlaying;
    bool mMoving;
    int mMovingTime;
    int mNumMotions;
    int mOffsetFrame;
    float mMixValue;
    ofMatrix4x4 mTrackPoseMatrix;
    MotionInfo mPrevMotion;
    MotionInfo mCurrentMotion;
    MotionInfo mNextMotion;
    MotionGraph *mMGraph;
    ofxDigitalDanceBvh *mBvh;
    ofxDigitalDanceBvh *mViewer;
    
    const bool hasBranch() const;
    const bool moveBranchMotion();
    const float setFrameMotionBlend(const MotionInfo& current, MotionInfo& next);
};

#endif /* defined(____MotionGraphPlayer__) */
