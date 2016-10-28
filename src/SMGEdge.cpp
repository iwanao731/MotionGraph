//
//  SMGEdge.cpp
//  
//
//  Created by NAOYAIWAMOTO on 25/10/2016.
//
//

#include "SMGEdge.h"

using namespace Euclid;

SMGEdge::SMGEdge() : mError(0.0f)
{
    
}

SMGEdge::~SMGEdge()
{

}

void SMGEdge::setStartNode(SMGNode *node)
{
    this->mNode1 = node;
}

void SMGEdge::setDestNode(SMGNode *node)
{
    this->mNode2 = node;
}

void SMGEdge::setError(float errorValue)
{
    this->mError = errorValue;
}

SMGNode *SMGEdge::getStartNode() const
{
    return this->mNode1;
}

SMGNode *SMGEdge::getDestNode() const
{
    return this->mNode2;
}

Node *SMGEdge::getStartMGNode() const
{
    // If mNode1 does not have actual value, return null pointer
    if(!mNode1)
    {
        return nullptr;
    }
    return mNode1->getMGNode();
}

Node *SMGEdge::getDestMGNode() const
{
    // If mNode1 does not have actual value, return null pointer
    if(!mNode2)
    {
        return nullptr;
    }
    return mNode2->getMGNode();
}

const float SMGEdge::getError() const
{
    return this->mError;
}

bool SMGEdge::compareEdgeError(const SMGEdge* lhs, const SMGEdge* rhs)
{
    // If mNode1 does not have actual value, return null pointer
    if(!lhs || !rhs){
        return nullptr;
    }
    return (lhs->mError < rhs->mError);
}

