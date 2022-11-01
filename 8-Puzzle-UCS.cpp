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

problem up(const problem currProb){
  problem newProb;
  newProb.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    newProb.currState[i] = new int[3];
  }
  for(unsigned int i = 0; i < arrSize; ++i) { //copy puzzle
    for(unsigned int j = 0; j < arrSize; ++j) {
      newProb.currState[i][j] = currProb.currState[i][j];
    }
  }
  newProb.x_pos = currProb.x_pos; //set x-coordinate for blank spot
  newProb.y_pos = currProb.y_pos; //set y-coordinate for blank spot
  newProb.g_n = currProb.g_n + 1; //parent g_n + 1

  //move number below blank space up
  if(newProb.x_pos >= 0 && newProb.x_pos <= 1){
      newProb.currState[newProb.x_pos][newProb.y_pos] = newProb.currState[newProb.x_pos+1][newProb.y_pos];
      newProb.currState[newProb.x_pos+1][newProb.y_pos] = 0;
      newProb.x_pos = newProb.x_pos+1;
  }

  return newProb; //return modified problem
}

problem down(const problem currProb){
  problem newProb;
  newProb.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    newProb.currState[i] = new int[3];
  }
  for(unsigned int i = 0; i < arrSize; ++i) { //copy puzzle
    for(unsigned int j = 0; j < arrSize; ++j) {
      newProb.currState[i][j] = currProb.currState[i][j];
    }
  }
  newProb.x_pos = currProb.x_pos; //set x-coordinate for blank spot
  newProb.y_pos = currProb.y_pos; //set y-coordinate for blank spot
  newProb.g_n = currProb.g_n + 1; //parent g_n + 1

  if(newProb.x_pos >= 1 && newProb.x_pos <= 2){
      newProb.currState[newProb.x_pos][newProb.y_pos] = newProb.currState[newProb.x_pos-1][newProb.y_pos];
      newProb.currState[newProb.x_pos-1][newProb.y_pos] = 0;
      newProb.x_pos = newProb.x_pos-1;
  }
  return newProb; //return modified problem
}

problem right(const problem currProb){
  problem newProb;
  newProb.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    newProb.currState[i] = new int[3];
  }
  for(unsigned int i = 0; i < arrSize; ++i) { //copy puzzle
    for(unsigned int j = 0; j < arrSize; ++j) {
      newProb.currState[i][j] = currProb.currState[i][j];
    }
  }
  newProb.x_pos = currProb.x_pos; //set x-coordinate for blank spot
  newProb.y_pos = currProb.y_pos; //set y-coordinate for blank spot
  newProb.g_n = currProb.g_n + 1; //parent g_n + 1

  if(newProb.y_pos >= 1 && newProb.y_pos <= 2){
      newProb.currState[newProb.x_pos][newProb.y_pos] = newProb.currState[newProb.x_pos][newProb.y_pos-1];
      newProb.currState[newProb.x_pos][newProb.y_pos-1] = 0;
      newProb.y_pos = newProb.y_pos-1;
  }
  return newProb; //return modified problem
}

problem left(const problem currProb){
  problem newProb;
  newProb.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    newProb.currState[i] = new int[3];
  }
  for(unsigned int i = 0; i < arrSize; ++i) { //copy puzzle
    for(unsigned int j = 0; j < arrSize; ++j) {
      newProb.currState[i][j] = currProb.currState[i][j];
    }
  }
  newProb.x_pos = currProb.x_pos; //set x-coordinate for blank spot
  newProb.y_pos = currProb.y_pos; //set y-coordinate for blank spot
  newProb.g_n = currProb.g_n + 1; //parent g_n + 1

  if(newProb.y_pos >= 0 && newProb.y_pos <= 1){
      newProb.currState[newProb.x_pos][newProb.y_pos] = newProb.currState[newProb.x_pos][newProb.y_pos+1];
      newProb.currState[newProb.x_pos][newProb.y_pos+1] = 0;
      newProb.y_pos = newProb.y_pos+1;
  }
  return newProb; //return modified problem
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

  int initialState[3][3] = {1,8,2,0,4,3,7,6,5}; //random start state

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
  eight_puzzle.y_pos = 0; //set y-coordinate for blank spot

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

  /*USED FOR TESTING
  //push initial state (root of tree) into queue
  nodes.push(eight_puzzle);
  cout << "Size of queue: " << nodes.size() << endl;
  currProb = nodes.front();
  nodes.pop();
  cout << "Before:\n";
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      cout << currProb.currState[i][j] << ' ';
    }
    cout << "\n";
  }

  expand(currProb, nodes); //returns the children nodes of currProb

  cout << "Size of queue: " << nodes.size() << endl;
  int nodesCount = 0;
  while(!nodes.empty()){
    cout << "Node number " << ++nodesCount << endl;
    currProb = nodes.front();
    nodes.pop();
    for(unsigned int i = 0; i < arrSize; ++i) {
      for(unsigned int j = 0; j < arrSize; ++j) {
        cout << currProb.currState[i][j] << ' ';
      }
      cout << "\n";
    }

  }*/


  while(!nodes.empty()){
    currProb = nodes.front();
    nodes.pop();
    if(goalTest(currProb)){
      cout << "Success!" << endl;
      return 0; //success algorithm done
    }
    //expand - get all children nodes from currProb by using all possible operators
    expand(currProb, nodes); //adds the children nodes of currProb into queue
    if(nodes.empty()){
      cout << "algorithm failed.\n";
      return -1;
    }
  }

  return 0;
}
