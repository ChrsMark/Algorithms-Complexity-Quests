#include <iostream>
#include <vector>
#include <ctime>
#include <climits>

using namespace std;

int N, M, K;
struct state {
  int playerNow;
  int playerNext;
} ;

void pritnState(state condition ){
	cout <<"("<< condition.playerNow <<","<<condition.playerNext<<")	";

}

state zeroState,helpState;
int** room; 
state ** roomOnLine;// you have to change this so as to be table of conditions(P1,P2)

state best(state a, state b){
	if(a.playerNow>b.playerNow) return a;
	else if(a.playerNow == b.playerNow){
		if(a.playerNext<b.playerNext) return a;
		else return b;
	}
	else return b;
}

state swapState(state a){
	int swap;
	swap = a.playerNow;
	a.playerNow = a.playerNext;
	a.playerNext= swap;

	return a;
}

//you have to change the function so as to take the the turn of the player also
state dfs(int i, int j, int turn) {
	//cout << "42.1 i am writng now at! "<<i<< ","<< j<<endl;
   
  helpState.playerNow = 0;
  helpState.playerNext=INT_MAX;
  state myBestState = helpState;
  int money = room [i][j];

  if (i == N-1 && j == M-1 ){ // check for last time in procedure && j == M-1
  		//cout << "i am writng now at! "<<i<< ","<< j<<endl;
  		if(roomOnLine[i][j].playerNow==0 && roomOnLine[i][j].playerNext==0){
  			 roomOnLine[i][j].playerNow=money;
  			 roomOnLine[i][j].playerNext=0;

	  	}
  		//cout << "ok with the writing at "<<i<< ","<< j<<endl;
  		return roomOnLine[i][j];
  }      
  else if (i==N-1){
  		//cout << "i should work! "<<i<< ","<< j<<endl;
		for(int l=1; l<=K; l++){
			
			if(j+l>=M)	break;
			if(roomOnLine[i][j+l].playerNow==0 && roomOnLine[i][j+l].playerNext==0){
				helpState=dfs(i,j+l,!turn);
				//helpState = swapState(helpState);
				myBestState = best(helpState,myBestState);
				
			}
			else{
					helpState.playerNow = roomOnLine[i][j+l].playerNow;
					helpState.playerNext = roomOnLine[i][j+l].playerNext;
					myBestState = best(helpState,myBestState);
			}

			
		}
		helpState = myBestState;
		myBestState.playerNow = money + helpState.playerNext;
		myBestState.playerNext = helpState.playerNow;

		roomOnLine[i][j].playerNow = myBestState.playerNow;
		roomOnLine[i][j].playerNext = myBestState.playerNext;

		/*cout<<"\n";
		for( int e=0;e<N; e++) {
      for ( int r=0;r<M; r++)
        pritnState(roomOnLine[e][r]); 
      cout << endl;
   } */

		return myBestState;
		
  }	
  else if (j==M-1){
  		for(int k=1; k<=K; k++ ){

  				if(i+k>=N) break;
				
				if(roomOnLine[i+k][j].playerNow==0 && roomOnLine[i+k][j].playerNext==0){
					helpState=dfs(i+k,j,!turn);
					//helpState = swapState(helpState);
					myBestState = best(helpState,myBestState);

				}
				else{
					helpState.playerNow = roomOnLine[i+k][j].playerNow;
					helpState.playerNext = roomOnLine[i+k][j].playerNext;
					myBestState = best(helpState,myBestState);
			}

			
		}
		helpState = myBestState;
		myBestState.playerNow = money + helpState.playerNext;
		myBestState.playerNext = helpState.playerNow;

		roomOnLine[i][j].playerNow = myBestState.playerNow;
		roomOnLine[i][j].playerNext = myBestState.playerNext;

		/*cout<<"\n";
		for( int e=0;e<N; e++) {
      for ( int r=0;r<M; r++)
        pritnState(roomOnLine[e][r]); 
      cout << endl;
   } */

		return myBestState;
  }
  else{
  		
		for(int k=0; k<=K; k++ ){
			for(int l=0; l<=K; l++){
				if(k==0 && l==0) continue;
				if(i+k>=N) break;
				if(j+l>=M)	break;
				//if (i==0 && j==0) cout << "i open at! "<<k<< ","<< l<<endl;
				if(roomOnLine[i+k][j+l].playerNow==0 && roomOnLine[i+k][j+l].playerNext==0){
					
					helpState=dfs(i+k,j+l,!turn);
					//helpState = swapState(helpState);
					
					/*cout<<"1.choose between my best: ";pritnState(myBestState);
					cout<<" and: ";pritnState(helpState);cout<<"\n";*/
					myBestState = best(helpState,myBestState);
					//cout<<"My decision is:";pritnState(myBestState);cout<<"\n";
					
				}
				else{
					helpState.playerNow = roomOnLine[i+k][j+l].playerNow;
					helpState.playerNext = roomOnLine[i+k][j+l].playerNext;
					/*cout<<"2.choose between my best: ";pritnState(myBestState);
					cout<<" and: ";pritnState(helpState);cout<<"\n";*/
					myBestState = best(helpState,myBestState);
					//cout<<"My decision is:";pritnState(myBestState);cout<<"\n";

				}
				//if (i==0 && j==0) cout << "i just finished at! "<<i+k<< ","<< j+l<<endl;
				
			}
		}
		
		/*cout<<"My best state is : ";
		pritnState(myBestState);
		cout<<"\n";		
		cout<<"\n";*/
		helpState = myBestState;
		myBestState.playerNow = money + helpState.playerNext;
		myBestState.playerNext = helpState.playerNow;

		roomOnLine[i][j].playerNow = myBestState.playerNow;
		roomOnLine[i][j].playerNext = myBestState.playerNext;

/*cout<<"\n";
		for( int e=0;e<N; e++) {
      for ( int r=0;r<M; r++)
        pritnState(roomOnLine[e][r]); 
      cout << endl;
   }*/ 

		return myBestState;
		
  }
  	
}


int main() {
  
    cin >> N >> M >> K;               //read input
    //cout << N <<" " <<M <<" " << K <<"\n" ;

    zeroState.playerNow=0;
    zeroState.playerNext=0;

    room = new int*[N];
    roomOnLine = new state*[N];
	for(int i = 0; i < N; ++i){
    	room[i] = new int[M];
    	roomOnLine[i] = new state[M];
	}
	
	//read the room matrix
	for (int i=0; i<N; i++)
		for (int j=0; j<M; j++){
		 cin >> room[i][j];
		 roomOnLine[i][j] = zeroState;
		}

		/*cout << "This is the room table"<<endl;
    // Print out the elements
   for( int i=0;i<N; i++) {
      for ( int j=0;j<M; j++)
        cout << room[i][j] << "	"; 
      cout << endl;
   }
   cout << "This is the OnLine table"<<endl;
   //Print out the OnLine table
   for( int i=0;i<N; i++) {
      for ( int j=0;j<M; j++)
        pritnState(roomOnLine[i][j]); 
      cout << endl;
   }*/


   //long long ans = 43;
    state ans = dfs(0, 0,0);//turn switches between 0 and 1 and this may be useless!!!
    ans=swapState(ans);
    cout << ans.playerNow <<" "<<ans.playerNext<< "\n" ;

    /*cout << "This is the Final OnLine table"<<endl;
   //Print out the OnLine table
   for( int i=0;i<N; i++) {
      for ( int j=0;j<M; j++)
        pritnState(roomOnLine[i][j]); 
      cout << endl;
   } */
    
  
}