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
    this->mDest = NULL;
}

Edge::Edge(Node *n, const std::string& label)
{
    this->mDest = n;
    this->mLabel = label;
}

Edge::~Edge()
{
    
}

void Edge::setLabel(const std::string& name)
{
    this->mLabel = name;
}

void Edge::setDestination(Node *node)
{
    this->mDest = node;
}

void Edge::setStartNode(Node *node)
{
    this->mStart = node;
}

const std::string& Edge::getLabel() const
{
    return this->mLabel;
}

Node *Edge::getDestination() const
{
    return this->mDest;
}

Node *Edge::getStartNode() const
{
    return this->mStart;
}
