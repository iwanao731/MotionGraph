//
//  MotionGraphPlayer.cpp
//  
//
//  Created by NAOYAIWAMOTO on 19/10/2016.
//
//

#include "MotionGraphPlayer.h"

MotionGraphPlayer::MotionGraphPlayer() : mOffsetFrame(3), mixValue(1.0f), mMovingTime(0), mMoving(false)
{
    
}

MotionGraphPlayer::~MotionGraphPlayer()
{
    
}

void MotionGraphPlayer::set(MotionGraph motion_graph)
{
    mMGraph = motion_graph;
    mNumMotions = this->mMGraph.getNumMotion();
    mBvh = new ofxDigitalDanceBvh [mNumMotions];
    
    for (int i=0; i<mNumMotions; i++) {
        mBvh[i].load(this->mMGraph.getMotion(i)->getFilePath());
        mBvh[i].setLoop(true);
        mBvh[i].play();
        std::cout << "Num Joints : " << mBvh[i].getNumJoints() << std::endl;
    }
    
    mViewer = &mBvh[mCurrentMotion.mMotionIndex];
}

void MotionGraphPlayer::load(const std::string filename)
{
    this->mMGraph.LoadGraph(filename);
}

void MotionGraphPlayer::update()
{
    if(this->isPlaying()) {
        mBvh[mCurrentMotion.mMotionIndex].update();
        mCurrentMotion.mFrame = mBvh[mCurrentMotion.mMotionIndex].getFrame();
        if(this->hasBranch() && mMoving == false){
            this->moveBranchMotion();
        }
    }
    
    if (mMoving) {
        this->mixValue = this->mixMotions(mCurrentMotion, mNextMotion);
        mMovingTime++;
        
        if(mOffsetFrame <= mMovingTime) {
            mCurrentMotion.mMotionIndex = mNextMotion.mMotionIndex;
            mCurrentMotion.mFrame = mNextMotion.mFrame;
            mMovingTime = 0;
            mMoving = false;
            this->mixValue = 1.0f;
        }
    }
}

void MotionGraphPlayer::play()
{
    mPlaying = true;
    mBvh[mCurrentMotion.mMotionIndex].play();
}

void MotionGraphPlayer::stop()
{
    mPlaying = false;
}

void MotionGraphPlayer::draw()
{
    mViewer = &mBvh[mCurrentMotion.mMotionIndex];

    ofMatrix4x4 mat;
    ofPushMatrix();
    glMultMatrixf(mat.getPtr());
    mViewer->drawMixMotion(&mBvh[mNextMotion.mMotionIndex], this->mixValue);
    ofPopMatrix();
}

bool MotionGraphPlayer::hasBranch()
{
    if(this->mMGraph.getGraph()->hasBranch(mCurrentMotion.mMotionIndex, mCurrentMotion.mFrame)){
        return true;
    }else{
        return false;
    }
}

void MotionGraphPlayer::moveBranchMotion()
{
    int nodeIndex = this->mMGraph.getGraph()->getNodeindex(mCurrentMotion.mMotionIndex, mCurrentMotion.mFrame);
    int numEdge = this->mMGraph.getGraph()->getNode(nodeIndex)->getNumEdges();
    
    if(numEdge > 0) {
        int index = ofRandom(numEdge);

        mNextMotion.mMotionIndex = this->mMGraph.getGraph()->getNode(nodeIndex)->getEdge(index)->getDestination()->getMotionID();
        mNextMotion.mFrame  = this->mMGraph.getGraph()->getNode(nodeIndex)->getEdge(index)->getDestination()->getFrameID();
        
        mMoving = true;        
    }
}

float MotionGraphPlayer::mixMotions(MotionInfo current, MotionInfo next)
{
    // current update
    this->mBvh[current.mMotionIndex].setFrame(current.mFrame);
    this->mBvh[current.mMotionIndex].update();
    
    // next update
    next.mFrame++;
    if(next.mFrame - mOffsetFrame > 0)
        this->mBvh[next.mMotionIndex].setFrame(next.mFrame - mOffsetFrame);
    else
        mNextMotion.mFrame = 0;

    this->mBvh[next.mMotionIndex].update();
    
    // interpolate
    return calcInterpolateValue(mMovingTime, mOffsetFrame);
}

bool MotionGraphPlayer::isPlaying()
{
    return this->mPlaying;
}

void MotionGraphPlayer::selectMotion(const int index)
{
    if(index < this->mMGraph.getNumMotion()){
        mCurrentMotion.mMotionIndex = index;
        cout << "motion index : " << index << endl;
    }else{
        cout << "max num of motion is " << this->mMGraph.getNumMotion() << endl;
    }
}

float MotionGraphPlayer::calcInterpolateValue(const int p, const int k)
{
    assert(-1 < p && p < k);

    return 2 * pow(((float)p+1)/(float)k, 3) - 3 * pow(((float)p+1)/(float)k, 2) + 1;
}

