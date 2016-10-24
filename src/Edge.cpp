//
//  Edge.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Edge.h"
#include "Node.h"

using namespace Euclid;

Edge::Edge()
{
    this->mNode2 = NULL;
}

Edge::Edge(Node *n)
{
    this->mNode2 = n;
}

Edge::~Edge()
{
    
}

void Edge::setDestination(Node *node)
{
    this->mNode2 = node;
}

void Edge::setStartNode(Node *node)
{
    this->mNode1 = node;
}

Node *Edge::getDestination() const
{
    return this->mNode2;
}

Node *Edge::getStartNode() const
{
    return this->mNode1;
}
