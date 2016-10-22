//
//  SecondaryMotionGraph.cpp
//
//
//  Created by NAOYAIWAMOTO on 21/10/2016.
//
//

#include "SecondaryMotionGraph.h"

using SMG = SecondaryMotionGraph; // same meaning typedef (C++11)

SMG::SecondaryMotionGraph()
{
    
}

SMG::~SecondaryMotionGraph()
{
    
}

void SMG::constructeGraph()
{
    this->initialization();
    
    this->expansion();
    
    this->merge();
}

void SMG::initialization()
{
    // search each node j from node i in a breath-first manner
    
    for(int i=0; i<this->getNumNodes(); i++)
    {
        // start this node
        Node *n = this->getNode(i);
        
        for(int j=0; j<n->getNumEdges(); j++){
            
        }
    }
}

void SMG::expansion()
{
    
}

void SMG::merge()
{
    
}
