//
//  Motion.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Motion.h"

Motion::Motion()
{
    this->mNPoints = 0;
}

Motion::~Motion()
{
    
}

Pose Motion::getPose(int i)
{
    assert(i < this->mNFrames);
    return this->mPoses[i];
}

void Motion::setPoses(std::vector<Pose> poses, const int nFrames)
{
    this->mPoses = poses;
    this->mNFrames = nFrames;
}

void Motion::addPose(Pose p)
{
    this->mPoses.push_back(p);
    
    if(this->mNPoints == 0){
        this->mNPoints = p.getNPoints();
    }else{
        // Please use same number of point clouds to evaluate distance of each motion.
        assert(this->mNPoints == p.getNPoints());
    }
}

void Motion::printInfo()
{
    std::cout << "label: " << this->mLabel << "    frames: " << this->mNFrames << std::endl;
}

