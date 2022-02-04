#include "BST.hpp"

BST::BST(){
    this->root = nullptr;
    this->maxPriorityNode = nullptr;
}

BST::~BST(){
    if(this->root != nullptr){
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
            bstNodes.pop();
            delete currNode;
        }

        this->root = nullptr;
        this->maxPriorityNode = nullptr;
    }

}

void BST::addAndCreateNodeFor(SearchGraphNode* searchGraphNode){
    BSTNode* newBSTNode = new BSTNode();
    newBSTNode->setNode(searchGraphNode);
    this->addNode(newBSTNode);
    
}

void BST::addNode(BSTNode* node){
    bool onlyWentToLeft = true;

    if(this->root == nullptr){
        //std::cout<<" Its the root node!";
        this->root = node;
    }else{
        //std::cout<<" Its NOT the root node!";
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
        //std::cout<<" Its the maxPriority one!";
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

    BSTNode* oldMaxPriority = this->maxPriorityNode;

    //If root node is the maxPriority one
    if(this->root->getNode()->getNodeId() == this->maxPriorityNode->getNode()->getNodeId()){
        //std::cout<<" A";
        
        //Updates Root node
        //As the root node was the maxPriority one, there is no nodes left to it
        this->root = this->root->getRightNode();
        if(this->root != nullptr){
            this->root->setParentNode(nullptr);
        }
        
        //Updates maxPriorityNode
        this->maxPriorityNode = this->findLeftMostFrom(this->root);
    
    //std::cout<<" B";
    
    }else{
        //Root node is not the maxPriority one
        //The maxPriority node doesnt have a left child
        //std::cout<<" C";
        
        if(this->maxPriorityNode->getRightNode() == nullptr){
            //MaxPriority Node doesn't have a right child
            //The new MaxPriority should be oldMaxPriority->parent
            //std::cout<<" D";
            //Updates maxPriorityNode
            this->maxPriorityNode = this->maxPriorityNode->getParentNode();
            //std::cout<<"NEW MAX: "<<this->maxPriorityNode->getNode()->getNodeId();

            //The oldMaxPriority is, for sure, the left child of its parent
            oldMaxPriority->getParentNode()->setLeftNode(nullptr);
        
        }else{
            //MaxPriority Node has a right child
            //The new MaxPriority should be leftmost(oldMaxPriority->rightChild)
            //std::cout<<" E";

            oldMaxPriority->getRightNode()->setParentNode(oldMaxPriority->getParentNode());
            oldMaxPriority->getParentNode()->setLeftNode(oldMaxPriority->getRightNode());

            //Updates the maxPriority node
            this->maxPriorityNode = this->findLeftMostFrom(oldMaxPriority->getRightNode());

        }

    }
    //std::cout<<" F";
    oldMaxPriority->setRightNode(nullptr);
    oldMaxPriority->setParentNode(nullptr);

    SearchGraphNode* nodeToReturn = oldMaxPriority->getNode();
    this->idsInBST.erase(nodeToReturn->getNodeId());

    delete oldMaxPriority;
    //std::cout<<" G";
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
    BSTNode* parentNode = updatedNode->getParentNode();
    BSTNode* leftChild = updatedNode->getLeftNode();
    BSTNode* rightChild = updatedNode->getRightNode();

    if(updatedNode->getNode()->getNodeId() == this->root->getNode()->getNodeId()){
        if (this->doesntHaveChildren(updatedNode)) {
            this->root = nullptr;
            this->maxPriorityNode = nullptr;
        }else if (leftChild == nullptr && rightChild != nullptr){
            this->root = rightChild;
            this->root->setParentNode(nullptr);
            //As the updatedNode doesn't have a left child and it is the root node,
            //it is the maxPriority Node. We have to update it
            this->maxPriorityNode = this->findLeftMostFrom(this->root);
            
        }else if(leftChild != nullptr && rightChild == nullptr){
            this->root = leftChild;
            this->root->setParentNode(nullptr);
            //As the node has a left child, it is not the maxPriority one and
            //thus we dont need to update the maxPriorityNode
        
        //Both children are set
        }else{
            //As the node has a left child, it is not the maxPriority one and
            //thus we dont need to update the maxPriorityNode
            BSTNode* leftMostR = this->findLeftMostFrom(rightChild);
            leftMostR->setLeftNode(leftChild);
            leftChild->setParentNode(leftMostR);
            
            this->root = rightChild;
            rightChild->setParentNode(nullptr);

        }
    //If it is not the root node
    }else{
        if(this->doesntHaveChildren(updatedNode)){
            updatedNode->updateMyPlaceAsChildWith(nullptr);

            if(this->maxPriorityNode->getNode()->getNodeId() == updatedNode->getNode()->getNodeId()){
                this->maxPriorityNode = updatedNode->getParentNode();
            }

        }else if(leftChild == nullptr && rightChild != nullptr){
            updatedNode->updateMyPlaceAsChildWith(rightChild);
            rightChild->setParentNode(parentNode);

            //UpdatedNode could be the maxPriorityNode and yet have a rightChild
            if(this->maxPriorityNode->getNode()->getNodeId() == updatedNode->getNode()->getNodeId()){
                this->maxPriorityNode = this->findLeftMostFrom(rightChild);
            }

        }else if(leftChild != nullptr && rightChild == nullptr){
            updatedNode->updateMyPlaceAsChildWith(leftChild);
            leftChild->setParentNode(parentNode);

        }else if (leftChild != nullptr && rightChild != nullptr){

            rightChild->setParentNode(parentNode);
            updatedNode->updateMyPlaceAsChildWith(rightChild);

            BSTNode* leftMostR = this->findLeftMostFrom(rightChild);
            leftMostR->setLeftNode(leftChild);
            leftChild->setParentNode(leftMostR);

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

void BST::printBST(){
    unsigned int level = 0;

    std::cout<<"--Printing BST!--\n";
    std::queue<BSTNode> levelNodes;

    levelNodes.push(*(this->root));
    while(!levelNodes.empty()){
        std::cout<<"Level: "<<level<<"\n";
        std::queue<BSTNode> nextLevelNodes;

        while(!levelNodes.empty()){
            BSTNode currNode = levelNodes.front();
            std::cout<<"Node: "<<currNode.getNode()->getNodeId();
            if(currNode.getParentNode() == nullptr){
                std::cout<<" Parent: NULL";
            }else{
                std::cout<<" Parent: "<<currNode.getParentNode()->getNode()->getNodeId();
            }
            
            std::cout<<" Total Cost: "<<currNode.getTotalCost();

            bool leafNode = true;

            if(currNode.getRightNode() != nullptr){
                nextLevelNodes.push(*(currNode.getRightNode()));
                leafNode = false;
            }

            if(currNode.getLeftNode() != nullptr){
                nextLevelNodes.push(*(currNode.getLeftNode()));
                leafNode = false;
            }

            if(leafNode){
                std::cout<<" LEAF NODE!";
            }

            if(this->maxPriorityNode->getNode()->getNodeId() == currNode.getNode()->getNodeId()){
                std::cout<<" ITS MAXPRIORITY!";
            }
            std::cout<<std::endl;

            
            levelNodes.pop();

        }

        level++;
        levelNodes = nextLevelNodes;
    }
}