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

class SecondaryMotionGraph : protected Graph
{
    //using SMG = SecondaryMotionGraph; // same meaning typedef (C++11)

public:
    SecondaryMotionGraph();
    ~SecondaryMotionGraph();

    void loadGraph(const string& filename);
    void constructeGraph();
    
private:
    
    // corresponding mg node id
    Eigen::SparseMatrix<float> IRF; // Hair Motion
    // parent node' id
    // children nodes' id
    
    void initialization();
    void expansion();
    void merge();
    
    // Breath First Search
    void BFS();
};

#endif /* defined(____Secondary__Motion__Graph____) */
