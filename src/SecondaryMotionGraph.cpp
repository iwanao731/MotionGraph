//
//  SecondaryMotionGraph.cpp
//
//
//  Created by NAOYAIWAMOTO on 21/10/2016.
//
//

#include "SecondaryMotionGraph.h"

using SMG = SecondaryMotionGraph; // same meaning typedef (C++11)

SMG::SecondaryMotionGraph()
{
    
}

SMG::~SecondaryMotionGraph()
{
    
}

void SMG::loadGraph(const string& filename)
{
    this->Euclid::Graph::loadGraph(filename);
}

int SMG::getNumNode()
{
    return this->mSMGNodes.size();
}

void SMG::constructeGraph(const int motionIndex, const int frameIndex)
{
    std::cout << "start Construct Graph" << std::endl;
    int nodeIndex = this->getNodeindex(motionIndex, frameIndex);
    cout << "nodeIndex : " << nodeIndex << endl;
    
    this->initialization(nodeIndex);
    this->expansion();
    this->merge();
    std::cout << "end Construct Graph" << std::endl;
}

void SMG::initialization(const int nodeIndex)
{
    Node *startNode = this->getNode(nodeIndex);
    cout << startNode->getNodeID() << "," << startNode->getNumEdges() << endl;;
    
    this->BFS(startNode);
}

void SMG::expansion()
{

}

void SMG::merge()
{
    
}

int SMG::addSMGNode(Euclid::Node *n)
{
    SMGNode *node;
    node = new SMGNode;
    node->setMGNode(n);
    int index = this->mSMGNodes.size();
    node->setNodeIndex(index);
    this->mSMGNodes.push_back(node);
    return index;
}

void SMG::addChildSMGNode(int SMGIndex, Node *childNode)
{
    SMGNode *smgNode;
    smgNode = new SMGNode;
    smgNode->setMGNode(childNode);
    smgNode->setParent(this->mSMGNodes[SMGIndex]);
    smgNode->setNodeIndex(mSMGNodes.size());
    
    this->mSMGNodes.push_back(smgNode);
    this->mSMGNodes[SMGIndex]->addChild(smgNode);
}

// search each node j from node i in a breath-first manner
void SMG::BFS(Euclid::Node *n)
{
    // Mark all the vertices as not visited
    std::vector<bool> visited;
    visited.resize(this->getNumNodes());
    std::fill(visited.begin(), visited.end(), false);
    
    // Create a queue for BFS
    list<Node*> nodeQueue;
    list<int> depthQueue;
    list<int> parentQueue;
    
    // Mark the current node as visited and enqueue it
    visited[n->getNodeID()] = true;
    
    nodeQueue.push_back(n);
    depthQueue.push_back(0);
    parentQueue.push_back(0);

    // add new smg node and return SMG index
    int SMGIndex = this->addSMGNode(n);
    
    while(!nodeQueue.empty())
    {
        // Dequeue a node from queue and print it
        n = nodeQueue.front();
        int depth = depthQueue.front();
        int parent = parentQueue.front();
        string depthStr;
        for(int i=0; i<depth; i++){
            depthStr += " ";
        }
        
        nodeQueue.pop_front();
        depthQueue.pop_front();
        parentQueue.pop_front();
        
        // Get all adjacent nodes of the dequeued node *n
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(int j=0; j<n->getNumEdges(); j++){
            int MGIndex = n->getEdge(j)->getDestNode()->getNodeID();
            if(!visited[MGIndex])
            {
                visited[MGIndex] = true;
                nodeQueue.push_back(n->getEdge(j)->getDestNode());
                depthQueue.push_back(depth+1);
                parentQueue.push_back(n->getNodeID());
                
                this->addChildSMGNode(SMGIndex, n->getEdge(j)->getDestNode());
            }
        }
        SMGIndex++;
    }
}
