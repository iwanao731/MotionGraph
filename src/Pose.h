//
//  PointCloud.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Euclid__Pose____
#define ____Euclid__Pose____

#include <stdio.h>
#include "Point3D.h"

namespace Euclid
{
    class Pose
    {
    public:
        Pose();
        ~Pose();
        void addPoint(const float& x, const float& y, const float& z);
        void addPoint(const Point3D& pos);
        
        const int getNPoints() const;
        const Point3D& getPoint(const int index) const;
        
    private:
        vector<Point3D> mPose;
        
    };
}

#endif /* defined(____Euclid__Pose____) */
