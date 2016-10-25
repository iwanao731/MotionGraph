//
//  SMGNode.h
//  
//
//  Created by NAOYAIWAMOTO on 24/10/2016.
//
//

#ifndef ____SMGNode__
#define ____SMGNode__

#include <stdio.h>
#include <vector>
#include "Node.h"

class SMGNode
{
public:
    SMGNode();
    virtual ~SMGNode();
    
    bool hasParent();
    bool hasChildren();
    bool IsGhostNode();
    
    void addChild(SMGNode *childNode);

    void setNodeIndex(int index);
    void setMGNode(Euclid::Node *n);
    void setParent(SMGNode *parentNode);
    void setGhostNode(bool bValue);
    
    int getNodeIndex();
    int getNumChildren();
    SMGNode* getParent();
    SMGNode* getChild(int index);
    Euclid::Node* getMGNode();
    
private:
    bool mHasParent;
    bool mHasChild;
    bool mGhostNode;
    int mIndex;
    int mNumChildren;
    Euclid::Node *mNode;
    SMGNode *mParentNode;
    std::vector<SMGNode*> mChildren;
};

#endif /* defined(____SMGNode__) */
