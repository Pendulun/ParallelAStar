#ifndef __BSTNODE_H__
#define __BSTNODE_H__

#include "SearchGraphNode.hpp"

class BSTNode{
    private:
        SearchGraphNode* node;
        BSTNode* leftNode;
        BSTNode* rightNode;
        BSTNode* parentNode;
    public:
        BSTNode();
        ~BSTNode();
        void setNode(SearchGraphNode* node);
        void setParentNode(BSTNode* parentNode);
        void setLeftNode(BSTNode* leftNode);
        void setRightNode(BSTNode* rightNode);
        SearchGraphNode* getNode();
        BSTNode* getLeftNode();
        BSTNode* getParentNode();
        BSTNode* getRightNode();
        float getTotalCost();
        void updateMyPlaceAsChildWith(BSTNode* newNode);
};

#endif