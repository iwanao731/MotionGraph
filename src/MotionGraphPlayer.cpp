//
//  MotionGraphPlayer.cpp
//  
//
//  Created by NAOYAIWAMOTO on 19/10/2016.
//
//

#include "MotionGraphPlayer.h"

MotionGraphPlayer::MotionGraphPlayer() : mOffsetFrame(10), mMixValue(1.0f), mMovingTime(0), mMoving(false)
{
    mCurrentMotion.mMotionIndex = 0;
    this->mMGraph = new MotionGraph;
    mTrackPoseMatrix.makeIdentityMatrix();
}

MotionGraphPlayer::~MotionGraphPlayer()
{
    
}

void MotionGraphPlayer::set(const MotionGraph& motionGraph)
{
//    mMGraph = motionGraph;
//    mNumMotions = this->mMGraph.getNumMotion();
//    mBvh = new ofxDigitalDanceBvh [mNumMotions];
//    
//    for (int i=0; i<this->getNumMotions(); i++) {
//        mBvh[i].load(this->mMGraph.getMotion(i)->getFilePath());
//        mBvh[i].setLoop(true);
//        //mBvh[i].play();
//    }
//    
//    mViewer = &mBvh[mCurrentMotion.mMotionIndex];
}

void MotionGraphPlayer::load(const std::string& filename)
{
    this->mMGraph->loadGraph(filename + "_graph.txt");
    this->mMGraph->loadMotionList(filename + "_motionlist.txt");

    // load motion
    mNumMotions = this->mMGraph->getNumMotion();
    mBvh = new ofxDigitalDanceBvh [mNumMotions];
    for (int i=0; i<this->getNumMotions(); i++) {
        mBvh[i].load(this->mMGraph->getMotion(i)->getFilePath());
        //mBvh[i].setLoop(true);
        //mBvh[i].play();
    }

    mViewer = &mBvh[mCurrentMotion.mMotionIndex];
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

void MotionGraphPlayer::update()
{
    if(this->isPlaying()) {
        mBvh[mCurrentMotion.mMotionIndex].update();
        mCurrentMotion.mFrame = mBvh[mCurrentMotion.mMotionIndex].getFrame();
        
        // for bug
        if(mCurrentMotion.mFrame == 0)
            mBvh[mCurrentMotion.mMotionIndex].setFrame(mCurrentMotion.mFrame);
        
        // confirm whether current frame has transition edge
        if(this->hasBranch() && mMoving == false && this->mMoving == 0){
            this->mMoving = this->moveBranchMotion();
        }
    }
    
    if (mMoving) {
        this->mMixValue = this->setFrameMotionBlend(mCurrentMotion, mNextMotion);
        mMovingTime++;
        
        if(mOffsetFrame <= mMovingTime) {
            mPrevMotion = mCurrentMotion;
            mCurrentMotion = mNextMotion;
            mMovingTime = 0;
            mMoving = false;
            mMixValue = 1.0f;
        }
    }
}

void MotionGraphPlayer::draw()
{
    mViewer = &mBvh[mCurrentMotion.mMotionIndex];

    ofMatrix4x4 mat;
    ofPushMatrix();
    glMultMatrixf(mat.getPtr());
    mViewer->drawMixMotion(&mBvh[mNextMotion.mMotionIndex], this->mMixValue,
                           mCurrentMotion.quat, mCurrentMotion.trans,
                           mNextMotion.quat, mNextMotion.trans  );
        
    ofPopMatrix();
}

void MotionGraphPlayer::drawGraph(const float& wScale, const float& hScale)
{
    this->mMGraph->draw(wScale, hScale);
}

void MotionGraphPlayer::resetPosition()
{
    this->mTrackPoseMatrix.makeIdentityMatrix();
    
    mCurrentMotion.quat = mTrackPoseMatrix.getRotate();
    mCurrentMotion.trans = mTrackPoseMatrix.getTranslation();
    mNextMotion.quat = mTrackPoseMatrix.getRotate();
    mNextMotion.trans = mTrackPoseMatrix.getTranslation();
}

const bool MotionGraphPlayer::isPlaying() const
{
    return this->mPlaying;
}

const void MotionGraphPlayer::setLoop(bool flag) const
{
    for (int i=0; i<this->getNumMotions(); i++) {
        mBvh[i].setLoop(flag);
    }
}

const int MotionGraphPlayer::getNumMotions() const
{
    return this->mNumMotions;
}

const int MotionGraphPlayer::getCurrentMotionIndex() const
{
    return this->mCurrentMotion.mMotionIndex;
}

void MotionGraphPlayer::selectMotion(const int index)
{
    if(index < this->mMGraph->getNumMotion()){
        
        mNextMotion.mMotionIndex = index;
        mNextMotion.mFrame = 0;
        
        mBvh[mNextMotion.mMotionIndex].setFrame(mNextMotion.mFrame);
        
        
        
        
        this->mMoving = true;
        
//        mCurrentMotion.mMotionIndex = index;
//        mCurrentMotion.mFrame = 0;
//        
//        mBvh[mCurrentMotion.mMotionIndex].setFrame(mCurrentMotion.mFrame);
        
        cout << "motion index : " << index << endl;
    }else{
        cout << "max num of motion is " << this->mMGraph->getNumMotion() << endl;
    }
}

const bool MotionGraphPlayer::hasBranch() const
{
    if(this->mMGraph->getGraph()->hasBranch(mCurrentMotion.mMotionIndex, mCurrentMotion.mFrame)){
        return true;
    }else{
        return false;
    }
}

const bool MotionGraphPlayer::moveBranchMotion()
{
    int nodeIndex = this->mMGraph->getGraph()->getNodeindex(mCurrentMotion.mMotionIndex, mCurrentMotion.mFrame);
    int numEdge = this->mMGraph->getGraph()->getNode(nodeIndex)->getNumEdges();
    
    if(numEdge > 0) {
        
        // for set random value
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dice(0, numEdge-1);
        int index = dice(mt);
        
        int nextMotionID = this->mMGraph->getGraph()->getNode(nodeIndex)->getEdge(index)->getDestNode()->getMotionID();
        int nextMotionFrame = this->mMGraph->getGraph()->getNode(nodeIndex)->getEdge(index)->getDestNode()->getFrameID();
        
        if(mCurrentMotion.mMotionIndex != nextMotionID && mPrevMotion.mFrame != nextMotionFrame){
            
            mNextMotion.mMotionIndex = this->mMGraph->getGraph()->getNode(nodeIndex)->getEdge(index)->getDestNode()->getMotionID();
            mNextMotion.mFrame  = this->mMGraph->getGraph()->getNode(nodeIndex)->getEdge(index)->getDestNode()->getFrameID();
        
            // set frame
            this->mBvh[mNextMotion.mMotionIndex].setFrame(mNextMotion.mFrame);
            
            // set tracking current pose matrix
            mCurrentMotion.quat = mTrackPoseMatrix.getRotate();
            mCurrentMotion.trans = mTrackPoseMatrix.getTranslation();
            
            // calculate tracking matrix from previous motion's last pose
            mTrackPoseMatrix = ofxDigitalDanceBvh::calcTrackPoseMatrix(mBvh[mCurrentMotion.mMotionIndex],
                                                                       mBvh[mNextMotion.mMotionIndex],
                                                                       mTrackPoseMatrix);
            // set tracking next pose matrix
            mNextMotion.quat = mTrackPoseMatrix.getRotate();
            mNextMotion.trans = mTrackPoseMatrix.getTranslation();

            return true;
        }
        else{
            return false;    // if same motion, still continue next frame
        }
    }
}

const float MotionGraphPlayer::setFrameMotionBlend(const MotionInfo& current, MotionInfo& next)
{
    // current update
    this->mBvh[current.mMotionIndex].setFrame(current.mFrame);
    
    // next update
    next.mFrame++;
    
    // set frame for next motion
    if(next.mFrame - mOffsetFrame > 0)
        this->mBvh[next.mMotionIndex].setFrame(next.mFrame - mOffsetFrame);
    else
        this->mBvh[next.mMotionIndex].setFrame(0);
        //mNextMotion.mFrame = 0;
    
    // next animation start playing
    this->mBvh[next.mMotionIndex].play();
    
    // return interpolate value (-1 <= mMovingTIme < mOffsetFrame)
    return ofxDigitalDanceBvh::calcInterpolateValue(mMovingTime, mOffsetFrame);
}
