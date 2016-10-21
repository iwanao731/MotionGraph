//
//  Motion.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Motion.h"

Euclid::Motion::Motion()
{
    this->mNPoints = 0;
}

Euclid::Motion::~Motion()
{
    
}

Pose& Euclid::Motion::getPose(const int& i)
{
    assert(i < this->mNFrames);
    return this->mPoses[i];
}

void Euclid::Motion::setPoses(const std::vector<Pose>& poses, const int& nFrames)
{
    this->mPoses = std::move(poses);    // poses is now valid but unspecified (C++11)
    this->mNFrames = nFrames;
}

void Euclid::Motion::addPose(Pose &p)
{
    this->mPoses.push_back(p);
    
    if(this->mNPoints == 0){
        this->mNPoints = p.getNPoints();
    }else{
        // Please use same number of point clouds to evaluate distance of each motion.
        assert(this->mNPoints == p.getNPoints());
    }
}

void Euclid::Motion::printInfo()
{
    std::cout << "label: " << this->mLabel << "    frames: " << this->mNFrames << std::endl;
}

