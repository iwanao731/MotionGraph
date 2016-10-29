//
//  SecondaryMotionGraph.cpp
//
//
//  Created by NAOYAIWAMOTO on 21/10/2016.
//
//

#include "SecondaryMotionGraph.h"

using SMG = SecondaryMotionGraph; // same meaning typedef (C++11)

using namespace Euclid;

SMG::SecondaryMotionGraph()
{
    
}

SMG::~SecondaryMotionGraph()
{
    
}

void SMG::loadGraph(const std::string& filename)
{
    this->Euclid::Graph::loadGraph(filename);
    
    cout << "node size : " << this->Graph::getNumNodes() << endl;
    mMGNodes.resize(this->Graph::getNumNodes());
}

const int SMG::getNumSMGNodes() const
{
    return this->mSMGNodes.size();
}

void SMG::constructeGraph(int motionIndex, int frameIndex)
{
    std::cout << "start Construct Graph" << std::endl;
    
    int nodeIndex = this->getNodeindex(motionIndex, frameIndex);
    
    // build initial secondary motion graph from motion graph
    this->initialization(nodeIndex);
    
//    // expand for each dead node
//    for(int k=0; k<5; k++){
//        cout << "error :  " << this->expansion() << endl;
//    }
//    
//    this->merge();
    
    std::cout << "end Construct Graph" << std::endl;
}

void SMG::initialization(int nodeIndex)
{
    Node *startNode = this->getNode(nodeIndex);
    
    // build initial SMG network
    this->BFS(startNode);
    
    // Dead End Node make connecting to another node as Ghost Node considering to the connection of motion graph
    this->removeDeadEnd();  //Actually we have to choose next state of the most minimum simulation error
}

float SMG::expansion()
{
    cout << "start expansion" << endl;
    
    // 	Ascending sort considering error value
    std::sort(mEdgeQueue.begin(), mEdgeQueue.end(), SMGEdge::compareEdgeError);
    SMGEdge *largestErrorEdge = mEdgeQueue.back();
    this->addChildSMGNode(largestErrorEdge->getStartNode(), largestErrorEdge->getDestMGNode());
    
    // remove the edge
    this->mEdgeQueue.pop_back();
    
    // re-initialization
    this->initialization(this->mSMGNodes.back()->getMGNode()->getNodeID());
    std::sort(mEdgeQueue.begin(), mEdgeQueue.end(), SMGEdge::compareEdgeError);

    cout << "size: " << mEdgeQueue.size() << endl;
    cout << "end expansion" << endl;
    return mEdgeQueue.back()->getError();
}

void SMG::merge()
{
    std::cout << "starting merge ..." << std::endl;
    
    for (auto m : this->mSMGNodes){
        cout << m->getMGNode()->getNodeID() << " : " << m->getNumChildren() << " -> ";
        for(int i=0; i<m->getNumChildren(); i++){
            cout << m->getChild(i)->getMGNode()->getNodeID() << ",";
        }
        cout << endl;
    }
    
    std::cout << "end merge ..." << std::endl;
}

ofVec3f calcBranchPos(int index, int numChild, float length, float depth)
{
    ofVec3f pos(0);
    float scale = 100;
    float ratio = 7.0f;
    float value = pow(1+scale, -depth/ratio) * scale;
    
    pos.y = length;
    if (numChild == 1) {
        pos.x = 0;
    }else if(numChild == 2){
        if(index == 0)
            pos.x = -value;
        else
            pos.x = value;
    }else{
        if (index == 0) {
            pos.x = -value;
        }else if(index == 1){
            pos.x = 0;
        }else{
            pos.x = value;
        }
    }
    return pos;
}

