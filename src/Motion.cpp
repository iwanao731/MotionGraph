//
//  Motion.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Motion.h"

using namespace Euclid;

Motion::Motion()
{
    this->mNPoints = 0;
}

Motion::~Motion()
{
    
}

const int Motion::getNFrames() const
{
    return this->mNFrames;
}

const int Motion::getNPoints() const
{
    return this->mNPoints;
}

const std::string& Motion::getLabel() const
{
    return this->mLabel;
}

const std::string& Motion::getFilePath() const
{
    return this->mFilePath;
}

Pose& Motion::getPose(const int i)
{
    assert(i < this->mNFrames);
    return this->mPoses[i];
}

void Motion::setNFrames(const int nFrames)
{
    this->mNFrames = nFrames;
}

void Motion::setLabel(const std::string& label)
{
    this->mLabel = label;
}

void Motion::setFilePath(const std::string& filepath)
{
    this->mFilePath = filepath;
}

void Motion::setPoses(const std::vector<Pose>& poses, const int nFrames)
{
    this->mPoses = std::move(poses);    // poses is now valid but unspecified (C++11)
    this->mNFrames = nFrames;
}

void Motion::addPose(Pose &p)
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

