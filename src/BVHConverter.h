//
//  BVH2MotionAdapter.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____BVH2MotionAdapter__
#define ____BVH2MotionAdapter__

#include <stdio.h>
#include "ofxDigitalDance.h"
#include "Motion.h"
#include "Pose.h"

namespace BVHConverter
{
    void ToMotion(mlib::ofxDigitalDanceBvh& bvh, Euclid::Motion& motion);
};

#endif /* defined(____BVH2MotionAdapter__) */
