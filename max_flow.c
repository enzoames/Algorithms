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

// EDWARDS AMES CSC 220

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool bfs(int n, int start, int end, int * residualG, int path[]);
void maximum_flow(int n, int s, int t, int *capacityMtrx, int *flowMtrx );
int findMin(int a, int b);
void addToQueue(int x);
int removeFromQueue();

//Global Variables
int head = 0; int tail = 0;
int queue[100000];
int cap[1000][1000], flow[1000][1000];
//

void maximum_flow(int n, int s, int t, int *capacityMtrx, int *flowMtrx )
{
    int residualGraph[n][n]; //to update the capacities as we go
    int path[n];
    int i, j;
    int bottleNeck = INT_MAX;

    //int maxflow = 0; for testing purposes

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
    while( bfs(n, s, t, &(residualGraph[0][0]), path) )
    {
        j = t;
        while (j!=s)
        {
            i = path[j];
            bottleNeck = findMin( bottleNeck , residualGraph[i][j] ); //Now that we know a path from s to t. Finds the min cap.
            j = path[j];
        }

        j = t;
        while (j!=s) //now increment the flow matrix with bottleneck
        {
            i = path[j];
            if ( *(capacityMtrx + i*n + j) > 0 )
                *(flowMtrx + i*n + j) += bottleNeck;
            else
                *(flowMtrx + i*n + j) -= bottleNeck;

            residualGraph[i][j] -= bottleNeck;
            residualGraph[j][i] += bottleNeck;

            j = path[j];
        }
        //maxflow += bottleNeck;
    }
}

bool bfs(int n, int start, int end, int *residualG, int path[])
{
    int visitedVertex[n];
    int t;
    int i, j;

    for (i = 0 ; i < n ; i++) //initialyze the visited vertices to zero
        visitedVertex[i] = 0; //false

    addToQueue(start);
    visitedVertex[start] = true;
    path[start] = -1;

    int count = 0;
    while(head!=tail)
    {
        t = removeFromQueue();

        for (j = 0; j < n ; j++)
        {
            if (*(residualG + t*n + j) > 0 && visitedVertex[j] == false )
            {
                addToQueue(j);
                visitedVertex[j] = true;
                path[j] = t;
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

int findMin(int a, int b)
{
    if ( a > b )
        return b;
    else
        return a;
}

int main(void)
{

    int i,j, flowsum;
    for(i=0; i< 1000; i++)
        for( j =0; j< 1000; j++ )
            cap[i][j] = 0;

    for(i=0; i<499; i++)
        for( j=i+1; j<500; j++)
            cap[i][j] = 2;
    for(i=1; i<500; i++)
        cap[i][500 + (i/2)] =4;
    for(i=500; i < 750; i++ )
    { cap[i][i-250]=3;
        cap[i][750] = 1;
        cap[i][751] = 1;
        cap[i][752] = 5;
    }
    cap[751][753] = 5;
    cap[752][753] = 5;
    cap[753][750] = 20;
    for( i=754; i< 999; i++)
    {  cap[753][i]=1;
        cap[i][500]=3;
        cap[i][498]=5;
        cap[i][1] = 100;
    }
    cap[900][999] = 1;
    cap[910][999] = 1;
    cap[920][999] = 1;
    cap[930][999] = 1;
    cap[940][999] = 1;
    cap[950][999] = 1;
    cap[960][999] = 1;
    cap[970][999] = 1;
    cap[980][999] = 1;
    cap[990][999] = 1;
    printf("prepared capacity matrix, now executing maxflow code\n");
    maximum_flow(1000,0,999,&(cap[0][0]),&(flow[0][0]));
    for(i=0; i<=999; i++)
        for(j=0; j<=999; j++)
        {  if( flow[i][j] > cap[i][j] )
        {  printf("Capacity violated\n"); exit(0);}
        }
    flowsum = 0;
    for(i=0; i<=999; i++)
        flowsum += flow[0][i];
    printf("Outflow of  0 is %d, should be 10\n", flowsum);
    flowsum = 0;
    for(i=0; i<=999; i++)
        flowsum += flow[i][999];
    printf("Inflow of 999 is %d, should be 10\n", flowsum);

    printf("End Test\n");
}


//int main()
//{
//    int vertices = 6; int source = 0; int target = 5; //target = n - 1
//
//    int capacityMatrx [6][6];
//    int flowMatrx [6][6];
//    int i, j;
//    printf("Enter Capacity for matrix: \n");
//
//    for (i = 0 ; i < vertices ; i++ ) //rows
//    {
//        for (j = 0 ; j < vertices ; j++) //columns
//        {
//            scanf("%d", &capacityMatrx[i][j]);
//        }
//    }
//
//    maximum_flow(vertices, source, target, &(capacityMatrx[0][0]), &(flowMatrx[0][0]) );
//
//
//    for (i = 0 ; i < vertices ; i++ ) //rows
//    {
//        for (j = 0 ; j < vertices ; j++) //columns
//        {
//            printf ( " %d ", flowMatrx[i][j] );
//        }
//        printf ("\n");
//    }
//
//
//    return 0;
//}
