//
//  BVH2MotionAdapter.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "BVHConverter.h"

Euclid::Motion BVHConverter::ToMotion(mlib::ofxDigitalDanceBvh &bvh)
{
    Euclid::Motion motion;
    
    int numFrames = bvh.getNumFrames();
    //cout << "numFrames : " << numFrames << endl;
    motion.setNFrames(numFrames);
    
    for(int i=0; i<numFrames; i++)
    {
        Pose pose;
        
        // update pose
        bvh.setFrame(i);
        bvh.update();
        
        // add pose
        for (int j=0; j<bvh.getNumJoints(); j++) {
            ofPoint p = bvh.getJoint(j)->getPosition();
            pose.addPoint(Point3D(p.x, p.y, p.z));
        }
        motion.addPose(pose);
    }
    return motion;
}
