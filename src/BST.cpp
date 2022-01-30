#include "BST.hpp"

BST::BST(){
    this->root = nullptr;
    this->maxPriorityNode = nullptr;
}

BST::~BST(){
    std::queue<BSTNode*> bstNodes;
    bstNodes.push(this->root);
    
    while(!bstNodes.empty()){
        BSTNode* currNode = bstNodes.front();

        if(currNode->getLeftNode() != nullptr){
            bstNodes.push(currNode->getLeftNode());
        }

        if(currNode->getRightNode() != nullptr){
            bstNodes.push(currNode->getRightNode());
        }

        currNode->setParentNode(nullptr);
        //Calls the currNode destructor
        bstNodes.pop();
    }

    this->root = nullptr;
    this->maxPriorityNode = nullptr;

}

void BST::addAndCreateNodeFor(SearchGraphNode* searchGraphNode){
    BSTNode* newBSTNode = new BSTNode();
    newBSTNode->setNode(searchGraphNode);
    this->addNode(newBSTNode);
    
}

void BST::addNode(BSTNode* node){
    bool onlyWentToLeft = true;

    if(this->root == nullptr){
        this->root = node;
    }else{
        BSTNode* currNode = this->root;

        while(true){
            //New node should be added at left of curr Node
            if(node->getNode()->getTotalCost() < currNode->getNode()->getTotalCost()){
                
                if(currNode->getLeftNode() == nullptr){
                    currNode->setLeftNode(node);
                    node->setParentNode(currNode);
                    break;
                }else{
                    currNode = currNode->getLeftNode();
                }

            //New node should be added at right of curr Node
            }else{
                onlyWentToLeft = false;
                 if(currNode->getRightNode() == nullptr){
                    currNode->setRightNode(node);
                    node->setParentNode(currNode);
                    break;
                }else{
                    currNode = currNode->getRightNode();
                }
            }
        }
    }

    if(onlyWentToLeft){
        this->maxPriorityNode = node;
    }

    this->idsInBST.insert(std::make_pair<>(node->getNode()->getNodeId(), node));

}

BSTNode* BST::findLeftMostFrom(BSTNode* rootNode){
    BSTNode* currNode = rootNode;

    while(currNode != nullptr && currNode->getLeftNode() != nullptr){
        currNode = currNode->getLeftNode();
    }

    return currNode;
}

BSTNode* BST::findRightMostFrom(BSTNode* rootNode){
    BSTNode* currNode = rootNode;

    while(currNode != nullptr && currNode->getRightNode() != nullptr){
        currNode = currNode->getRightNode();
    }

    return currNode;
}

SearchGraphNode* BST::popMaxPriorityNode(){

    if(this->maxPriorityNode == nullptr){
        return nullptr;
    }

    BSTNode* oldMaxPriority = nullptr;
    SearchGraphNode* nodeToReturn = nullptr;

    //If root node is the maxPriority one
    if(this->root == this->maxPriorityNode){
        std::cout<<" A";
        
        //Updates Root node
        //As the root node was the maxPriority one, there is no nodes left to it
        this->root = this->root->getRightNode();
        if(this->root != nullptr){
            this->root->setParentNode(nullptr);
        }
        
        //Updates maxPriorityNode
        oldMaxPriority = this->maxPriorityNode;
        this->maxPriorityNode = this->findLeftMostFrom(this->root);
    
    std::cout<<" B";
    
    }else{
        //Root node is not the maxPriority one
        //The maxPriority node doesnt have a left child
        std::cout<<" C";
        //MaxPriority Node doesn't have a right child
        if(this->maxPriorityNode->getRightNode() == nullptr){
            std::cout<<" D";
            //Updates maxPriorityNode
            oldMaxPriority = this->maxPriorityNode;
            this->maxPriorityNode = this->maxPriorityNode->getParentNode();
        
        //MaxPriority Node has a right child
        }else{
            std::cout<<" E";
            oldMaxPriority = this->maxPriorityNode;

            //Updates the maxPriority node
            //this->maxPriorityNode = this->findLeftMostFrom(this->maxPriorityNode->getRightNode());
            this->maxPriorityNode = this->maxPriorityNode->getParentNode();

            //Updates left child of oldMaxPriority parent node 
            this->maxPriorityNode->setLeftNode(oldMaxPriority->getRightNode());
        }
    }
    std::cout<<" F";
    nodeToReturn = oldMaxPriority->getNode();
    this->idsInBST.erase(nodeToReturn->getNodeId());

    delete oldMaxPriority;
    std::cout<<" G";
    return nodeToReturn;
}

