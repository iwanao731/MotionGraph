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
    this->mGhostNode = false;
    this->mIndex = -1;
    this->mNumChildren = 0;
}

SMGNode::~SMGNode()
{
    
}

bool SMGNode::hasParent()
{
    return this->mHasParent;
}

bool SMGNode::hasChildren()
{
    return this->mHasChild;
}

bool SMGNode::IsGhostNode()
{
    return this->mGhostNode;
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

void SMGNode::addChild(SMGNode *childNode)
{
    this->mHasChild = true;
    this->mChildren.push_back(childNode);
    mNumChildren++;
}

int SMGNode::getNodeIndex()
{
    return this->mIndex;
}

SMGNode* SMGNode::getParent()
{
    return this->mParentNode;
}

int SMGNode::getNumChildren()
{
    return this->mNumChildren;
}

Euclid::Node* SMGNode::getMGNode()
{
    return this->mNode;
}

SMGNode* SMGNode::getChild(int index)
{
    if(index < mNumChildren)
        return this->mChildren[index];
    else
        return NULL;
}


