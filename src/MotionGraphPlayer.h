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
#include "MotionGraph.h"
#include "ofxDigitalDanceBvh.h"

using namespace mlib;

struct MotionInfo {
    int mFrame;
    int mMotionIndex;
};

class MotionGraphPlayer
{
public:
    MotionGraphPlayer();
    ~MotionGraphPlayer();

    void set(MotionGraph motion_graph);
    void load(const std::string filename);
    void update();
    void play();
    void stop();
    virtual void draw();
    
    bool isPlaying();
    int getNumMotions() { return mNumMotions; }
    int getCurrentMotionIndex() { return mCurrentMotion.mMotionIndex; }
    void selectMotion(const int index);

private:
    bool mPlaying;
    bool mMoving;
    int mMovingTime;
    int mNumMotions;
    int mOffsetFrame;
    float mixValue;
    MotionInfo mCurrentMotion;
    MotionInfo mNextMotion;
    MotionGraph mMGraph;
    ofxDigitalDanceBvh *mBvh;
    ofxDigitalDanceBvh *mViewer;
    
    bool hasBranch();
    void moveBranchMotion();
    float mixMotions(MotionInfo current, MotionInfo next);
    float calcInterpolateValue(const int p, const int k);
};

#endif /* defined(____MotionGraphPlayer__) */
