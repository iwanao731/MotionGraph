//
//  Motion.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Euclid__Motion____
#define ____Euclid__Motion____

#include <stdio.h>
#include <vector>
#include <string>
#include "Pose.h"

namespace Euclid
{
    class Motion
    {
    public:
        Motion();
        ~Motion();
        
        int getNFrames() { return this->mNFrames; }
        int getNPoints() { return this->mNPoints; }
        std::string getLabel() { return this->mLabel; }
        std::string *getLabelPtr() { return &this->mLabel; }
        std::string getFilePath() { return this->mFilePath; }
        Pose getPose(int i);
        
        void setPoses(std::vector<Pose> poses, int nFrames);
        void setNFrames(const int nFrames) { this->mNFrames = nFrames; }
        void setLabel(const std::string label) { this->mLabel = label; }
        void setFilePath(const std::string filepath) { this->mFilePath = filepath; }
        void addPose(Pose p);
        
        // utility
        void printInfo();

    private:
        int mNFrames;
        int mNPoints;
        std::string mLabel;
        std::string mFilePath;
        std::vector<Pose> mPoses;
    };
}

#endif /* defined(____Euclid__Motion____) */
