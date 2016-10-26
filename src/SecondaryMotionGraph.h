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
#include "Eigen/Sparse"
#include "MotionGraph.h"
#include "SMGNode.h"
#include "SMGEdge.h"

class SecondaryMotionGraph : public Euclid::Graph
{
public:
    SecondaryMotionGraph();
    virtual ~SecondaryMotionGraph();

    void loadGraph(const string& filename);
    void constructeGraph(const int motionIndex, const int frameIndex);

    int getNumSMGNodes();

private:
    
    vector<SMGNode*> mSMGNodes;
    Eigen::SparseMatrix<float> mIRF; // Hair Motion
    std::vector<SMGEdge*> mEdgeQueue;
    std::vector<std::vector<SMGNode*> > mMGNodes; // SMG Nodes at each MG Node.
    
    void initialization(const int nodeIndex);
    float expansion();
    void merge();
    
    int addSMGNode(Euclid::Node *n);
    void addChildSMGNode(SMGNode *parentNode, Euclid::Node *childNode);
    void addEdgeQueue(SMGNode* node1, SMGNode *node2);
    
    void setChildSMGNode(SMGNode *parentNode, SMGNode *childNode);
    
    /// Breath First Search
    void BFS(Euclid::Node *n);
    
    /// 
    void removeDeadEnd();
};

#endif /* defined(____Secondary__Motion__Graph____) */
