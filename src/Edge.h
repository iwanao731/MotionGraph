//
//  Edge.h
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#ifndef ____Euclid__Edge____
#define ____Euclid__Edge____

#include <stdio.h>
#include <string>

namespace Euclid
{
    class Node;

    class Edge
    {
    public:
        Edge();
        Edge(Node *n);
        ~Edge();
        
        void setStartNode(Node *node);
        void setDestination(Node *node);
        
        Node *getStartNode() const;
        Node *getDestination() const;
        
    private:
        float mWeight;
        float mDistance;
        Node *mNode1;
        Node *mNode2;
        
    };
}
#endif /* defined(____Euclid__Edge____) */
