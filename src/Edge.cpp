//
//  Edge.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Edge.h"
#include "Node.h"

Edge::Edge()
{
    this->dest = NULL;
}

Edge::Edge(Node *n, std::string label)
{
    this->dest = n;
    this->mLabel = label;
}

Edge::~Edge()
{
    
}
