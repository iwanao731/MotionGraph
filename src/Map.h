//
//  Map.h
//  
//
//  Created by NAOYAIWAMOTO on 10/10/2016.
//
//

#ifndef ____Map__
#define ____Map__

#include <stdio.h>
#include <vector>
#include <fstream>
#include "Motion.h"

using namespace Euclid;

class Map
{
public:
    Map();
    Map(const int nMotions);
    ~Map();
    
    void setNSteps(const int step) { this->mNSteps = step; }
    void setNRelations(const int n) { this->mNRelations = n; }
    void setThreshold(const float threshold) { this->mThreshold = threshold; }
    
    int getNSteps() { return this->mNSteps; }
    int getNRelations() { return this->mNRelations; }
    float getThreshold() { return this->mThreshold; }
    string getRelations(const int i, const int j){ return mRelations[i][j]; }
    
    void constructMap(std::vector<Motion> motions, const int nMotions);
    void compareMotions(Motion &m1, Motion &m2);
    float comparePoses(Pose &pose1, Pose &pose2);

    int getMinimums(const int level, std::vector<int> *m1, std::vector<int> *m2);
    void exportMapFile(float **map, Motion &m1, Motion &m2);
    Motion getMotion(const int index) { return this->mMotions[index]; }
    int getNMotions() { return mMotions.size(); }

private:
    int mNRelations;
    int mMaxRelations;
    int mNSteps;
    float mThreshold;
    float ***mDifferenceMap;
    std::string **mRelations;
    std::vector<Motion> mMotions;
    
    ofstream ofs;
    void calcLocalMinimum(bool **transPoint, const int motionIndex, const int i, const int j, const int range, const int sizeW, const int sizeH);
    //void saveImage(float **map, Motion &m1, Motion &m2);
    void saveImage(bool **BMap, float **map, Motion &m1, Motion &m2);
};

#endif /* defined(____Map__) */
