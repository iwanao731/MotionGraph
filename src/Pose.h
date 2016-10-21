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
    void addPoint(const float& x, const float& y, const float& z);
    void addPoint(const Point3D& pos);
    
    const int getNPoints() const;
    const Point3D getPoint(const int index) const;
    
private:
    vector<Point3D> mPose;
    
};

#endif /* defined(____PointCloud__) */
