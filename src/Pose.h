//
//  PointCloud.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____PointCloud__
#define ____PointCloud__

#include <stdio.h>
#include <ofMain.h>
#include "Point3D.h"

class Pose
{
public:
    Pose();
    ~Pose();
    void addPoint(float x, float y, float z);
    void addPoint(Point3D pos);
    
    int getNPoints() { return mPose.size(); }
    Point3D getPoint(const int index) { return mPose[index]; }
    
private:
    vector<Point3D> mPose;
    
};

#endif /* defined(____PointCloud__) */
