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
  int x_pos; //x-Position for blank spot
  int y_pos; //y-Position for blank spot
  int f_n = 0;// heuristic cost
  int g_n = 0;//depth cost

};

const int arrSize = 3;
int goalState[3][3] = {1,2,3,4,5,6,7,8,0};

bool equalProblems(problem prob1, problem prob2){ //returns true if given puzzles are the same
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      if(prob1.currState[i][j] != prob2.currState[i][j]){ //if any cell does not match then goal state isn't reached
        return false;
      }
    }
  }
    return true;
}

bool goalTest(problem currProb){
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      if(goalState[i][j] != currProb.currState[i][j]){ //if any cell does not match then goal state isn't reached
        return false;
      }
    }
  }
    return true;
}

problem up(problem currProb){
  //move number below blank space up
  if(currProb.x_pos >= 0 && currProb.x_pos <= 1){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos+1][currProb.y_pos];
      currProb.currState[currProb.x_pos+1][currProb.y_pos] = 0;
      currProb.x_pos = currProb.x_pos+1;
  }
  currProb.g_n += 1; //parent g_n + 1
  return currProb; //return modified problem
}

problem down(problem currProb){
  if(currProb.x_pos >= 1 && currProb.x_pos <= 2){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos-1][currProb.y_pos];
      currProb.currState[currProb.x_pos-1][currProb.y_pos] = 0;
      currProb.x_pos = currProb.x_pos-1;
  }
  currProb.g_n += 1; //parent g+n + 1
  return currProb; //return modified problem
}

problem right(problem currProb){
  if(currProb.y_pos >= 1 && currProb.y_pos <= 2){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos][currProb.y_pos-1];
      currProb.currState[currProb.x_pos][currProb.y_pos-1] = 0;
      currProb.y_pos = currProb.y_pos-1;
  }
  currProb.g_n += 1; //parent g+n + 1
  return currProb; //return modified problem
}

problem left(problem currProb){
  if(currProb.y_pos >= 0 && currProb.y_pos <= 1){
      currProb.currState[currProb.x_pos][currProb.y_pos] = currProb.currState[currProb.x_pos][currProb.y_pos+1];
      currProb.currState[currProb.x_pos][currProb.y_pos+1] = 0;
      currProb.y_pos = currProb.y_pos+1;
  }
  currProb.g_n += 1; //parent g+n + 1
  return currProb; //return modified problem
}

void expand(problem currProb, queue<problem>& nodes){
  problem upOperator = up(currProb);
  if(!equalProblems(currProb, upOperator)){
    nodes.push(upOperator);
  }
  problem downOperator = down(currProb);
  if(!equalProblems(currProb, downOperator)){
    nodes.push(downOperator);
  }
  problem leftOperator = left(currProb);
  if(!equalProblems(currProb, leftOperator)){
    nodes.push(leftOperator);
  }
  problem rightOperator = right(currProb);
  if(!equalProblems(currProb, rightOperator)){
    nodes.push(rightOperator);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  problem eight_puzzle;
  //create 2D array to keep track of current state of puzzle
  eight_puzzle.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    eight_puzzle.currState[i] = new int[3];
  }

  int initialState[3][3] = {8,3,5,4,1,0,2,7,6}; //random start state

  //initialize eight-puzzle to the initial state
  /* Initialize eigh-puzzle to the initial state
      -Puzzle is initialized to random start State
      -Depth cost of initial state is 0
      -Heuristic cost for Uniform cost search is 0
  */

  for(unsigned int i = 0; i < arrSize; ++i) { //initialize puzzle to initial state
    for(unsigned int j = 0; j < arrSize; ++j) {
      eight_puzzle.currState[i][j] = initialState[i][j];
    }
  }
  eight_puzzle.x_pos = 1; //set x-coordinate for blank spot
  eight_puzzle.y_pos = 2; //set y-coordinate for blank spot

  cout << "Initial State:\n";
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      cout << initialState[i][j] << ' ';
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

  //data structure to track nodes
  queue<problem> nodes;
  problem currProb;

  //push initial state (root of tree) into queue
  nodes.push(eight_puzzle);
  currProb = nodes.front();
  nodes.pop();
  cout << "Before:\n";
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      cout << currProb.currState[i][j] << ' ';
    }
    cout << "\n";
  }

  expand(currProb, nodes);
  if(!nodes.empty()){
    currProb = nodes.front();
    nodes.pop();
  }
  cout << "After 1:\n";
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      cout << currProb.currState[i][j] << ' ';
    }
    cout << "\n";
  }

  if(!nodes.empty()){
    currProb = nodes.front();
    nodes.pop();
  }
  cout << " After 2:\n";
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      cout << currProb.currState[i][j] << ' ';
    }
    cout << "\n";
  }


  /*while(!nodes.empty()){
    currProb = nodes.front();
    nodes.pop();
    if(goalTest(currProb)){
      return 0; //success algorithm done
    }
    //expand - get all children nodes from currProb by using all possivle operators
    if(nodes.empty()){
      cout << "algorithm failed.\n";
      return -1;
    }
  }*/

  return 0;
}
