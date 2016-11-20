//
//  Header.hpp
//  Heuristic Search Algorithms
//
//  Created by Enzo Ames on 7/13/16.
//  Copyright © 2016 Enzo Ames. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>

//******************************************************************************************
//************************************ CLASS NODE ******************************************
//******************************************************************************************

class Node
{
    friend class Tree;
    
    public:
    
        Node(int distance = NULL, int eRDistance = NULL, char label = ' ', Node * left = nullptr, Node * right = nullptr);
    
        void setLeft(Node * left){this->left = left;};
        void setRight(Node * right){ this->right = right;};
    
        Node * getLeft(){ return this->left;};
        Node * getRight() { return this->right;};
    
        int getDistance() const{ return this->distance;};
        int getERDistance() const{ return this->eRDistance;};
        char getLabel(){return this->label;};
    
    private:
        int distance;
        int eRDistance;
        char label;
    
        Node * left;
        Node * right;
};

//******************************************************************************************
//**************************** OVERLOAD THE COMPARISON OPERATOR ****************************
//******************************************************************************************

//Overloading the comparison operator for the Priority Queue for DISTANCE
struct CompDistance
{
    bool operator()(const Node* a, const Node* b)
    {
        return a->getDistance() < b->getDistance();
    }
};

////Overloading the comparison operator for the Priority Queue for ESTIMATE OF REMAINING DISTANCE
//struct CompERDistance_descending
//{
//    bool operator()(const Node* a, const Node* b)
//    {
//        return a->getERDistance() < b->getERDistance();
//    }
//};

//Overloading the comparison operator for the Priority Queue for ESTIMATE OF REMAINING DISTANCE (in ascending order)
struct CompERDistance_ascending
{
    bool operator()(const Node* a, const Node* b)
    {
        return a->getERDistance() > b->getERDistance();
    }
};

//Overloading the comparison operator for the Priority Queue for ESTIMATE OF REMAINING DISTANCE AND DISTANCE (ascending order)
// f(x) = g(x) + h(x) where g is the distance and h is the ERdistance
struct CompERD_and_Distance
{
    bool operator()(const Node* a, const Node* b)
    {
        return (a->getDistance() + a->getERDistance()) > (b->getDistance() + b->getERDistance());
    }
};

//******************************************************************************************
//************************************ CLASS TREE ******************************************
//******************************************************************************************

class Tree
{
    public:
        Tree() { this->head = nullptr;};
    
        //Builds the Maze
        void buildMaze();
    
        //Shows tree on Console
        void treeWalk(Node * t);
    
        //getter for the head node
        Node * getHeadPtr(){ return this->head;}
    
        //BFS Function
        void BFSd (Node * root);
        //void BFSerd (Node * root);
        void BFSerd_ascending (Node * root);
        void BFSa_star (Node * root);
    
    
        //Functions to clear priority queues
        void qNodesClearD() { while(!qNodes.empty()) qNodes.pop();}
        //void qNodesClearERD() { while(!qNodes2.empty()) qNodes2.pop();}
        void qNodesClearERD_Ascending() { while(!qNodes3.empty()) qNodes3.pop();}
    
        //All Search Algorithms
        char hillClimbing(Node * root);
        char beamSearch(Node * root, int width);
        void bestFirstSearch(Node * root, int goal);
        void BnB(Node * root, int goal);
        void BnBwithU(Node * root, int goal);
        void BnBwithDP(Node * root, int goal);
        void A_starSearch(Node * root, int goal);
    
    private:
        Node * head;
        std::priority_queue < Node*, std::vector<Node*>, CompDistance> qNodes;
        //std::priority_queue < Node*, std::vector<Node*>, CompERDistance_descending> qNodes2;
        std::priority_queue < Node*, std::vector<Node*>, CompERDistance_ascending> qNodes2;
        std::priority_queue < Node*, std::vector<Node*>, CompERD_and_Distance> qNodes3;

};



#endif /* Header_h */








