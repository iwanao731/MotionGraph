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
        
        // getter
        const int getNFrames() const;
        const int getNPoints() const;
        const std::string& getLabel() const;
        const std::string& getFilePath() const;
        const Pose& getPose(const int i);
        
        // setter
        void setNFrames(const int nFrames);
        void setLabel(const std::string& label);
        void setFilePath(const std::string& filepath);
        void setPoses(const std::vector<Pose>& poses, const int nFrames);
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
