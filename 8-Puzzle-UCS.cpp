#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/* i, j
Positions:
0,0 0,1 0,2
1,0 1,1 1,2
2,0 2,1 2,2
*/

struct problem {
  int **currState; // current state
  int initialState[3][3] = {8,3,5,4,1,0,2,7,6}; //random start state
  int goalState[3][3] = {1,2,3,4,5,6,7,8,0};
  int x_pos = 1;
  int y_pos = 2;
  int f_n = 0;// heuristic cost
  int g_n = 0;//depth cost

};

const int arrSize = 3;


//queue<int> q; //look up!
//ask Prof about how exact he wants us to match the pseudo code
//goal test is not a member of the problem, does it need to be?
bool goalTest(problem currProb){
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      if(currProb.goalState[i][j] != currProb.currState[i][j]){ //if any cell does not match then goal state isn't reached
        return false;
      }
    }
  }
    return true;
}

void up(problem& currProb){
  if(currProb.x_pos >= 0 && currProb.x_pos <= 1){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos+1][currProb.y_pos];
      currProb.currState[currProb.x_pos+1][currProb.y_pos] = 0;
      currProb.x_pos = currProb.x_pos+1;
  }
}

void down(problem& currProb){
  if(currProb.x_pos >= 1 && currProb.x_pos <= 2){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos-1][currProb.y_pos];
      currProb.currState[currProb.x_pos-1][currProb.y_pos] = 0;
      currProb.x_pos = currProb.x_pos-1;
  }
}

void right(problem& currProb){
  if(currProb.y_pos >= 1 && currProb.y_pos <= 2){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos][currProb.y_pos-1];
      currProb.currState[currProb.x_pos][currProb.y_pos-1] = 0;
      currProb.y_pos = currProb.y_pos-1;
  }
}

void left(problem& currProb){
  if(currProb.y_pos >= 0 && currProb.y_pos <= 1){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos][currProb.y_pos+1];
      currProb.currState[currProb.x_pos][currProb.y_pos+1] = 0;
      currProb.y_pos = currProb.y_pos+1;
  }
}

queue<problem> nodes;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  problem eight_puzzle;
  //create 2D array to keep track of current state of puzzle
  eight_puzzle.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    eight_puzzle.currState[i] = new int[3];
  }

  //initialize current state to the initial state
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      eight_puzzle.currState[i][j] = eight_puzzle.initialState[i][j];
    }
  }

  cout << "Initial State:\n";
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      cout << eight_puzzle.initialState[i][j] << ' ';
    }
    cout << "\n";
  }

  cout << "Current State:\n";
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      cout << eight_puzzle.currState[i][j] << ' ';
    }
    cout << "\n";
  }

  nodes.push(eight_puzzle.initialState);

  if(goalTest(eight_puzzle)){
    cout << "Solved!\n";
  } else {
    cout << "Not solved\n";
  }

  return 0;
}
