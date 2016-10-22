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
    this->mGraph->loadGraph(filename);
}

void MotionGraph::exportGraph(const std::string& filename)
{
    std::vector<std::string> motion_filepaths;
    for(int i=0; i<this->mMotions.size(); i++){
        motion_filepaths.push_back(this->mMotions.at(i).getFilePath());
    }
    this->mGraph->exportGraphFile(filename, this->mMotions);
}

Graph *MotionGraph::prune()
{

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


