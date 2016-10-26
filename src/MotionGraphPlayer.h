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
using namespace Euclid;

struct MotionInfo {
    int mFrame;
    int mMotionIndex;
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
    const bool isPlaying() const;
    
    const int getNumMotions() const;
    const int getCurrentMotionIndex() const;
    
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
    
    const bool hasBranch() const;
    void moveBranchMotion();
    const float mixMotions(const MotionInfo& current, MotionInfo& next);
    const float calcInterpolateValue(const int p, const int k);
};

#endif /* defined(____MotionGraphPlayer__) */
