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
        
        const int& getNFrames() const{ return this->mNFrames; }
        const int& getNPoints() const { return this->mNPoints; }
        const std::string& getLabel() const { return this->mLabel; }
        const std::string& getFilePath() const { return this->mFilePath; }
        Pose& getPose(const int& i);
        
        void setPoses(const std::vector<Pose>& poses, const int& nFrames);
        void setNFrames(const int& nFrames) { this->mNFrames = nFrames; }
        void setLabel(const std::string& label) { this->mLabel = label; }
        void setFilePath(const std::string& filepath) { this->mFilePath = filepath; }
        void addPose(Pose& p);
        
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
