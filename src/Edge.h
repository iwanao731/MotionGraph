//
//  Edge.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Edge__
#define ____Edge__

#include <stdio.h>
#include <string>

class Node;

class Edge
{
public:
    Edge();
    Edge(Node *n, std::string label);
    ~Edge();
    
    void setLabel(const std::string name) { this->mLabel = name; }
    void setDestination(Node *node) { this->dest = node; }
    void setStartNode(Node *node) { this->start = node; }
    
    std::string getLabel() { return this->mLabel; }
    Node *getDestination() { return this->dest; }
    Node *getStartNode() { return this->start; }
        
private:
    Node *start;
    Node *dest;
    std::string mLabel;
    int mInit1, mInit2, mEnd1, mEnd2;
    
};

#endif /* defined(____Edge__) */
