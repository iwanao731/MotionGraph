//
//  Graph.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Graph.h"

Graph::Graph()
{
    this->mIndices = NULL;
    this->mNNodes = 0;
}

Graph::~Graph()
{
    
}

void Graph::initIndices(std::vector<Motion> motions, const int nMotions)
{
    int maxFrames = -1;
    
    for(auto m : motions)
    {
        if(maxFrames < m.getNFrames())
            maxFrames = m.getNFrames();
    }
    
    cout << "nMotions : " << nMotions << endl;
    
    this->mIndices = new int *[nMotions];
    
    for(int i=0; i<nMotions; i++){
        this->mIndices[i] = new int [maxFrames];
    }
    
    for(int i=0; i<nMotions; i++){
        for(int j=0; j<maxFrames; j++){
            this->mIndices[i][j] = -1;
        }
    }
    
    // make graph structure with setting node and edge
    /*
            e1
     1-------------->2

     */
    int i=0;
    for(auto m : motions) {
        Node *n1 = new Node;
        Node *n2 = new Node;
        Edge *e = new Edge(n2, m.getLabel());
        
        n1->addEdge(e);
        n1->setMotionID(i);
        n1->setMotionLabel(m.getLabel());
        n1->setFrameID(0);
        
        int lastPos = m.getNFrames()-1;
        n2->setMotionID(i);
        n2->setMotionLabel(m.getLabel());
        n2->setFrameID(lastPos);

        this->mIndices[i][0] = this->addNode(n1);
        this->mIndices[i][lastPos] = this->addNode(n2);
        i++;
    }
}

void Graph::exportGraphFile(const string filename, const std::vector<std::string> motion_paths)
{   
    std::cout << "export graph file: " << endl;
    std::stringstream ss;
    ss << filename;
    
    // using openFrameworks utility function
    ofFile file;
    std::string label = file.getAbsolutePath() + "/" + ss.str();
    
    std::ofstream ofs(label);
    if(!ofs) {
        std::cerr << "Failed open file" << std::endl;
        std::exit(1);
    }else{
        cout << "export... " << ss.str() << endl;
    }
    
    std::cout << "Numbert of Node" << this->getNumNodes() << endl;
    
    ofs << "# Graph Version 0.1" << endl;
    
    int previousFrame = -1;
    
    // add Motion Path;
    int motionNum = motion_paths.size();
    
    ofs << "MotionNum " << motionNum << endl;
    
    for(int i=0; i<motionNum; i++) {
        ofs << "MotionPath " << motion_paths[i] << std::endl;
    }
    
    for(int i=0; i<this->getNumNodes(); i++) {
        if(this->getNode(i)->getNumEdges() > 0) {
            ofs << "MotionName " << this->getNode(i)->getMotionLabel() << " ";
            ofs << "frame " << this->getNode(i)->getFrameID() << " ";
            ofs << "NumEdges " << this->getNode(i)->getNumEdges() << endl;;
            
            for(int j=0; j<this->getNode(i)->getNumEdges(); j++) {
                ofs << "    TargetLabel " << this->getNode(i)->getEdge(j)->getDestination()->getMotionLabel() << " ";
                ofs << "frame " << this->getNode(i)->getEdge(j)->getDestination()->getFrameID() << endl;;
            }
        }
    }
    ofs.close();
}

void Graph::draw(const float wScale, const float hScale)
{
    ofSetColor(50);

    ofVec2f offset(10,10);
    ofSetColor(0);
    int count = 0;
    for(int i=0; i<this->getNumNodes(); i++) {
        
        int index1, index2;
        int frame1, frame2;
        
        frame1 = this->getNode(i)->getFrameID();
        index1 = this->getNode(i)->getMotionID();
        ofDrawCircle(offset.x + frame1 * wScale, offset.y + index1 * hScale, 2.0);
        
        for(int j=0; j<this->getNode(i)->getNumEdges(); j++) {
            index2 = this->getNode(i)->getEdge(j)->getDestination()->getMotionID();
            frame2 = this->getNode(i)->getEdge(j)->getDestination()->getFrameID();
            
            if(index1 == index2){
                ofPoint p1(offset.x + frame1 * wScale, offset.y + index1 * hScale);
                ofPoint p2(offset.x + frame2 * wScale, offset.y + index2 * hScale);
                ofPoint midPoint( (p1 + p2)/2 );
                midPoint.set(midPoint.x, midPoint.y + 0.1 * hScale);
                ofDrawLine(p1, midPoint);
                ofDrawLine(midPoint, p2);
                
            }else{
                ofDrawLine(offset.x + frame1 * wScale, offset.y + index1 * hScale, offset.x + frame2 * wScale, offset.y + index2 * hScale);
            }
            ofDrawCircle(offset.x + frame2 * wScale, offset.y + index2 * hScale, 2.0);
        }
    }
    
    ofSetColor(255, 0, 0);
    ofDrawCircle(offset.x + mCurrentFrame * wScale, offset.y + mCurrentMotionIndex * hScale, 10.0);
}

