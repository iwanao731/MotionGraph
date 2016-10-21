//
//  MotionGraph.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____MotionGraph__
#define ____MotionGraph__

#include <stdio.h>
#include <string>
#include <vector>
#include "Graph.h"
#include "Motion.h"

using namespace Euclid;

class Threshold;
class NCoincidents;

class MotionGraph
{
public:
    MotionGraph();
    ~MotionGraph();
    
    void addMotion(const Motion& motion);
    
    // Motion Graph Function
    void constructGraph(Threshold threshold, NCoincidents nCoincidents);
    Graph *prune();
    
    // utility function
    void draw(const float& wScale, const float& hScale);
    bool LoadGraph(const std::string& filename);
    void exportGraph(const std::string& filename);
    
    Motion *getMotion(const int& index);
    const int getNumMotion() const;
    bool isExistMotion(const int& index);
    Graph *getGraph() { return mGraph; };
    
protected:
    int mAnimCount;
    Graph *mGraph;
    std::vector<Motion> mMotions;
    
};

class Threshold
{
public:
    Threshold(float value) : mThreshold(value) {}
    ~Threshold() {}
    float getValue() { return mThreshold; }
    
private:
    float mThreshold;
};

class NCoincidents
{
public:
    NCoincidents(int value) : mNCoincidents(value) {}
    ~NCoincidents() {}
    int getValue() { return mNCoincidents; }
    
private:
    int mNCoincidents;
};

#endif /* defined(____MotionGraph__) */
