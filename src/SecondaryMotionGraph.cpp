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
    
    cout << "node size : " << this->Graph::getNumNodes() << endl;
    mMGNodes.resize(this->Graph::getNumNodes());
}

int SMG::getNumSMGNodes()
{
    return this->mSMGNodes.size();
}

void SMG::constructeGraph(const int motionIndex, const int frameIndex)
{
    std::cout << "start Construct Graph" << std::endl;
    
    int nodeIndex = this->getNodeindex(motionIndex, frameIndex);
    
    // build initial secondary motion graph from motion graph
    this->initialization(nodeIndex);
    
    // expand for each dead node
    this->expansion();
    
    // 
    this->merge();
    
    std::cout << "end Construct Graph" << std::endl;
}

void SMG::initialization(const int nodeIndex)
{
    Node *startNode = this->getNode(nodeIndex);
    
    // build initial SMG network
    this->BFS(startNode);
    
    // Dead End Node make connecting to another node as Ghost Node considering to the connection of motion graph
    this->removeDeadEnd();  //Actually we have to choose next state of the most minimum simulation error
}

void SMG::expansion()
{
    cout << "start expansion" << endl;
    
    // 	descending sort considering error value
    std::sort(mEdgeQueue.begin(), mEdgeQueue.end(), SMGEdge::compareEdgeError);

//    for (auto m : mEdgeQueue) {
//        std::cout << m->getError() << std::endl;
//    }
    
//    int index = 0;
//    for (auto mm : mMGNodes){
//        cout << "No. " << index << " : " << mm.size() << endl;
//        index++;
//    }
    
    cout << "end expansion" << endl;
}

void SMG::merge()
{
    
}

int SMG::addSMGNode(Euclid::Node *n)
{
    SMGNode *node;
    node = new SMGNode;
    node->setMGNode(n);
    int index = this->mSMGNodes.size(); // index == 0
    node->setNodeIndex(index);
    this->mSMGNodes.push_back(node);
    
    // for expansion
    this->mMGNodes[n->getNodeID()].push_back(node);
    
    return index;
}

void SMG::addChildSMGNode(int SMGIndex, Node *childNode)
{
    SMGNode *smgNode;
    smgNode = new SMGNode;
    smgNode->setMGNode(childNode);
    smgNode->setParent(this->mSMGNodes[SMGIndex]);
    smgNode->setNodeIndex(mSMGNodes.size());
    
    // for expansion
    this->mMGNodes[childNode->getNodeID()].push_back(smgNode);
    
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

void SMG::removeDeadEnd()
{
    cout << "start removeDeadEnd" << endl;

    // add Ghost Node at each node
    int numNodes = this->getNumSMGNodes(); // causion: while the loop below, number of nodes is increasing
    
    for(int j=0; j<numNodes; j++) {
        
        SMGNode *n = this->mSMGNodes[j];
        
        // access only dead end node
        if(!n->hasChildren()) {
            
            // (TBD) We have to simulate and choose SMG index of most similar state of physics
            
            // add candidate of Ghost Node using Motion Graph network
            int numEdges = n->getMGNode()->getNumEdges(); // (TBD)<- Select next candidate based on similarity of physics model
            if(numEdges>0) {
                for (int i=0; i<numEdges; i++) {
                    // add children to dead end node
                    this->addChildSMGNode(n->getNodeIndex(), n->getMGNode()->getEdge(i)->getDestNode());
                    
                    // add transition error queue from node1 to node2
                    this->addEdgeQueue(n, this->mSMGNodes.back());  // (TBD) necessary to consider simulation error
                    
                    // set as Ghost Node
                    n->getChild(i)->setGhostNode(true);
                }
            }else{
                // (TBD) dead end node should be removed
            }
        }else{
            n->setGhostNode(false);
        }
    }
    
    cout << "end removeDeadEnd" << endl;
    
}

// (TBD) necessary to consider simulation error
void SMG::addEdgeQueue(SMGNode* node1, SMGNode *node2)
{
    SMGEdge *edge;
    edge = new SMGEdge;
    edge->setStartNode(node1);
    edge->setDestNode(node2);
    edge->setError(ofRandom(100));   // oF function temporary
    this->mEdgeQueue.push_back(edge);

    int index = node2->getMGNode()->getNodeID();
    
    cout << this->mEdgeQueue.back()->getError() << " : " << node2->getNodeIndex() << " : " << node1->getNodeIndex() << "->" << this->mMGNodes[index][0]->getNodeIndex() << endl;
    
}


