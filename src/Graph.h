//
//  Graph.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Euclid__Graph____
#define ____Euclid__Graph____

#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
#include "Node.h"
#include "Motion.h"
#include "Edge.h"
#include "Map.h"
#include <ofMain.h>

namespace Euclid
{
    class Graph
    {
    public:
        Graph();
        ~Graph();

        const int getNumNodes() const;
        Node* getNode(const int node);
        
        const bool hasBranch(const int motionIndex, const int frameId);
        const int getNodeindex(const int motionIndex, const int frameId);

        void constructGraph(const std::vector<Motion>& motions, const int nMotions, const float& threshold, const int nCoincidents);
        void loadGraph(const std::string& filename);
        void exportGraphFile(const std::string& filename, const std::vector<Motion>& motion);
        void draw(const float& wScale, const float& hScale);
        
    private:
        int **mIndices;             // first : number of motion, second : number of frame
        int mNNodes;                // Number of Nodes        
        std::vector<Node*> mNodes;  // Nodes
        std::map<std::string, int> mMapLabelIndex;

        int mCurrentMotionIndex;
        int mCurrentFrame;
        
        const int addNode(Node *node);
        void insertNode(Node *n);
        void initIndices(const std::vector<Motion>& motions, int nMotions);
        void createTransitions( std::string& m1, int node1, int frame1, int motionID1,
                                std::string& m2, int node2, int frame2, int motionID2,
                                int transiction, int range, int totalFrames1, int totalFrames2);
    };
}

#endif /* defined(____Euclid__Graph____) */
