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

namespace Euclid
{
    class Edge;

    class Node
    {
    public:
        Node();
        Node(const int id);
        ~Node();
        
        // setter
        void setNodeID(const int index);
        void setFrameID(const int frameID);
        void setMotionID(const int motionID);
        void setMotionLabel(const std::string& label);
        
        // getter
        const int getNodeID() const;
        const int getNumEdges() const;
        const int getFrameID() const;
        const int getMotionID() const;
        const std::string& getMotionLabel() const;
        Edge *getEdge(const unsigned int index);

        const int addEdge(Edge *edge);
        void insertNode(const int motionID, const int frameID);
        void removeEdge(const int index);
        
    private:
        int mNodeID;
        int mFrameID;
        int mMotionID;
        int mEndFrameID;
        std::string mMotionLabel;
        std::vector<Edge> mEdges;
    };
}
#endif /* defined(____Node__) */
