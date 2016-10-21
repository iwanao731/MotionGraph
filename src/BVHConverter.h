//
//  BVH2MotionAdapter.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____BVHConverter__
#define ____BVHConverter__

#include <stdio.h>
#include "ofxDigitalDance.h"
#include "Motion.h"
#include "Pose.h"

namespace Euclid
{
    void BvhToMotion(mlib::ofxDigitalDanceBvh& bvh, Euclid::Motion& motion);
};

#endif /* defined(BVHConverter) */
