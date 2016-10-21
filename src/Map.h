//
//  Map.h
//  
//
//  Created by NAOYAIWAMOTO on 10/10/2016.
//
//

#ifndef ____Euclid__Map____
#define ____Euclid__Map____

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
    
    void setNSteps(const int step);
    void setNRelations(const int n);
    void setThreshold(const float& threshold);
    
    const int getNSteps() const;
    const int getNRelations() const;
    const int getNMotions() const;
    const float& getThreshold() const;
    const std::string& getRelations(const int i, const int j) const;
    const Motion& getMotion(const int index) const;
    
    void constructMap(const std::vector<Motion>& motions, const int nMotions);
    void compareMotions(Motion& m1, Motion& m2);
    const float& comparePoses(const Pose& pose1, const Pose& pose2);

    const int calcMinimums(const int level, std::vector<int>& m1, std::vector<int>& m2);
    void exportMapFile(float **map, const Motion& m1, const Motion& m2);

private:
    int mNRelations;
    int mMaxRelations;
    int mNSteps;
    float mThreshold;
    float ***mDifferenceMap;
    std::string **mRelations;
    std::vector<Motion> mMotions;
    
    void calcLocalMinimum(bool **transPoint, const int motionIndex, const int i, const int j, const int range, const int sizeW, const int sizeH);
    void saveImage(bool **BMap, float **map, const Motion& m1, const Motion& m2);
};

#endif /* defined(____Euclid__Map____) */
