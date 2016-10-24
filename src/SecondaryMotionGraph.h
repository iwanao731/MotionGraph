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
#include "Eigen/Sparse"
#include "MotionGraph.h"

class SecondaryMotionGraph : public Euclid::Graph
{
public:
    SecondaryMotionGraph();
    virtual ~SecondaryMotionGraph();

    void loadGraph(const string& filename);
    void constructeGraph(const int motionIndex, const int frameIndex);
    
private:
    Eigen::SparseMatrix<float> IRF; // Hair Motion
    
    void initialization(const int nodeIndex);
    void expansion();
    void merge();
    
    // Breath First Search
    void BFS(Euclid::Node *n);
};

#endif /* defined(____Secondary__Motion__Graph____) */
