//
//  SMGNode.cpp
//  
//
//  Created by NAOYAIWAMOTO on 24/10/2016.
//
//

#include "SMGNode.h"

SMGNode::SMGNode()
{
    this->mHasParent = false;
    this->mHasChild = false;
    this->mIsGhostNode = false;
    this->mIndex = -1;
}

SMGNode::~SMGNode()
{
    
}

const bool SMGNode::hasParent() const
{
    return this->mHasParent;
}

const bool SMGNode::hasChildren() const
{
    return this->mHasChild;
}

const bool SMGNode::IsGhostNode() const
{
    return this->mIsGhostNode;
}

void SMGNode::setNodeIndex(int index)
{
    this->mIndex = index;
}

void SMGNode::setMGNode(Euclid::Node *n)
{
    mNode = n;
}

void SMGNode::setParent(SMGNode *parentNode)
{
    this->mParentNode = parentNode;
    this->mHasParent = true;
}

void SMGNode::setGhostNode(bool bValue)
{
    this->mIsGhostNode = bValue;
}

void SMGNode::addChild(SMGNode *childNode)
{
    this->mHasChild = true;
    this->mChildren.push_back(childNode);
}

const int SMGNode::getNodeIndex() const
{
    return this->mIndex;
}

const int SMGNode::getNumChildren() const
{
    return this->mChildren.size();
}

SMGNode* SMGNode::getParent() const
{
    return this->mParentNode;
}

Euclid::Node* SMGNode::getMGNode() const
{
    return this->mNode;
}

SMGNode* SMGNode::getChild(int index) const
{
    if(0 <= index && index < this->mChildren.size())
        return this->mChildren[index];
    else
        return NULL;
}


