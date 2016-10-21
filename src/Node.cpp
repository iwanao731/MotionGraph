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

Node::Node()
{
    this->mNEdge = 0;
    this->mNodeID = -1;
    this->mFrameID = -1;
    this->mEndFrameID = -1;
}

Node::Node(const int id)
{
    this->mNEdge = 0;
    this->mNodeID = id;
    this->mFrameID = -1;
    this->mEndFrameID = -1;
}

Node::~Node()
{
    
}

int Node::getNumEdges()
{
    this->mNEdge = this->mEdges.size();
    return this->mNEdge;
}

void Node::removeEdge(const int index)
{
    if(this->mEdges.size()>index) {
        this->mEdges.erase(this->mEdges.begin() + index);
    }
}

using namespace std;
int Node::addEdge(Edge *edge)
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
        this->mNEdge++;
        return this->mNEdge;
    }else{
        return -1;
    }
}
    
    
Edge *Node::getEdge(const unsigned int index)
{
    if(index > this->mNEdge) return NULL;
    
    return &this->mEdges[index];
}

void Node::insertNode(const int motionID, const int frameID)
{
    
}
