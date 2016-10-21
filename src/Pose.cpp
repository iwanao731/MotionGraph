//
//  PointCloud.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Pose.h"

Pose::Pose()
{
    
}

Pose::~Pose()
{
    
}

void Pose::addPoint(float x, float y, float z)
{
    this->mPose.push_back(Point3D(x,y,z));
}

void Pose::addPoint(Point3D pos)
{
    this->mPose.push_back(pos);
}
