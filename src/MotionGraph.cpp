//
//  MotionGraph.cpp
//  
//
//  Created by NAOYAIWAMOTO on 09/10/2016.
//
//

#include "MotionGraph.h"

using namespace Euclid;

MotionGraph::MotionGraph()
{
    mAnimCount = 0;
    this->mGraph = new Graph();
}

MotionGraph::~MotionGraph()
{
    
}

void MotionGraph::addMotion(const Motion& motion)
{
    this->mMotions.push_back(motion);
    this->mAnimCount++;
}

void MotionGraph::constructGraph(const Threshold& threshold, const NCoincidents& nCoincidents)
{
    std::cout << "start construct graph" << std::endl;
    
    if(mAnimCount == 0) return;
        
    //this->mGraph = new Graph();
    this->mGraph->constructGraph(this->mMotions, this->mAnimCount, threshold.getValue(), nCoincidents.getValue());
    //this->mGraph = this->prune();

    std::cout << "end construct graph" << std::endl;
}

void MotionGraph::draw(const float& wScale, const float& hScale)
{
    this->mGraph->draw(wScale, hScale);
}

bool MotionGraph::loadGraph(const std::string& filename)
{
    // load graph file
    this->mGraph->loadGraph(filename);
}

bool MotionGraph::loadMotionList(const std::string& motionList)
{
    std::cout << "Load Motion List : " << motionList << std::endl;
    
    ofFile file;
    std::string path = file.getAbsolutePath() + "/" + motionList;
    
    std::ifstream inFile;
    inFile.open(path, std::ios_base::in);
    if(!inFile)
        return false;
    
    const int MAX_LINE_CHAR = 512;
    char szLine[MAX_LINE_CHAR] = "";
    inFile.getline(szLine, MAX_LINE_CHAR);

    // initialization for this->mMotion
    int numMotion = std::atoi(szLine);
    this->mMotions.resize(numMotion);

    for(int i=0; i<numMotion; i++){
        inFile.getline(szLine, MAX_LINE_CHAR);
        this->mMotions[i].setFilePath(szLine);
        //std::cout << "motion path: " << this->mMotions[i].getFilePath() << std::endl;
    }    
}

void MotionGraph::exportGraph(const std::string& filename)
{
    // export Motion information
    ofFile file;
    std::string path = file.getAbsolutePath() + "/" + filename;
    std::ofstream ofs(path + "_motionlist.txt");
    ofs << this->mMotions.size() << endl;
    for(int i=0; i<this->mMotions.size(); i++){
        ofs << this->mMotions.at(i).getFilePath() << std::endl;
    }
    ofs.close();
    
    // export Graph information
    this->mGraph->exportGraphFile(path+"_graph.txt", this->mMotions);
}

bool MotionGraph::isExistMotion(const int index) const
{
    if(index < this->mMotions.size())
        return true;
    else{
        cout << "out of order" << endl;
        return false;
    }
}

Motion *MotionGraph::getMotion(const int index)
{
    if(this->isExistMotion(index))
        return &this->mMotions.at(index);
    else
        return 0;
}

Graph *MotionGraph::getGraph() const
{
    return this->mGraph;
}

const int MotionGraph::getNumMotion() const
{
    return this->mMotions.size();
}