void Graph::constructGraph(std::vector<Motion> motions, const int nMotions, const float threshold, const int nCoincidents)
{
    if(nMotions == 0) return;
    
    // initialize
    this->initIndices(motions, nMotions);
    
    this->mMap = new Map(nMotions);
    this->mMap->setThreshold(threshold);
    this->mMap->setNSteps(nCoincidents);
    this->mMap->constructMap(motions, nMotions); // also export each map file.

    for(int i=0 ; i<this->mMap->getNRelations(); i++){
        std::string label1 = this->mMap->getRelations(i, 0);
        std::string label2 = this->mMap->getRelations(i, 1);
        
        int index1 = -1, index2 = -1;
        
        int j=0;
        for(auto m : motions){
            if(m.getLabel() == label1) index1 = j;
            if(m.getLabel() == label2) index2 = j;
            j++;
        }
        
        int nRelations = 0; // number of similar poses
        
        if(index1 != -1 && index2 != -1) {
            std::vector<int> minFrame1, minFrame2;
            
            // Get Minumum
            nRelations = this->mMap->getMinimums(i, &minFrame1, &minFrame2);
            
            for(j=0; j<nRelations; j++) {
                if(this->mIndices[index1][minFrame1[j]] < 0 || this->mIndices[index1][minFrame1[j]] > this->mNNodes){
                    Node *n = new Node();
                    this->mIndices[index1][minFrame1[j]] = this->addNode(n);
                }
                
                if(this->mIndices[index2][minFrame2[j]] < 0 || this->mIndices[index2][minFrame2[j]] > this->mNNodes){
                    Node *n = new Node();
                    this->mIndices[index2][minFrame2[j]] = this->addNode(n);
                }

                this->createTransitions(label1, this->mIndices[index1][minFrame1[j]], minFrame1[j], index1,
                        label2, this->mIndices[index2][minFrame2[j]], minFrame2[j], index2,
                        j, this->mMap->getNSteps(),
                        motions.at(index1).getNFrames(), motions.at(index2).getNFrames() );
                
            }
        }
    }
}

/*
        e1					   e3	   e4
 1-------------->2			1----->5------->2
                    ---->		    \ e7
                                     \
 3-------------->4			3-------->6---->4
        e2						e5		e6
 */
void Graph::createTransitions(std::string m1, int node1, int frame1, int motionID1,
                              std::string m2, int node2, int frame2, int motionID2,
                              int transiction,int range, int totalFrames1, int totalFrames2)
{
    std::stringstream ss;
    ss << m1 << "_" ;
    ss << m2 << "_" << transiction;
    std::string newName = ss.str();

    this->getNode(node1)->setFrameID(frame1);
    this->getNode(node2)->setFrameID(frame2);
    
    this->getNode(node1)->setMotionID(motionID1);
    this->getNode(node2)->setMotionID(motionID2);
    
    this->getNode(node1)->setMotionLabel(m1);
    this->getNode(node2)->setMotionLabel(m2);
    
    this->insertNode(this->getNode(node1));
    this->insertNode(this->getNode(node2));
    
    
    // TBD
    // not cycle in same motion
    if(motionID1 != motionID2){
        this->getNode(node1)->addEdge(new Edge(this->getNode(node2),newName));
    }
}

/*
        <------------->        <----> <----->
       *---------------*      *------*-------*
*/
void Graph::insertNode(Node *n)
{

    int count = 0;
    for(int i=0; i<this->mNodes.size(); i++) {
        if(this->mNodes[i]->getMotionID() == n->getMotionID()) {
            
            for(int j=0; j<this->mNodes[i]->getNumEdges(); j++) {
                if(this->mNodes[i]->getEdge(j)->getDestination()->getMotionID() == n->getMotionID()) {
                    
                    if(this->mNodes[i]->getFrameID() < n->getFrameID() && n->getFrameID() < this->mNodes[i]->getEdge(j)->getDestination()->getFrameID())
                    {
                        Edge *e = new Edge(this->mNodes[i]->getEdge(j)->getDestination(), this->mNodes[i]->getMotionLabel());
                        n->addEdge(e);
                        this->mNodes[i]->getEdge(j)->setDestination(n);
                        //this->mNodes[i]->setEndFrameID(this->mNodes[i]->getEdge(j)->getDestination()->getFrameID());
                        count++;
                    }
                }
            }
        }
    }
}

Node* Graph::getNode(const int node)
{
    if(node >= this->mNNodes || node < 0) return NULL;
    else return this->mNodes.at(node);
}

int Graph::addNode(Node *node)
{
    node->setNodeID(this->mNNodes);
    this->mNodes.push_back(node);
    this->mNNodes++;
    return node->getNodeID();
}

bool Graph::hasBranch(const int motionIndex, const int frameId)
{
    mCurrentMotionIndex = motionIndex;
    mCurrentFrame = frameId;
    if(this->mIndices[motionIndex][frameId] > 0)
        return true;
    else
        return false;
}

int Graph::getNodeindex(const int motionIndex, const int frameId)
{
    mCurrentMotionIndex = motionIndex;
    mCurrentFrame = frameId;
    return this->mIndices[motionIndex][frameId];
}




