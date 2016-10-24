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
        
        void setDestination(Node *node);
        void setStartNode(Node *node);
        
        Node *getDestination() const;
        Node *getStartNode() const;
            
    private:
        Node *mNode1;
        Node *mNode2;
        float mWeight;
        float mDistance;
    };
}
#endif /* defined(____Euclid__Edge____) */
