#ifndef __BST_H__
#define __BST_H__
#include "BSTNode.hpp"
#include "SearchGraphNode.hpp"

#include <iostream>
#include <iterator>
#include <unordered_map>
#include <queue>

class BST{
    private:
        BSTNode* root;
        BSTNode* maxPriorityNode;
        std::unordered_map<unsigned int, BSTNode*> idsInBST;
        BSTNode* findLeftMostFrom(BSTNode* rootNode);
        BSTNode* findRightMostFrom(BSTNode* rootNode);
        void addNode(BSTNode* node);
        bool doesntHaveChildren(BSTNode* node);
        bool isMaximumPriority(BSTNode* node);
        bool isRoot(BSTNode* node);
    public:
        void addAndCreateNodeFor(SearchGraphNode* searchGraphNode);
        SearchGraphNode* popMaxPriorityNode();
        double peekMaxPriority();
        bool hasNode(unsigned int nodeId);
        BSTNode* findNode(unsigned int nodeId);
        void updateNode(BSTNode* updatedNode);
        bool empty();
        void printBST();
        BST();
        ~BST();
};

#endif