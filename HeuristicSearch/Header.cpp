//
//  Header.cpp
//  Heuristic Search Algorithms
//
//  Created by Enzo Ames on 7/13/16.
//  Copyright © 2016 Enzo Ames. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include "Header.h"
using namespace std;


//******************************************************************************************
//************************************ NODE CONSTRUCT **************************************
//******************************************************************************************

Node::Node(int distance, int eRDistance, char label, Node * left, Node * right)
{
    this->distance  = distance;
    this->eRDistance = eRDistance;
    this->label = label;
    this->left = left;
    this->right = right;
}


//******************************************************************************************
//******************************* BUILD MAZE FUNCTION **************************************
//******************************************************************************************

void Tree::buildMaze()
{
    //The following two arrays are the distances, estimate of remaining distance, and the labels for each node in the graph (maze)
    char labels [] = {   'S', 'A', 'B', 'C', 'D', 'F', 'E', 'G', 'H', 'I', 'J', 'K', 'M'};
    int distance [] = {   0,  12,  98,   32,  24,  34,  40,  65,  47,  53,  55,  87,  100};
    int erDistance [] = { 100, 88, 198, 108,  76,  86,  60,  85,  53,  59,  45,  77,   0};
    
    //the start node has a distance of 0, estimate of remaining distance of 100, and a label 'S'
    //the goal node has a distance of 100, estimate of remaining distance of 0, and a label 'M'
    
    Node * firstNode = new Node(distance[0], erDistance[0], labels[0]); //start node S
    this->head = firstNode;
    
    Node * newNodeLeft = new Node(distance[1], erDistance[1], labels[1]);
    Node * newNodeRight = new Node(distance[2], erDistance[2],labels[2]);
    
    this->head->setLeft(newNodeLeft);
    this->head->setRight(newNodeRight);
    
    
    Node * current = this->head->getLeft();
    
    for (int i = 3 ; i < 12; i+=2)
    {
        Node * newNodeLeft = new Node(distance[i], erDistance[i], labels[i]);
        
        current->setLeft(newNodeLeft);
        
        Node * newNodeRight = new Node(distance[i+1], erDistance[i+1], labels[i+1]);
        
        current->setRight(newNodeRight);
        
        if (current->getLeft()->getERDistance() > current->getRight()->getERDistance())
            current = current->getRight();
        else
            current = current->getLeft();
    }
    
}

//******************************************************************************************
//*************************** BREADTH FIRST SEARCH FUNCTIONS *******************************
//******************************************************************************************

//BREADTH FIRST SEARCH, uses priority queue sorted based on distance

void Tree::BFSd (Node * root)
{
    //qNodes.push(root);
    
    if (root->getLeft())
        qNodes.push(root->getLeft());
    
    if (root->getRight())
        qNodes.push(root->getRight());
}


//BREADTH FIRST SEARCH, uses priority queue sorted based on estimate of remaining distance (in ascending order)

void Tree::BFSerd_ascending (Node * root)
{
    //qNodes2.push(root);
    
    if (root->getLeft())
        qNodes2.push(root->getLeft());
    
    if (root->getRight())
        qNodes2.push(root->getRight());
}


//BREADTH FIRST SEARCH, uses priority queue sorted based on estimate of remaining distance + distance (in ascending order)
// f(x) = g(x) + h(x) where g is the distance and h is the ERdistance

void Tree::BFSa_star (Node * root)
{
    //qNodes3.push(root);
    
    if (root->getLeft())
        qNodes3.push(root->getLeft());
    
    if (root->getRight())
        qNodes3.push(root->getRight());
}


//******************************************************************************************
//**************** THE FOLLOWING FUNCTIONS ARE ALL THE SEARCH ALGORITHMS *******************
//******************************************************************************************


//Hill Climbing. takes the shortest remaining path. USE HEURISTIC ESTIMATES. ESTIMATES OF REMAINING DISTANCE

