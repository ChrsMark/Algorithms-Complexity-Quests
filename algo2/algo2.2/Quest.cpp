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
state ** roomOnLine;

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


state dfs(int i, int j) {

   
  helpState.playerNow = 0;
  helpState.playerNext=INT_MAX;
  state myBestState = helpState;
  int money = room [i][j];

  if (i == N-1 && j == M-1 ){ // check for last time in procedure 
  		
  		if(roomOnLine[i][j].playerNow==0 && roomOnLine[i][j].playerNext==0){
  			 roomOnLine[i][j].playerNow=money;
  			 roomOnLine[i][j].playerNext=0;

	  	}

  		return roomOnLine[i][j];
  }      
  else if (i==N-1){ //check if you have reached at the last row

		for(int l=1; l<=K; l++){
			
			if(j+l>=M)	break;
			if(roomOnLine[i][j+l].playerNow==0 && roomOnLine[i][j+l].playerNext==0){
				helpState=dfs(i,j+l);
				myBestState = best(helpState,myBestState);				
			}
			else{
					helpState.playerNow = roomOnLine[i][j+l].playerNow;
					helpState.playerNext = roomOnLine[i][j+l].playerNext;
					myBestState = best(helpState,myBestState);
			}			
		}
		
  }	
  else if (j==M-1){ //check if you have reached at the last column
  		for(int k=1; k<=K; k++ ){

  				if(i+k>=N) break;
				
				if(roomOnLine[i+k][j].playerNow==0 && roomOnLine[i+k][j].playerNext==0){
					helpState=dfs(i+k,j);
					myBestState = best(helpState,myBestState);
				}
				else{
					helpState.playerNow = roomOnLine[i+k][j].playerNow;
					helpState.playerNext = roomOnLine[i+k][j].playerNext;
					myBestState = best(helpState,myBestState);
			}			
		}

  }
  else{ //you are in the middle of nowhere, go on! 
  		
		for(int k=0; k<=K; k++ ){
			for(int l=0; l<=K; l++){
				if(k==0 && l==0) continue;
				if(i+k>=N) break;
				if(j+l>=M)	break;
				
				if(roomOnLine[i+k][j+l].playerNow==0 && roomOnLine[i+k][j+l].playerNext==0){					
					helpState=dfs(i+k,j+l);
					myBestState = best(helpState,myBestState);					
				}
				else{
					helpState.playerNow = roomOnLine[i+k][j+l].playerNow;
					helpState.playerNext = roomOnLine[i+k][j+l].playerNext;
					myBestState = best(helpState,myBestState);
				}
			}
		}		
  }

  //take the money and swap!
  helpState = myBestState;
  myBestState.playerNow = money + helpState.playerNext;
  myBestState.playerNext = helpState.playerNow;
  //copy that state at memo table
  roomOnLine[i][j].playerNow = myBestState.playerNow;
  roomOnLine[i][j].playerNext = myBestState.playerNext;

  return myBestState;
  	
}


int main() {
  
    cin >> N >> M >> K;               //read input

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
	//solve the DP			
    state ans = dfs(0,0);
    ans=swapState(ans);
    cout << ans.playerNow <<" "<<ans.playerNext<< "\n" ;   
}