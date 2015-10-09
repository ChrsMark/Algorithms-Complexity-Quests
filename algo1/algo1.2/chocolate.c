#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>




struct point
{
    int point_in_road;
    char type_of_point;   // it is starting or finishing point of a job 
 }; 
void quickSort( struct point [], int, int);
int partition( struct point [], int, int);

struct point *points;  // we have k starting points and k finishing points total is 2K points






//set these as GLOBAL to be accessible from all function with having to "pass" their pointers


int N,minTime,maxNum;
long long  int K;
  
int main(int argc, char *argv[]) {
    
   
     
    N=K=0;
    int i;
    int d,r;

    i = 0;    

    scanf("%d",&N);
    scanf("%lld",&K);
    


    int Bound = 2*N; 
    int j=0;
    points = malloc((Bound) * sizeof(struct point));
    for (i=0; i<N; i++){
        
        scanf("%d",&d);
        scanf("%d",&r);
        
        points[j].point_in_road = d;
        points[j].type_of_point = 'S';
        j++;
        points[j].point_in_road = r;
        points[j].type_of_point = 'F';
        j++;
    }
 
    //  start of sorting here
  
    quickSort( points, 0, (Bound)-1);
    
    

    // end of sorting here
    

    

    int successTime=0;
    long long int capacity=0;
    int factor=0;
    int previous = points[0].point_in_road;
    int previousFact=0;
    

    for( i=0; i<Bound; i++){
        
       // first do the 
        capacity = capacity + (points[i].point_in_road - previous)*factor ;
        if(capacity==K){
            //printf("i found it exactly\n");
            successTime = points[i].point_in_road;
            break;
        }
        
		
        if (points[i].type_of_point== 'S'){
            previousFact=factor;
			capacity++;
            factor++;
        } 
        
        if (points[i].type_of_point== 'F'){
            previousFact=factor;
            factor--;
        } 
        
        
        // after adds have been done check if the goal is here!
        if(capacity==K){
            successTime = points[i].point_in_road;
            break;
        }
        else if(capacity>K){  // if capacity is >k then the WantedTime is somewhere between curent i and previous stop
            if(points[i].type_of_point== 'S'){
				successTime=points[i].point_in_road - ((capacity-1-K)/previousFact);
                break;
            }

            else{
                successTime=points[i].point_in_road - ((capacity-K)/previousFact);
                break;
            }
        }
         previous = points[i].point_in_road;
		 
    }


    

    printf("%d\n", successTime);
    free(points);
    return 0;

}   



void quickSort( struct point a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
    // divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
    
}



int partition( struct point a[], int l, int r) {
   int pivot, i, j;
   struct point t;
   pivot = a[l].point_in_road;
   i = l; j = r+1;
        
   while( 1)
   {
    do ++i; while( a[i].point_in_road <= pivot && i <= r );
    do --j; while( a[j].point_in_road > pivot );
    if( i >= j ) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}