char Tree::hillClimbing(Node * root)
{
    Node * current = root;
    Node * leftChild = current->getLeft();
    Node * rightChild = current->getRight();
    
    while (leftChild!=nullptr && rightChild!=nullptr) //Hill Climbing will traverse through the tree finding a path to
    {                                                  //the goal. The optimal path to the goal is not guarantee
        if ( leftChild->getERDistance() < rightChild->getERDistance())
        {
            current = leftChild;
            leftChild = current->getLeft();
            rightChild = current->getRight();
        }
        else
        {
            current = rightChild;
            leftChild = current->getLeft();
            rightChild = current->getRight();
        }
    }
    
    return current->getLabel();
}


//Beam Search. USE HEURISTIC ESTIMATES. ESTIMATES OF REMAINING DISTANCE

char Tree::beamSearch(Node * root, int width)
{
    if (!root)
        return 0;
    
    Node * temp = root;
    
    Node * topNodes [width]; //array of node pointers to hold the top two paths
    
    Node * currentMax;
    
    BFSerd_ascending(temp); // BFS function to insert the children of the root node to start off
    
    int j = 0;

    while (temp->getDistance() != 100) // 100 is our "goal distance"
    {
        int i = 0;
        while(i < width) // In this while loop we insert the best two nodes in arrayNodes []
        {
            currentMax = qNodes2.top();
            qNodes2.pop();
            topNodes[i] = currentMax;
            i++;
        }
        
        for(j = 0 ; j < width; j++) // Once we have the best two nodes, we check if those two nodes have children
        {                           // if they do, then we call BFS funcion on each node.
            if (topNodes[j]->getLeft()!=nullptr && topNodes[j]->getRight()!=nullptr) // This if statement determines
            {                                                                        // if there is a path.
                BFSerd_ascending(topNodes[j]);
                temp = topNodes[j];
            }
            if (topNodes[j]->getDistance() == 100)
            {
                qNodesClearERD_Ascending();
                return topNodes[j]->getLabel();
            }
        }
        
    }

    return temp->getLabel();
}

void Tree::bestFirstSearch(Node * root, int goal)
{
    if (!root)
        return;
    
    Node * temp = root;
    
    Node * ClosedList[20] ; // The Closed list of best nodes;
    
    BFSerd_ascending(temp); // BFS function inserts the children of the root node to start off;
    // Inserts into qNodes2 to give nodes with estimated remaining distance.
    ClosedList[0] = root; // initialized Closedlist [0] to 0 because that is our start state
    
    int i = 1;
    
    while(!qNodes2.empty())
    {
        Node * CurrentBest = qNodes2.top();
        Node * leftChild = CurrentBest->getLeft();
        Node * rightChild = CurrentBest->getRight();
        
        qNodes2.pop();
        
        if(CurrentBest->getDistance() == goal)
        {
            ClosedList[i] = CurrentBest;
            for(int i = 0; i < 7; i++)
                cout<< ClosedList[i]->getLabel() << " ";
            
            qNodesClearERD_Ascending();
        }
        
        if(leftChild==nullptr && rightChild==nullptr)
        {
            ClosedList[i] = qNodes2.top();
            BFSerd_ascending(qNodes2.top());
            CurrentBest = qNodes2.top();
        }
        ClosedList[i] = CurrentBest;
        BFSerd_ascending(CurrentBest);
        i++;
    }
}

void Tree::BnB(Node * root, int goal)
{
    Node * temp = root;

    BFSd(temp); //Call BFS function on the root node
    
    char path [7]; // this array holds the path to the goal, to be printed on the console
    path[0]= 'S'; //We can initalize the first index to 'S' since we know that is our start state
    Node * current = nullptr;
    
    int i = 1;
    while(!qNodes.empty())
    {
        current  = qNodes.top();
        qNodes.pop();
        
        if (current->getDistance() == goal) //Loop to check if we are at the goal state
        {
            path[i] = current->getLabel();
            for(int j = 0 ; j < 7 ; j++) //Loop to show the path back, from the start state to the goal state
                cout << path[j] << " " ;
            qNodesClearERD_Ascending(); //Clear the priority queue
        }
        else // else we insert the children of the node in queue
        {
            if(current->getLeft()!=nullptr && current->getRight()!=nullptr) //if statement to insert nodes which have children
            {
                path[i] = current->getLabel();
                BFSd(current);
                i++;
            }
        }
    }

}