bool BST::hasNode(const unsigned int nodeId){
    std::unordered_map<unsigned int, BSTNode*>::iterator got = this->idsInBST.find(nodeId);
    return got != this->idsInBST.end();
}

BSTNode* BST::findNode(const unsigned int nodeId){
    if(this->idsInBST.empty()){
        return nullptr;
    }

    std::unordered_map<unsigned int, BSTNode*>::iterator got = this->idsInBST.find(nodeId);
    if(got != this->idsInBST.end()){
        return got->second;
    }else{
        return nullptr;
    }
}

bool BST::empty(){
    return this->idsInBST.empty();
}

void BST::updateNode(BSTNode* updatedNode){
    //Assumes that we are not updating the maxPriorityNode
    BSTNode* parentNode = updatedNode->getParentNode();
    BSTNode* leftChild = updatedNode->getLeftNode();
    BSTNode* rightChild = updatedNode->getRightNode();

    if(updatedNode == this->root){
        if (this->doesntHaveChildren(updatedNode)) {
            this->root = nullptr;
            this->maxPriorityNode = nullptr;
        }else if (leftChild == nullptr && rightChild != nullptr){
            this->root = rightChild;
            rightChild->setParentNode(nullptr);
            //As the updatedNode doesn't have a left child and it is the root node,
            //it is the maxPriority Node. We have to update it
            this->maxPriorityNode = this->findLeftMostFrom(this->root);
            
        }else if(leftChild != nullptr && rightChild == nullptr){
            this->root = leftChild;
            leftChild->setParentNode(nullptr);
            //As the node has a left child, it is not the maxPriority one and
            //thus we dont need to update the maxPriorityNode
        
        //Both children are set
        }else{
            //As the node has a left child, it is not the maxPriority one and
            //thus we dont need to update the maxPriorityNode
            BSTNode* leftMostNode = this->findLeftMostFrom(rightChild);
            leftChild->setParentNode(leftMostNode);
            leftMostNode->setLeftNode(leftChild);
            
            this->root = rightChild;
            rightChild->setParentNode(nullptr);

        }
    //If it is not the root node
    }else{
        if(this->doesntHaveChildren(updatedNode)){
            updatedNode->updateMyPlaceAsChildWith(nullptr);

        }else if(leftChild == nullptr && rightChild != nullptr){
            updatedNode->updateMyPlaceAsChildWith(rightChild);
            rightChild->setParentNode(parentNode);

        }else if(leftChild != nullptr && rightChild == nullptr){
            updatedNode->updateMyPlaceAsChildWith(leftChild);
            leftChild->setParentNode(parentNode);

        }else if (leftChild != nullptr && rightChild != nullptr){

            BSTNode* rightMost = this->findRightMostFrom(leftChild);
            rightChild->setParentNode(rightMost);
            rightMost->setRightNode(rightChild);

            updatedNode->updateMyPlaceAsChildWith(leftChild);
            leftChild->setParentNode(parentNode);

        }
    }

    updatedNode->setLeftNode(nullptr);
    updatedNode->setRightNode(nullptr);
    updatedNode->setParentNode(nullptr);
    this->idsInBST.erase(updatedNode->getNode()->getNodeId());

    this->addNode(updatedNode);
}

bool BST::doesntHaveChildren(BSTNode* node){
    return node->getLeftNode() == nullptr && node->getRightNode() == nullptr;
}