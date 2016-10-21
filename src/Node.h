//
//  Node.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Node__
#define ____Node__

#include <stdio.h>
#include <vector>
#include <string>

class Edge;

class Node
{
public:
    Node();
    Node(const int id);
    ~Node();
    
    int addEdge(Edge *edge);
    void setNodeID(const int index) { this->mNodeID = index; }
    void setFrameID(const int frameID) { this->mFrameID = frameID; }
    //void setEndFrameID(const int endFrameID) { this->mEndFrameID = endFrameID; }
    void setMotionID(const int motionID) { this->mMotionID = motionID; }
    void setMotionLabel(const std::string label) { this->mMotionLabel = label; }
    void insertNode(const int motionID, const int frameID);
    
    int getNodeID() { return this->mNodeID; }
    int getNumEdges();
    int getFrameID() { return this->mFrameID; }
    int getMotionID() { return this->mMotionID; }
    std::string getMotionLabel() { return this->mMotionLabel; }
    Edge *getEdge(const unsigned int index);
    void removeEdge(const int index);
    
private:
    int mNodeID;
    int mNEdge;
    int mFrameID;
    int mMotionID;
    int mEndFrameID;
    std::string mMotionLabel;
    std::vector<Edge> mEdges;
};

#endif /* defined(____Node__) */
