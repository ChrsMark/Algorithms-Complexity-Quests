
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <map>
#include <vector>
#include <queue>
#define myPair pair<int,int>

using namespace std;
class Combine
{
public:
    int operator() ( const pair<int, int>& p1, const pair<int, int>& p2 )
    {
        return p1.second < p2.second;
    }
};

using namespace std;

#define MARKER -1

;

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

int numOfNodes=0;
int K;  // K stands for the number of planets in the solar system


  

/* A binary tree Node has key, pointer to left and right children */
struct Node
{
    int key;
    struct Node* left, *right;
};

// A table Nodes. Each item represents the airspace-port of each planet
// Above this Node , all city-Nodes will be allocated!
Node **planets;

// A table Nodes. Each item represents a city of 
// Above this Node , the child city-Nodes will be allocated!
Node **myPointers;

// forword priority-queue
priority_queue<myPair, vector<myPair > , Combine > Qf;
// backword-priority-queue
priority_queue<myPair, vector<myPair > , Combine > Qb;
 
/* Helper function that allocates a new Node with the
   given key and NULL left and right pointers. */
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return (temp);
}
 
// This function adds a node in the proper position in the tree
void deSerialize(int parentID)
{
    // Read next item from file. If theere are no more items or next
    // item is marker, then return
    int val=numOfNodes;
    numOfNodes++;
    
 
    // Else create node with this item and recur for children
    Node *root = newNode(val);
    myPointers[val]=root;
    if(myPointers[parentID]->left==NULL){
     //printf("i will add a left child\n");
     myPointers[parentID]->left=root;
 	}
    else {
    	//printf("i will add a right child\n");
    	myPointers[parentID]->right=root;
    }
}
 
// A simple inorder traversal used for testing the constructed tree
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
 

/*The second parameter is to store the height of tree.
   Initially, we need to pass a pointer to a location with value
   as 0. So, function should be used as follows:
 
   int height = 0;
   struct node *root = SomeFunctionToMakeTree();
   int diameter = diameterOpt(root, &height); */

int diameterOpt(Node *root, int* height)
{
  /* lh --> Height of left subtree
      rh --> Height of right subtree */
  int lh = 0, rh = 0;
  
  /* ldiameter  --> diameter of left subtree
      rdiameter  --> Diameter of right subtree */
  int ldiameter = 0, rdiameter = 0;
  
  if(root == NULL)
  {
    *height = 0;
     return 0; /* diameter is also 0 */
  }
  
  /* Get the heights of left and right subtrees in lh and rh
    And store the returned values in ldiameter and ldiameter */
  ldiameter = diameterOpt(root->left, &lh);
  rdiameter = diameterOpt(root->right, &rh);

  // keep the max height to this point saved ;
  //maxSecHeight = maxHeight;
 // if(maxHeight == ( max(lh  ,rh  ) +1  ) ) maxSecHeight = maxHeight; 
  //maxHeight = max (maxHeight , ( max(lh  ,rh  ) +1  ) );
  
  /* Height of current node is max of heights of left and
     right subtrees plus 1*/
  *height = max(lh, rh) + 1 ;
  
  return max(lh + rh +1, max(ldiameter, rdiameter));
}
 

/* slide-window-find */
int myMachine(int A[])
{
 
int maxProfit=0;
  int forword=0;
  int backword=0;

    while(!Qf.empty())
    {  
      int temp = Qf.top().first;
      int temp2 =Qf.top().second;
      if (temp <= forword)
      {
        Qf.pop();
      }
      else{
            maxProfit=max(maxProfit,A[forword]+temp2-forword);
             
            forword++;
          }
    }

       while(!Qb.empty())
    {  
      int temp = Qb.top().first;
      int temp2 =Qb.top().second;
      if (temp <= backword)
      {
        Qb.pop();
      }
      else{
            maxProfit=max(maxProfit,A[backword]+temp2+backword);
           
            backword++;
          }
    }
  
  return maxProfit;
}


/* Driver program to test above functions*/
int main()
{
    

    cin >> K ;               //read input
    
    //alocate space for the matrix
    planets=(Node **) malloc(K*sizeof(Node));
    
    int heights[K];

    int numberOfCities=0;
    int tempAncestor=0;

    /******** read the input and constract the system ********/
             
    //read each planet's road system
    for (int i=0; i<K; i++){
        numOfNodes=0;
        cin >> numberOfCities;    //read number of cities
        // Allocate space to keep the pointers' adresses
        myPointers=(Node **) malloc(numberOfCities*sizeof(Node));
        Node *root1 = NULL;
        root1 = newNode(numOfNodes);
        myPointers[numOfNodes]=root1;
        numOfNodes++;

        planets[i]=root1;

        //cout << "Now the cities are " << numberOfCities << "\n";
        if(numberOfCities == 1){
            cin >> tempAncestor ;
            continue;
        }
        for (int j=0; j<numberOfCities-1; j++){ //add each city in the road-system

         cin >> tempAncestor ;
         //if (tempAncestor==0) break; // There is only one city in this planet!
         //printf("i am gona add node %d with parent %d or else %d\n",numOfNodes,myPointers[tempAncestor-1]->key,tempAncestor-1);
         deSerialize(tempAncestor-1); // Put the city in the right place!

        }
        free(myPointers);
    }

    /************** END OF READ AND CONSTRACTION *************/


    /************** FIND THE TOUR *************/
    int myTempTour;
    int myMaxTour=0;
    

    int maxHeight=0;
    
    for (int i=0; i<K; i++){
        myTempTour=0;

        int height = 0;
        //inorder(planets[i]);
        
        //maxHeightPrev = maxHeight;
        int diameter = diameterOpt(planets[i], &height);
        //printf("%d -> returned height is %d\n",i,height-1);
	//printf("%d, ",height-1);
	
        heights[i]=height-1;
	Qf.push(myPair(i,heights[i]+i));
             
        Qb.push(myPair(i,heights[i]+K-i));
        myTempTour = diameter;
        
        myMaxTour = max(myMaxTour,myTempTour);
    }
	
    maxHeight = myMachine(heights);
    int FinalTour;
    //printf("K=%d\n",K);
    //printf("myMaxTour is %d\n",myMaxTour-1);
    /*if(myMaxTour>maxHeight) printf("result is from tour\n");
    else printf("result is from maxHeight\n");*/
    FinalTour = max (myMaxTour-1, (maxHeight) );
    
    //FinalTour = (myMaxTour -1) + (myMaxSecTour-1) + (K-1);
    /************** END OF TOUR-FINDING *************/
    free(planets);   
    printf("%d\n",FinalTour);
 
    return 0;
}
