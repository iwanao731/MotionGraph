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
        Edge(Node *n, const std::string& label);
        ~Edge();
        
        void setLabel(const std::string& name);
        void setDestination(Node *node);
        void setStartNode(Node *node);
        
        const std::string& getLabel() const;
        Node *getDestination() const;
        Node *getStartNode() const;
            
    private:
        Node *mStart;
        Node *mDest;
        std::string mLabel;
        int mInit1, mInit2, mEnd1, mEnd2;
        
    };
}
#endif /* defined(____Euclid__Edge____) */
