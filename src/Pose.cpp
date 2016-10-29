//
//  PointCloud.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Pose.h"

using namespace Euclid;

Pose::Pose()
{
    
}

Pose::~Pose()
{
    
}

void Pose::addPoint(const float& x, const float& y, const float& z)
{
    this->mPose.push_back(Point3D(x,y,z));
}

void Pose::addPoint(const Point3D& pos)
{
    this->mPose.push_back(pos);
}

const int Pose::getNPoints() const
{
    return this->mPose.size();
}

const Point3D& Pose::getPoint(const int index) const
{
    return this->mPose[index];
}
