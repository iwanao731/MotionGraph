//
//  Graph.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "Graph.h"

using namespace Euclid;

Graph::Graph()
{
    this->mIndices = NULL;
    this->mNNodes = 0;
}

Graph::~Graph()
{
    
}

const int Graph::getNumNodes() const
{
    return this->mNNodes;
}

Node* Graph::getNode(const int node)
{
    if(node >= this->mNNodes || node < 0) return NULL;
    else return this->mNodes.at(node);
}

const bool Graph::hasBranch(const int motionIndex, const int frameId)
{
    mCurrentMotionIndex = motionIndex;
    mCurrentFrame = frameId;
    if(this->mIndices[motionIndex][frameId] > 0)
        return true;
    else
        return false;
}

const int Graph::getNodeindex(const int motionIndex, const int frameId)
{
    mCurrentMotionIndex = motionIndex;
    mCurrentFrame = frameId;
    return this->mIndices[motionIndex][frameId];
}

void Graph::constructGraph(const std::vector<Motion>& motions, const int nMotions, const float& threshold, const int nCoincidents)
{
    if(nMotions == 0) return;
    
    // initialize
    this->initIndices(motions, nMotions);
    
    Map *map;                  // ErrorMap

    map = new Map(nMotions);
    map->setThreshold(threshold);
    map->setNSteps(nCoincidents);
    map->constructMap(motions, nMotions); // also export each map file.
    
    for(int i=0 ; i<map->getNRelations(); i++){
        std::string label1 = map->getRelations(i, 0);
        std::string label2 = map->getRelations(i, 1);
        
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
            nRelations = map->calcMinimums(i, minFrame1, minFrame2);
            
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
                                        j, map->getNSteps(),
                                        motions.at(index1).getNFrames(), motions.at(index2).getNFrames() );
                
            }
        }
    }
}

void Graph::loadGraph(const std::string& filename)
{
    cout << "Load Graph : " << filename << endl;
    
    ofFile file;
    std::string label = file.getAbsolutePath() + "/" + filename;
    
    std::ifstream inFile;
    inFile.open(label, std::ios_base::in);
    if(!inFile)
        return false;
    
    const int MAX_LINE_CHAR = 512;
    char szLine[MAX_LINE_CHAR] = "";
    char szLineTokens[MAX_LINE_CHAR] = "";
    
    inFile.getline(szLine, MAX_LINE_CHAR); //line of file type
    if( 0 != strcmp(szLine,"# Graph Version 0.1") ) //check the file type
    {
        printf("Graph file should begin with \"# Graph Version 0.1\"  \n");
        return false;
    }
    
    // loop process the file body
    while( true )
    {
        inFile.getline(szLine, MAX_LINE_CHAR);
        
        if( 0 == strlen(szLine) ) // end of file
            break;
        
        strcpy(szLineTokens, szLine);
        
        // split the line to tokens
        std::vector<char *> tokens;
        const char* szDelimit = " ,=:\"{}\t";
        char *token = strtok(szLineTokens, szDelimit);
        
        while(token)
        {
            tokens.push_back(token);
            token = strtok(NULL, szDelimit);
        }
        
        if( 0 == tokens.size() )
            continue;
        if( tokens[0][0] == '#') // comment line
            continue;
        
        if( 0 == strcmp("MotionNum", tokens[0]) )
        {
            int MotionNum = std::atoi(tokens[1]);
            cout << "MotionNum " << MotionNum << endl;
        }
        else if( 0 == strcmp("MotionPath", tokens[0]) )
        {
            string MotionPath = tokens[1];
            cout << "MotionPath " << MotionPath << endl;
        }
        else if( 0 == strcmp("MotionName", tokens[0]) )
        {
            string motionName = tokens[1];
            cout << "MotionName " << motionName << endl;
            if( 0 == strcmp("frame", tokens[2]) )
            {
                int frame = std::atoi(tokens[3]);
                cout << "frame " << frame << endl;
                int index;
                if( index > -1 ){
                    Node *n;
                    n->setMotionLabel(motionName);
                    n->setFrameID(frame);
                    this->mNodes.push_back(n);
                }
            }
            if( 0 == strcmp("NumEdges", tokens[4]) )
            {
                int NumEdges = std::atoi(tokens[5]);
                cout << "NumEdges " << NumEdges << endl;
            }
        }
        else if( 0 == strcmp("TargetLabel", tokens[0]) )
        {
            Node *n;
            Edge *e;
            e = new Edge(this->mNodes.back());

            string TargetLabel = tokens[1];
            n->setMotionLabel(TargetLabel);
            cout << "   TargetLabel " << TargetLabel << endl;
            if( 0 == strcmp("frame", tokens[2]) )
            {
                int frame = std::atoi(tokens[3]);
                cout << "   frame " << frame << endl;
                n->setFrameID(frame);
                e->setDestination(n);
            }
        }
    }
}

