//
//  main.cpp
//  Maximun Flow
//
//  Created by Enzo Ames on 4/13/16.
//  Copyright © 2016 Enzo Ames. All rights reserved.
//

/*
Write code that finds a maximum flow in a directed graph, using the Ford-Fulkerson algorithm on capacities given as matrix
void maximum flow(int n, int s, int t, int *capacity, int *flow)
Your function has the following arguments:
- n: the number of vertices of the graph,
- s: the start vertex,
- t: the target vertex
- capacity: the matrix of edge capacities.
- flow: the matrix used to return the maximum flow.
The vertices are numbered from 0 to n-1, so s and t are numbers in that range. capacity, flow are a pointers to n×n matrices of nonnegtive integers; the array el- ement capacity[i][j] is the capacity of the edge from i to j, and can be accessed as *(capacity + i*n + j). Your function should return in the matrix flow the flow values of the maximum flow from s to t. The flow variable of your function points to space allocated for the flow matrix.
Your function will need at least the following auxiliary arrays:
- an n×n matrix to hold the current flow,
- an n×n matrix to hold the current residual capacities,
- an array to maintain which vertices are already visited in the search of an augmenting
path from s to t with positive residual capacity.
You have to allocate the auxiliary arrays. You can use either BFS or DFS for the search of the augmenting path.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool bfs(int n, int start, int end, int * residualG, int path[]);
void maximum_flow(int n, int s, int t, int *capacityMtrx, int *flowMtrx );
void addToQueue(int x);
int removeFromQueue();

//Global Variables
int head = 0; int tail = 0;
int queue[10000];



void maximum_flow(int n, int s, int t, int *capacityMtrx, int *flowMtrx )
{
    int residualGraph[n][n]; //to update the capacities as we go
    int path[n];
    int i, j;
    int u, v;

    //Residual_Capacity = Capacity
    //Initialyze Flow Matrix to zero
    for (i = 0 ; i < n ; i++ ) //rows
    {
        for (j = 0 ; j < n ; j++) //columns
        {
            residualGraph[i][j] = *(capacityMtrx + i*n + j);
            *(flowMtrx + i*n + j) = 0;
        }
    }

    //Agument the path from s to t
    while(bfs(n, s, t, &(residualGraph[0][0]), path)
    {



    }




}


//    int temp = 0;
//    while (!temp)
//    {
//        u = 0;
//        for (v = 0; v < n ; v++)
//        {
//            if( residualGraph[u][v] - flowMtrx[u][v] > 0 ) //if greater than 0 then there is a link.
//            {
//                addToQueue(v);
//            }
//        }
//
//
//
//    }
//
//  BFS(n,s,t);


bool bfs(int n, int start, int end, int *residualG, int path[])// n = number of vertices , start = 0 , end = 5
{
    int visitedVertex[n];
    int t, u;

    for (u = 0 ; u < n ; u++) //initialyze the visited vertices to zero
        visitedVertex[u] = 0; //false

    addToQueue(start);
    visitedVertex[start] = true;
    path[start] = -1;

    while(head!=tail)
    {
        t = removeFromQueue();

        for (u = 0; u < n ; u++)
        {
            if (*(residualG + t*n + u) > 0 && visitedVertex[u] == false )
            {
                addToQueue(u);
                visitedVertex[u] = true;
                path[u] = t;
            }
        }
    }

    if (visitedVertex[end] == true)
        return true;
    else
        return false;

}

void addToQueue(int x)
{
    queue[tail] = x;
    tail++;

}

int removeFromQueue()
{
    int s;
    s = queue[head];
    head ++;
    return s;
}



int main()
{
    int vertices = 6; int source = 0; int target = 5; //target = n - 1

    int capacityMatrx [6][6];
    int flowMatrx [6][6];
    int i, j;
    printf("Enter Capacity for matrix: \n");

    for (i = 0 ; i < vertices ; i++ ) //rows
    {
        for (j = 0 ; j < vertices ; j++) //columns
        {
            scanf("%d", &capacityMatrx[i][j]);
        }
    }


    maximum_flow(vertices, source, target, &(capacityMatrx[0][0]), &(flowMatrx[0][0]) );

    return 0;
}
