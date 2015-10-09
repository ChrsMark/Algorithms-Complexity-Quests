#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int pid = 0;


struct point
{
    int map;
    int id;   // it is starting or finishing point of a job 
 }; 
void quickSort( struct point [], int, int);
int partition( struct point [], int, int);

struct point *points_x;
struct point *points_y;




int main(int argc, char *argv[]) {


	int i,N;
	long long  int minDist;
	



 
  
  
  	scanf("%d",&N);
	points_x = malloc((N) * sizeof(struct point));
	points_y = malloc((N) * sizeof(struct point));
	long long int distance[N];
 
  	i = 0;
	for (i=0; i<N; i++){
	     scanf("%d",&points_x[i].map);
	     scanf("%d",&points_y[i].map);
	     points_x[i].id=i;
	     points_y[i].id=i;
	     distance[i]=0;
	                 }
    
			
	quickSort( points_x, 0, (N)-1);
	quickSort( points_y, 0, (N)-1);
	

	//West to East ->
	int prev =  points_x[0].map;
	int count =0;
	long long int tempSum=0;
	long long int prevSum=0;
	for(i=0; i<N; i++){
		tempSum = 0;
		tempSum =prevSum +(points_x[i].map - prev)*count;
		distance[points_x[i].id] = distance[points_x[i].id] + tempSum;
		prev=points_x[i].map;
		count++;
		prevSum = tempSum;
		

	}
	
	//East to West  <-
	prev =  points_x[N-1].map;
	count=0;
	prevSum=0;
	for(i=N-1; i>=0; i-- ){
		tempSum =prevSum+ (prev-points_x[i].map)*count;
		distance[points_x[i].id] = distance[points_x[i].id] +tempSum;
		prev=points_x[i].map;
		count++;
		prevSum = tempSum;

	}
	//North to South 
	prev =  points_y[N-1].map;
	count=0;
	prevSum=0;
	for(i=N-1; i>=0; i--){
		tempSum = prevSum +(prev-points_y[i].map)*count;
		distance[points_y[i].id] = distance[points_y[i].id] + tempSum;
		prev=points_y[i].map;
		count++;
		prevSum = tempSum;
	}
	//South to North
	prev =  points_y[0].map;
	count=0;
	prevSum=0;
	for(i=0; i<N; i++ ){
		tempSum = prevSum+ (points_y[i].map - prev)*count;
		distance[points_y[i].id] = distance[points_y[i].id] + tempSum;
		prev=points_y[i].map;
		count++;
		prevSum = tempSum;
	}


	//Find min Distance
	minDist = 999999999999999999;
	for(i=0; i<N; i++ ){
		if (distance[i]<minDist) minDist = distance[i];
		
	}

		
printf("%lld\n",minDist);


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
   pivot = a[l].map;
   i = l; j = r+1;
        
   while( 1)
   {
    do ++i; while( a[i].map <= pivot && i <= r );
    do --j; while( a[j].map  > pivot );
    if( i >= j ) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
 
