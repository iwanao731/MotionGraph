//
//  MotionGraph.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "MotionGraph.h"

MotionGraph::MotionGraph()
{
    mAnimCount = 0;
}

MotionGraph::~MotionGraph()
{
    
}

void MotionGraph::addMotion(const Motion& motion)
{
    this->mMotions.push_back(motion);
    this->mAnimCount++;
}

void MotionGraph::constructGraph(Threshold threshold, NCoincidents nCoincidents)
{
    std::cout << "start construct graph" << std::endl;
    
    if(mAnimCount == 0) return;
        
    this->mGraph = new Graph();
    this->mGraph->constructGraph(this->mMotions, this->mAnimCount, threshold.getValue(), nCoincidents.getValue());
    //this->mGraph = this->prune();

    std::cout << "end construct graph" << std::endl;
}

void MotionGraph::draw(const float& wScale, const float& hScale)
{
    this->mGraph->draw(wScale, hScale);
}

bool MotionGraph::LoadGraph(const std::string& filename)
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
            }
            if( 0 == strcmp("NumEdges", tokens[4]) )
            {
                int NumEdges = std::atoi(tokens[5]);
                cout << "NumEdges " << NumEdges << endl;
            }
        }
        else if( 0 == strcmp("TargetLabel", tokens[0]) )
        {
            string TargetLabel = tokens[1];
            cout << "   TargetLabel " << TargetLabel << endl;
            if( 0 == strcmp("frame", tokens[2]) )
            {
                int frame = std::atoi(tokens[3]);
                cout << "   frame " << frame << endl;
            }
        }
    }
}

void MotionGraph::exportGraph(const std::string& filename)
{
    std::vector<std::string> motion_filepaths;
    for(int i=0; i<this->mMotions.size(); i++){
        motion_filepaths.push_back(this->mMotions.at(i).getFilePath());
    }
    this->mGraph->exportGraphFile(filename, motion_filepaths);
}

Graph *MotionGraph::prune()
{
    int numNode = this->mGraph->getNumNodes();
    for(int i=0; i<numNode; i++) {
        this->mGraph->getNode(i)->getMotionLabel();
        this->mGraph->getNode(i)->getFrameID();
        int numEdges = this->mGraph->getNode(i)->getNumEdges();
        for(int j=0; j<numEdges; j++) {
            Node *nextNode = this->mGraph->getNode(i)->getEdge(j)->getDestination();
        }
    }
}

bool MotionGraph::isExistMotion(const int& index)
{
    if(index < this->mMotions.size())
        return true;
    else{
        cout << "out of order" << endl;
        return false;
    }
}

Motion *MotionGraph::getMotion(const int& index)
{
    if(this->isExistMotion(index))
        return &this->mMotions.at(index);
    else
        return 0;
}

const int MotionGraph::getNumMotion() const
{
    return this->mMotions.size();
}