void Graph::exportGraphFile(const string& filename, const std::vector<Motion>& motion)
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
    int motionNum = motion.size();
    
    ofs << "MotionNum " << motionNum << endl;
    
    for(int i=0; i<motionNum; i++) {
        ofs << "MotionPath " << motion[i].getFilePath() << " frameNum " << motion[i].getNFrames() << std::endl;
    }

    for(int i=0; i<this->getNumNodes(); i++) {
        ofs << "MotionName " << this->getNode(i)->getMotionLabel() << " ";
        ofs << "frame " << this->getNode(i)->getFrameID() << " "; 
        ofs << "NumEdges " << this->getNode(i)->getNumEdges() << endl;
    }
    
    for(int i=0; i<this->getNumNodes(); i++) {
        ofs << this->getNode(i)->getNodeID() << " " << this->getNode(i)->getNumEdges() << " ";
        for(int j=0; j<this->getNode(i)->getNumEdges(); j++) {
            ofs << this->getNode(i)->getEdge(j)->getDestination()->getNodeID() << " ";
        }
        ofs << endl;
    }

//    for(int i=0; i<this->getNumNodes(); i++) {
//        if(this->getNode(i)->getNumEdges() > 0) {
//            ofs << "MotionName " << this->getNode(i)->getMotionLabel() << " ";
//            ofs << "frame " << this->getNode(i)->getFrameID() << " ";
//            ofs << "NumEdges " << this->getNode(i)->getNumEdges() << endl;;
//            
//            for(int j=0; j<this->getNode(i)->getNumEdges(); j++) {
//                ofs << "    TargetLabel " << this->getNode(i)->getEdge(j)->getDestination()->getMotionLabel() << " ";
//                ofs << "frame " << this->getNode(i)->getEdge(j)->getDestination()->getFrameID() << endl;;
//            }
//        }
//    }
    ofs.close();
}

void Graph::draw(const float& wScale, const float& hScale)
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

const int Graph::addNode(Node *node)
{
    node->setNodeID(this->mNNodes);
    this->mNodes.push_back(node);
    this->mNNodes++;
    return node->getNodeID();
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
                        Edge *e = new Edge(this->mNodes[i]->getEdge(j)->getDestination());
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

void Graph::initIndices(const std::vector<Motion>& motions, const int nMotions)
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
        Edge *e = new Edge(n2);
        
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

/*
        e1					   e3	   e4
 1-------------->2			1----->5------->2
                    ---->		    \ e7
                                     \
 3-------------->4			3-------->6---->4
        e2						e5		e6
 */
void Graph::createTransitions(std::string& m1, const int node1, const int frame1, const int motionID1,
                              std::string& m2, const int node2, const int frame2, const int motionID2,
                              const int transiction, const int range, const int totalFrames1, const int totalFrames2)
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
        this->getNode(node1)->addEdge(new Edge(this->getNode(node2)));
    }
}
