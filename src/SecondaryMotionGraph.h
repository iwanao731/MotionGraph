//
//  SecondaryMotionGraph.h
//
//
//  Created by NAOYAIWAMOTO on 21/10/2016.
//
//

#ifndef ____Secondary__Motion__Graph____
#define ____Secondary__Motion__Graph____

#include <stdio.h>
#include <list>
#include <limits> // for rand function
#include <random>
#include "Eigen/Sparse"
#include "MotionGraph.h"
#include "SMGNode.h"
#include "SMGEdge.h"

class SecondaryMotionGraph : public Euclid::Graph
{
public:
    SecondaryMotionGraph();
    virtual ~SecondaryMotionGraph();

    void loadGraph(const std::string& filename);
    void constructeGraph(int motionIndex, int frameIndex);
    void drawTree(float scaleX, float scaleY);
    float expansion();


    const int getNumSMGNodes() const;

private:
    
    vector<SMGNode*> mSMGNodes;
    Eigen::SparseMatrix<float> mIRF; // Hair Motion
    std::vector<SMGEdge*> mEdgeQueue;
    std::vector<std::vector<SMGNode*> > mMGNodes; // SMG Nodes at each MG Node.
    
    void initialization(int nodeIndex);
    void merge();
    
    int addSMGNode(Euclid::Node *n);
    void addChildSMGNode(SMGNode *parentNode, Euclid::Node *childNode);
    void addEdgeQueue(SMGNode* node1, SMGNode *node2);
    
    void setChildSMGNode(SMGNode *parentNode, SMGNode *childNode);
    
    /// Breath First Search
    void BFS(Euclid::Node *n);
    void removeDeadEnd();    
};

#endif /* defined(____Secondary__Motion__Graph____) */