void SMG::drawTree(float scaleX, float scaleY)
{
    ofSetColor(50);
    
    std::vector<bool> visited(this->getNumSMGNodes());
    std::fill(visited.begin(), visited.end(), false);
    
    ofTranslate(ofGetWidth()/2, 20);
    ofPushMatrix();
    
    SMGNode *root = this->mSMGNodes[0];
    
    list<SMGNode*> nodeQueue;
    list<int> depthQueue;
    list<ofVec3f> posQueue;
    
    nodeQueue.push_back(root);
    depthQueue.push_back(0);
    posQueue.push_back(ofVec3f(0));
    visited[root->getNodeIndex()] = true;
    
    ofDrawCircle(0, 0, 5);
    
    while (!nodeQueue.empty()) {
        
        SMGNode *n = nodeQueue.front();
        int depth = depthQueue.front();
        int numChild = n->getNumChildren();
        ofVec3f pos = posQueue.front();
        
        nodeQueue.pop_front();
        depthQueue.pop_front();
        posQueue.pop_front();
        
        for(int j=0; j<numChild; j++) {
            int nextID = n->getChild(j)->getNodeIndex();
            if(!visited[nextID]) {
                
                visited[nextID] = true;
                nodeQueue.push_back(n->getChild(j));
                depthQueue.push_back(depth+1);
                
                ofVec3f childPos = pos + calcBranchPos(j, numChild, 40, depth+1);
                posQueue.push_back(childPos);
                ofDrawLine(pos.x * scaleX, pos.y * scaleY, childPos.x * scaleX, childPos.y * scaleY);
                
                if(this->mSMGNodes[nextID]->getNumChildren() == 0)
                    ofSetColor(255, 0, 0);
                else{
                    ofSetColor(50);
                }
                ofDrawCircle(childPos.x * scaleX, childPos.y * scaleY, 5.0f/(float)(depth+1));
                ofSetColor(50);
            }
        }
    }
    ofPopMatrix();
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

void SMG::addChildSMGNode(SMGNode *parentNode, Node *childNode)
{
    SMGNode *smgNode;
    smgNode = new SMGNode;
    smgNode->setMGNode(childNode);
    smgNode->setParent(parentNode);
    smgNode->setNodeIndex(mSMGNodes.size());
    
    // for expansion
    this->mMGNodes[childNode->getNodeID()].push_back(smgNode);
    
    this->mSMGNodes.push_back(smgNode);
    parentNode->addChild(smgNode);
}

void SMG::setChildSMGNode(SMGNode *parentNode, SMGNode *childNode)
{
    parentNode->addChild(childNode);
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
//    list<int> depthQueue;
//    list<int> parentQueue;
    
    // Mark the current node as visited and enqueue it
    visited[n->getNodeID()] = true;
    
    nodeQueue.push_back(n);
    //depthQueue.push_back(0);
    //parentQueue.push_back(0);

    // add new smg node and return SMG index
    int SMGIndex = this->addSMGNode(n);
    
    while(!nodeQueue.empty())
    {
        // Dequeue a node from queue and print it
        n = nodeQueue.front();
        //int depth = depthQueue.front();
        //int parent = parentQueue.front();
        
        nodeQueue.pop_front();
        //depthQueue.pop_front();
        //parentQueue.pop_front();
        
        // Get all adjacent nodes of the dequeued node *n
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(int j=0; j<n->getNumEdges(); j++){
            int MGIndex = n->getEdge(j)->getDestNode()->getNodeID();
            if(!visited[MGIndex])
            {
                visited[MGIndex] = true;
                nodeQueue.push_back(n->getEdge(j)->getDestNode());
                //depthQueue.push_back(depth+1);
                //parentQueue.push_back(n->getNodeID());
                
                cout << SMGIndex << "," << n->getEdge(j)->getDestNode()->getNodeID() << endl;
                this->addChildSMGNode(this->mSMGNodes[SMGIndex], n->getEdge(j)->getDestNode());
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
                    //this->addChildSMGNode(n, n->getMGNode()->getEdge(i)->getDestNode());
                    
                    // set
                    SMGNode *child = this->mMGNodes[n->getMGNode()->getEdge(i)->getDestNode()->getNodeID()].front();
                    this->setChildSMGNode(n, child);
                    
                    // add transition error queue from node1 to node2
                    this->addEdgeQueue(n, child);  // (TBD) necessary to consider simulation error
                    
                    // set as Ghost Node
                    //n->getChild(i)->setGhostNode(true);
                }
            }else{
                // (TBD) dead end node should be removed
            }
        }else{
            //n->setGhostNode(false);
        }
    }
    
    cout << "end removeDeadEnd" << endl;
}

// for calculate random value from 0 to max.
int randomError(float max) {
    return (max * rand() / float(RAND_MAX)) * (1.0f - std::numeric_limits<float>::epsilon());
}

// (TBD) necessary to consider simulation error
void SMG::addEdgeQueue(SMGNode* node1, SMGNode *node2)
{
    SMGEdge *edge;
    edge = new SMGEdge;
    edge->setStartNode(node1);
    edge->setDestNode(node2);
    
    edge->setError(randomError(100)); //  <- (TBD) should be put simulation error here
    
    this->mEdgeQueue.push_back(edge);
}