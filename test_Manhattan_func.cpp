#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

using namespace std::chrono;
using namespace std;

/*REFERENCED GEEKS FOR GEEKS
    for timer implementation
    Link: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
*/

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
  int h_n = 0;// heuristic cost
  int g_n = 0;//depth cost

};


const int arrSize = 3;
int goalState[3][3] = {1,2,3,4,5,6,7,8,0};

int computeCellDist(problem prob1, int x_given, int y_given){ //returns the distance away from its goal position
  int dist = 0;
  int x_dist = 0;
  int y_dist = 0;
  int x_goal;
  int y_goal;
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      if(goalState[i][j] == prob1.currState[x_given][y_given]){
        x_goal = i;
        y_goal = j;
      }
    }
  }

  x_dist = x_given - x_goal;
  y_dist = y_given - y_goal;
  if(x_dist < 0){
    x_dist *= -1;
  }
  if(y_dist < 0) {
    y_dist *= -1;
  }
  dist = x_dist +y_dist;
  return dist;
}

int computeManhattanDist(problem prob1){
  int manhattanDist = 0;
  for(unsigned int i = 0; i < arrSize; ++i){
    for(unsigned int j = 0; j < arrSize; ++j){
      if(prob1.currState[i][j] != goalState[i][j] && prob1.currState[i][j] != 0){ //for any mistmaching tiles, compute how far they are from goal state pos
        manhattanDist += computeCellDist(prob1, i, j);
      }
    }
  }
  return manhattanDist;
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int q_maxSize = 0; //tracks max size of queue
  int nodes_numExpanded = 0; //tracks number of nodes expanded

  problem eight_puzzle;
  //create 2D array to keep track of current state of puzzle
  eight_puzzle.currState = new int* [3];
  for (unsigned int i = 0; i < 3; ++i){
    eight_puzzle.currState[i] = new int[3];
  }

  //int initialState[3][3] = {3,2,8,4,5,6,7,1,0}; //random start state FIRST TEST
  //int initialState[3][3] = {1,2,3,4,5,6,7,8,0}; //DEPTH 0 SOLUTION
  //int initialState[3][3] = {1,2,3,4,5,6,0,7,8}; //DEPTH 2 SOLUTION
  //int initialState[3][3] = {1,2,3,5,0,6,4,7,8}; //DEPTH 4 SOLUTION
  //int initialState[3][3] = {1,3,6,5,0,2,4,7,8}; //DEPTH 8 SOLUTION
  //int initialState[3][3] = {1,3,6,5,0,7,4,8,2}; //DEPTH 12 SOLUTION
  //int initialState[3][3] = {1,6,7,5,0,3,4,8,2}; //DEPTH 16 SOLUTION
  int initialState[3][3] = {7,1,2,4,8,5,6,3,0}; //DEPTH 20 SOLUTION


  //initialize eight-puzzle to the initial state
  /* Initialize eigh-puzzle to the initial state
      -Puzzle is initialized to random start State
      -Depth cost of initial state is 0
      -Heuristic cost for Misplaces Tiles is numMisplacedTiles
  */

  for(unsigned int i = 0; i < arrSize; ++i) { //initialize puzzle to initial state
    for(unsigned int j = 0; j < arrSize; ++j) {
      eight_puzzle.currState[i][j] = initialState[i][j];
    }
  }
  for(unsigned int i = 0; i < arrSize; ++i){ //find blank spot and assign x_pos and y_pos to the coordinates of it
    for(unsigned int j = 0; j < arrSize; ++j){
      if(eight_puzzle.currState[i][j] == 0){
        eight_puzzle.x_pos = i;
        eight_puzzle.y_pos = j;
      }
    }
  }
  eight_puzzle.h_n = computeManhattanDist(eight_puzzle);
  cout << "Manhattan Distance: " << eight_puzzle.h_n << "\n";

  cout << "Initial State:\n";
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      cout << initialState[i][j] << ' ';
    }
    cout << "\n";
  }

  return 0;
}