void Tree::BnBwithU(Node * root, int goal)
{
    Node * temp = root;
    
    BFSerd_ascending(temp);
    char path [7];
    path[0] = 'S';
    Node * current = nullptr;
    
    int i = 1;
    
    while (!qNodes2.empty())
    {
        current = qNodes2.top();
        qNodes2.pop();
        
        if (current->getDistance() == goal)
        {
            path[i] = current->getLabel();
            for(int j = 0 ; j < 7 ; j++) //Loop to show the path back, from the start state to the goal state
                cout << path[j] << " " ;
            qNodesClearERD_Ascending();
        }
        else
        {
            if(current->getLeft()!=nullptr && current->getRight()!=nullptr)
            {
                path[i] = current->getLabel();
                BFSerd_ascending(current);
                i++;
            }
        }
    }

}


void Tree::BnBwithDP(Node * root, int goal)
{
    Node * temp = root;
    
    qNodes.push(temp); //push the root to the priority queue
    
    char path [7]; //this array holds the path to the goal, to be printed on the console
    //path[0] = 'S';
    
    Node * current = nullptr;
    
    vector<Node *> visited; //list to hold the visited nodes

    Node * left = nullptr;
    Node * right =  nullptr;
    
    int i = 0;
    int count = 0;
    
    while(!qNodes.empty())
    {
        current = qNodes.top(); //current is now the top of queue
        qNodes.pop(); //pop first element of queue
        visited.push_back(current); //push "current" to the vector of visited nodes
        
        //cout << "current: " << current->getLabel() << endl;
        
        if(current->getLeft() && current->getRight())
            path[i++] = current->getLabel(); //record the path

        
        if (current->getDistance() == goal)
        {
            path[i] = current->getLabel();
            for(int j = 0 ; j < 7 ; j++) //Loop to show the path back, from the start state to the goal state
                cout << path[j] << " " ;
            qNodesClearD(); //Clear the priority queue
        }
        
        //Now we need to determine whether the children of "current" are in the visited list
        left =  current->getLeft();
        right =  current->getRight();
        
        for(vector<Node*>::iterator it = visited.begin(); it != visited.end(); it++) //If left & right aren't in the visited list
        {   //cout << "visited list: " << (*it)->getLabel()<< endl;                 //push those nodes into the queue
            if(left!=nullptr && (*it)->getLabel()!=left->getLabel())       //Also make sure left and right doesn't equal to null
            {
                count++;
            }
            if(right!=nullptr && (*it)->getLabel()!= right->getLabel())
            {
                count++;
            }
            if(count == visited.size()*2)
            {
                //cout << "count: " << count << "  " << "visited size: " << visited.size()*2 <<  endl;
                //cout << "calling BFS <<  endl;"
                BFSd(current);
            }
        }
        count = 0;
    }
    
}

void Tree::A_starSearch(Node * root, int goal)
{
    Node * temp = root;
    
    char path [7]; //this array holds the path to the goal, to be printed on the console //path[0] = 'S';
    path[0] = 'S';
    
    Node * current = nullptr;
    Node * left = nullptr;
    Node * right =  nullptr;
    
    int i = 0;
    int count = 0;
    
    qNodes3.push(temp); //push the root to the priority queue
    vector<Node *> visited;
    
    while (!qNodes3.empty())
    {
        current = qNodes3.top(); //current is now the top of queue
        qNodes3.pop(); //pop first element of queue
        visited.push_back(current); //push "current" to the vector of visited nodes
        
        left =  current->getLeft();
        right =  current->getRight();
        
        if(left && right)
            path[i++] = current->getLabel();
        
        if(current->getDistance() == goal)
        {
            path[i] = current->getLabel();
            
            for(int j = 0 ; j < 7 ; j++) // Prints Path to the goal state
                cout << path[j] << " " ;
            
            qNodesClearERD_Ascending();
        }
        
        else
        {
            for(vector<Node*>::iterator it = visited.begin(); it != visited.end(); it++)
            {
                if(left!=nullptr && (*it)->getLabel()!=left->getLabel())
                    count++;
                
                if(right!=nullptr && (*it)->getLabel()!= right->getLabel())
                    count++;
                
                if(count == visited.size()*2)
                    BFSa_star(current);
            }
            count = 0;
        }
    }
}






