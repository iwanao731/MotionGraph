//
//  Graph.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Graph__
#define ____Graph__

#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
#include "Node.h"
#include "Motion.h"
#include "Edge.h"
#include "Map.h"
#include <ofMain.h>

class Graph
{
public:
    Graph();
    ~Graph();

    int getNumNodes() { return this->mNNodes; }
    Node* getNode(const int node);
    
    bool hasBranch(const int motionIndex, const int frameId);
    int getNodeindex(const int motionIndex, const int frameId);

    void constructGraph(std::vector<Motion> motions, const int nMotions, const float threshold, const int nCoincidents);
    void exportGraphFile(const string filename, const std::vector<std::string> motion_paths);
    void draw(const float wScale, const float hScale);
    //float calcInterpolateValue(const int p, const int k);
    
private:
    int **mIndices;             // first : number of motion, second : number of frame
    int mNNodes;                // Number of Nodes
    std::vector<Node*> mNodes;  // Nodes
    Map *mMap;                  // ErrorMap

    int mCurrentMotionIndex;
    int mCurrentFrame;
    
    int addNode(Node *node);
    void insertNode(Node *n);
    void initIndices(std::vector<Motion> motions, const int nMotions);
    void createTransitions( std::string m1, int node1, int frame1, int motionID1,
                            std::string m2, int node2, int frame2, int motionID2,
                            int transiction,int range, int totalFrames1, int totalFrames2);  
};

#endif /* defined(____Graph__) */
