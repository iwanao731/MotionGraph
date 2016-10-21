//
//  Node.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace Euclid;

Node::Node()
{
    this->mNodeID = -1;
    this->mFrameID = -1;
    this->mEndFrameID = -1;
}

Node::Node(const int id)
{
    this->mNodeID = id;
    this->mFrameID = -1;
    this->mEndFrameID = -1;
}

Node::~Node()
{
    
}

void Node::setNodeID(const int index)
{
    this->mNodeID = index;
}

void Node::setFrameID(const int frameID)
{
    this->mFrameID = frameID;
}

void Node::setMotionID(const int motionID)
{
    this->mMotionID = motionID;
}

void Node::setMotionLabel(const std::string& label)
{
    this->mMotionLabel = label;
}

const int Node::getNodeID() const
{
    return this->mNodeID;
}

const int Node::getNumEdges() const
{
    return this->mEdges.size();
}

const int Node::getFrameID() const
{
    return this->mFrameID;
}

const int Node::getMotionID() const
{
    return this->mMotionID;
}

const std::string& Node::getMotionLabel() const
{
    return this->mMotionLabel;
}

Edge *Node::getEdge(const unsigned int index)
{
    if(index > this->getNumEdges()) return NULL;
    
    return &this->mEdges[index];
}

void Node::removeEdge(const int index)
{
    if(this->getNumEdges() > index) {
        this->mEdges.erase(this->mEdges.begin() + index);
    }
}

const int Node::addEdge(Edge *edge)
{
    if(!edge) return -1;
    
    bool bEdge = true;
    
    for(auto e1 : this->mEdges) {
        if(e1.getDestination()->getFrameID() == edge->getDestination()->getFrameID()) {
            if(e1.getDestination()->getMotionLabel() == edge->getDestination()->getMotionLabel()) {
                bEdge = false;
            }
        }
    }
    
    if(bEdge == true) {
        edge->setStartNode(this);
        this->mEdges.push_back(*edge);
        return this->getNumEdges();
    }else{
        return -1;
    }
}

void Node::insertNode(const int motionID, const int frameID)
{
    
}
