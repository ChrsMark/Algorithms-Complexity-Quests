#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int L, W;


/* function for efficient reading from http://corelab.ntua.gr/courses/algorithms/problemsets/read.c */ 
#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;



long readLong() 
{

    long d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}

/* a struct to represent a point in 2-D coordinate system*/
struct Coordinate
{
    int i, j;
    long weight;
    int explorationState;
	unsigned long D;
	int parentI;
	int parentJ;
 
};

vector<vector<Coordinate> > plaketa;
struct Coordinate *startingPoint; 
struct Coordinate *finishingPoint;
struct Coordinate *u;
struct Coordinate *v;


struct Comp
{
   bool operator()(const Coordinate* s1, const Coordinate* s2)
   {
       return (s1->D) > (s2->D);
   }
};
 
/* machine functiuon that does the job */
void dijkstra()
{
   vector<Coordinate *> myHeap; 

   myHeap.resize(1, startingPoint);
   make_heap(myHeap.begin(), myHeap.end(), Comp());

  

   struct Coordinate *currentNode;

   // while heap has elements go on dijkstra exploration
   while (myHeap.size() > 0) {
		currentNode = myHeap.front();
		if ((currentNode->i == finishingPoint->i) && (currentNode->j == finishingPoint->j))
			break;
		pop_heap (myHeap.begin(),myHeap.end(), Comp());
		myHeap.pop_back();
		currentNode->explorationState = 1;		//Mark u as explored

		if (currentNode->i == plaketa[currentNode->parentI][currentNode->parentJ].i) {
		//If we have came from row then we will go on to the column.
			// expand down 
			for (int i = (currentNode->i) + 1; i < L; i++) {
				v = &plaketa[i][currentNode->j];
				//printf("Examining %d,%d.\n", v->i, v->j);
				// it is explored already or it is an obstacle
				if (v->explorationState == 1)
					break;
				else if (v->explorationState == -1) {
					v->D = currentNode->D + v->weight;
					v->parentI = currentNode->i;
					v->parentJ = currentNode->j;
					v->explorationState = 0;
					myHeap.push_back(v);
					push_heap (myHeap.begin(), myHeap.end(), Comp());
					
				}
				else {
					unsigned long myTemp = currentNode->D + v->weight;
					if (myTemp < v->D) {
						v->D = myTemp;
						v->parentI = currentNode->i;
						v->parentJ = currentNode->j;
						v->explorationState = 0;
						
					}
				}
			}

			// expand up 
			for (int i = (currentNode->i) - 1; i >= 0; i--) {
				v = &plaketa[i][currentNode->j];
				//printf("Examining %d,%d.\n", v->i, v->j);
				
				// it is explored already or it is an obstacle
				if (v->explorationState == 1)
					break;

				else if (v->explorationState == -1) {
					v->D = currentNode->D + v->weight;
					v->parentI = currentNode->i;
					v->parentJ = currentNode->j;
					v->explorationState = 0;
					myHeap.push_back(v);
					push_heap (myHeap.begin(), myHeap.end(), Comp());
				}
				else {
					unsigned long myTemp = currentNode->D + v->weight;
					if (myTemp < v->D) {
						v->D = myTemp;
						v->parentI = currentNode->i;
						v->parentJ = currentNode->j;
						v->explorationState = 0;
					}
				}
			}
		}

		if (currentNode->j == plaketa[currentNode->parentI][currentNode->parentJ].j) {
		//If we have came from column then we will go on to the row.

		
			// expand right 
			for (int j = (currentNode->j) + 1; j < W; j++) {
				v = &plaketa[currentNode->i][j];
				
				// it is explored already or it is an obstacle
				if (v->explorationState == 1)
					break;
				else if (v->explorationState == -1) {
					v->D = currentNode->D + v->weight;
					v->parentI = currentNode->i;
					v->parentJ = currentNode->j;
					v->explorationState = 0;
					myHeap.push_back(v);
					push_heap (myHeap.begin(), myHeap.end(), Comp());
				}
				else {
					unsigned long myTemp = currentNode->D + v->weight;
					if (myTemp < v->D) {
						v->D = myTemp;
						v->parentI = currentNode->i;
						v->parentJ = currentNode->j;
						v->explorationState = 0;
					}
				}
			}

			
			// expand left 	
			for (int j = (currentNode->j) - 1; j >= 0; j--) {
				v = &plaketa[currentNode->i][j];
				
				// it is explored already or it is an obstacle
				if (v->explorationState == 1)
					break;
				else if (v->explorationState == -1) {
					v->D = currentNode->D + v->weight;
					v->parentI = currentNode->i;
					v->parentJ = currentNode->j;
					v->explorationState = 0;
					myHeap.push_back(v);
					push_heap (myHeap.begin(), myHeap.end(), Comp());
					//printf("Added %d,%d to heap with D = %lu\n", v->i, v->j, v->D);

				}
				else {
					unsigned long myTemp = currentNode->D + v->weight;
					if (myTemp < v->D) {
						v->D = myTemp;
						v->parentI = u->i;
						v->parentJ = u->j;
						v->explorationState = 0;
						//printf("Updated node %d,%d\n", v->i, v->j);

					}
				}
			}
		}

	}	//end of while

	printf("%lu\n", currentNode->D);


}
 
 
// Driver program to test above functions
int main()
{

    cin >> L >> W ;               //read input
    
    //alocate space for the matrix
    plaketa.resize(L, vector<Coordinate>(W));

    /******** read the input and find connection points ********/
    
    int connectionPoints=0;
    
    //read the  matrix
    for (int i=0; i<L; i++)
        for (int j=0; j<W; j++){
         plaketa[i][j].weight= readLong();
         plaketa[i][j].i=i;
         plaketa[i][j].j=j;
         plaketa[i][j].explorationState=-1;
         
         //check for connection points
         if(plaketa[i][j].weight==0 && connectionPoints==0 ) {
            
            connectionPoints++;

            plaketa[i][j].D = 0;
            plaketa[i][j].parentI=i;
            plaketa[i][j].parentJ=j;
            startingPoint = &plaketa[i][j];
         } 
         else if (plaketa[i][j].weight==0 && connectionPoints!=0) {
            plaketa[i][j].D = ULONG_MAX;
            finishingPoint = &plaketa[i][j];
         }
         else{
         	plaketa[i][j].D = ULONG_MAX;
         } 

         // if it is an obstacle make it to be out of the set
         if(plaketa[i][j].weight==4000){
         	plaketa[i][j].explorationState=1;
         }

        }

    /******* END OF READING *********/

    //printf("Now i will run dijkstra in the maze\n"); 
    dijkstra();
 
    return 0;
}
