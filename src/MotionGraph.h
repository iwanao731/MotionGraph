//
//  MotionGraph.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Euclid__MotionGraph____
#define ____Euclid__MotionGraph____

#include <stdio.h>
#include <string>
#include <vector>
#include "Graph.h"
#include "Motion.h"

namespace Euclid
{
    class Threshold;
    class NCoincidents;

    class MotionGraph
    {
    public:
        MotionGraph();
        ~MotionGraph();
        
        void addMotion(const Motion& motion);
        
        // Motion Graph Function
        void constructGraph(const Threshold& threshold, const NCoincidents& nCoincidents);
        Graph *prune(); // under constructing
        
        // utility function
        
        /// draw MotionGraph structure on 2D
        void draw(const float& wScale, const float& hScale);
        
        bool LoadGraph(const std::string& filename);
        void exportGraph(const std::string& filename);
        
        bool isExistMotion(const int index) const;
        const int getNumMotion() const;
        Motion *getMotion(const int index);
        Graph *getGraph() const { return this->mGraph; }
        
    private:
        int mAnimCount;
        Graph *mGraph;
        std::vector<Motion> mMotions;
        
    };

    class Threshold
    {
    public:
        Threshold(const float value) : mThreshold(value) {}
        ~Threshold() {}
        const float getValue() const { return this->mThreshold; }
        
    private:
        float mThreshold;
    };

    class NCoincidents
    {
    public:
        NCoincidents(const int value) : mNCoincidents(value) {}
        ~NCoincidents() {}
        const int getValue() const { return this->mNCoincidents; }
        
    private:
        int mNCoincidents;
    };
}

#endif /* defined(____Euclid__MotionGraph____) */
