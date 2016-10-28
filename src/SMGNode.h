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
    
    const bool hasParent() const;
    const bool hasChildren() const;
    const bool IsGhostNode() const;
    
    void addChild(SMGNode *childNode);

    void setNodeIndex(int index);
    void setMGNode(Euclid::Node *n);
    void setParent(SMGNode *parentNode);
    void setGhostNode(bool bValue);
    
    const int getNodeIndex() const;
    const int getNumChildren() const;
    SMGNode* getParent() const;
    SMGNode* getChild(int index) const;
    Euclid::Node* getMGNode() const;
    
private:
    bool mHasParent;
    bool mHasChild;
    bool mIsGhostNode;
    int mIndex;
    Euclid::Node *mNode;
    SMGNode *mParentNode;
    std::vector<SMGNode*> mChildren;
};

#endif /* defined(____SMGNode__) */
