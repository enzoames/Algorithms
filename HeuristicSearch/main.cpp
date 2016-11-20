//
//  main.cpp
//  Heuristic Search Algorithms
//
//  Created by Enzo Ames on 7/13/16.
//  Copyright © 2016 Enzo Ames. All rights reserved.
//

#include <iostream>
#include "Header.h"

using namespace std;


int main(int argc, const char * argv[])
{
    //Creating an instance of the class Tree
    Tree maze;
    
    //Calls the function that builds the maze in a tree format
    maze.buildMaze();
    
    //Calls The Hill Climbing function. getHeadPtr returns the root node of the maze (tree)
    cout << "Running Hill Climbing Algorithm \n";
    cout << maze.hillClimbing(maze.getHeadPtr()) <<  endl << endl;
    
    //Calls The Beam Search function, width = 2
    cout << "Running Beam Search Algorithm \n";
    cout << maze.beamSearch(maze.getHeadPtr(), 2) << endl << endl;

    //Calls The Best First Search function
    cout << "Running Best First Search Algorithm \n Returning the path, start state to goal state: \n";
    maze.bestFirstSearch(maze.getHeadPtr(), 100); cout << endl << endl;
    
    //Calls Branch and Bound
    cout << "Running Branch and Bound Algorithm \n Returning the path from start state to goal state: \n";
    maze.BnB(maze.getHeadPtr(), 100); cout << endl << endl;

    //Calls Branch and Bound with underestimates
    cout << "Running Branch and Bound with Underestimates \n Returning the path from start state to goal state: \n";
    maze.BnBwithU(maze.getHeadPtr(), 100); cout << endl << endl;
    
    //Calls Branch and Bound with Dynamic Programming
    cout << "Running Branch and Bound with Dynamic Programming \n Returning the path from start state to goal state: \n";
    maze.BnBwithDP(maze.getHeadPtr(), 100); cout << endl << endl;
    
    //Calls A* Search Algorithm
    cout << "Running A* Search Algorithm \n Returning the path from start state to goal state: \n";
    maze.A_starSearch(maze.getHeadPtr(), 100); cout << endl << endl;
    
    
    return 0;
    
}
