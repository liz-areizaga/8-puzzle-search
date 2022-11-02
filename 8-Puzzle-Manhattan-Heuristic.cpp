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

/* custom function to sort vector by cheapest cost (g_n + h_n)
REFERENCED: https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
*/
struct greater_than_key {
    inline bool operator() (const problem& prob1, const problem& prob2)
    {
        return (prob1.g_n + prob1.h_n > prob2.g_n + prob2.h_n);
    }
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

problem up(const problem currProb){ // moves the tile below the blank spot up if within range
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
  newProb.h_n = computeManhattanDist(newProb);

  return newProb; //return modified problem
}

problem down(const problem currProb){ // moves the tile above the blank spot down if within range
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
  newProb.h_n = computeManhattanDist(newProb);
  return newProb; //return modified problem
}

problem right(const problem currProb){ // moves the tile to the left of the blank spot right if within range
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
  newProb.h_n = computeManhattanDist(newProb);
  return newProb; //return modified problem
}

problem left(const problem currProb){ // moves the tile to the right of the blank spot left if within range
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
  newProb.h_n = computeManhattanDist(newProb);
  return newProb; //return modified problem
}

/*EXPAND
  -tests all operators on given puzzle
  -adds valid resulting puzzles into queue
*/
void expand(problem currProb, vector<problem>& nodes){ //creates children of current puzzle

  problem upOperator = up(currProb);
  if(!equalProblems(currProb, upOperator)){
    nodes.push_back(upOperator);
  }
  problem downOperator = down(currProb);
  if(!equalProblems(currProb, downOperator)){
    nodes.push_back(downOperator);
  }
  problem leftOperator = left(currProb);
  if(!equalProblems(currProb, leftOperator)){
    nodes.push_back(leftOperator);
  }
  problem rightOperator = right(currProb);
  if(!equalProblems(currProb, rightOperator)){
    nodes.push_back(rightOperator);
  }
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

  //int initialState[3][3] = {1,8,2,0,4,3,7,6,5}; //random start state FIRST TEST
  //int initialState[3][3] = {1,2,3,4,5,6,7,8,0}; //DEPTH 0 SOLUTION
  //int initialState[3][3] = {1,2,3,4,5,6,0,7,8}; //DEPTH 2 SOLUTION
  //int initialState[3][3] = {1,2,3,5,0,6,4,7,8}; //DEPTH 4 SOLUTION
  //int initialState[3][3] = {1,3,6,5,0,2,4,7,8}; //DEPTH 8 SOLUTION
  int initialState[3][3] = {1,3,6,5,0,7,4,8,2}; //DEPTH 12 SOLUTION
  //int initialState[3][3] = {1,6,7,5,0,3,4,8,2}; //DEPTH 16 SOLUTION
  //int initialState[3][3] = {7,1,2,4,8,5,6,3,0}; //DEPTH 20 SOLUTION
  //int initialState[3][3] = {0,7,2,4,6,1,3,5,8}; //DEPTH 24 SOLUTION


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
  eight_puzzle.h_n = computeManhattanDist(eight_puzzle); //FIX

  cout << "Initial State:\n";
  for(unsigned int i = 0; i < arrSize; ++i) {
    for(unsigned int j = 0; j < arrSize; ++j) {
      cout << initialState[i][j] << ' ';
    }
    cout << "\n";
  }

  //data structure to track nodes
  //using vector to be able to sort for heuristic search
  vector<problem> nodes;
  problem currProb; //tracks node at the front of the queue

  auto start = high_resolution_clock::now(); //tracks start time of algorithm
  //push initial state (root of tree) into queue
  nodes.push_back(eight_puzzle);
  q_maxSize = nodes.size();

  //test heuristic function - computeMisplacedTiles
  //cout << "Number of mispaced tiles " << computeMisplacedTiles(eight_puzzle) << "\n";

  /*
  GENERIC SEARCH ALGORITHM
    -Misplaced Tiles heuristic
    -h_n = number of tiles that are misplaced
  */

  while(!nodes.empty()){
    sort(nodes.begin(), nodes.end(), greater_than_key());
    currProb = nodes.back();
    nodes.pop_back();
    if(goalTest(currProb)){
      break; //success algorithm done
    }
    //expand - get all children nodes from currProb by using all possible operators
    ++nodes_numExpanded;
    cout << "The best state to expand with g(n) = " << currProb.g_n << " and h(n) = " << currProb.h_n << " is...\n";
    for(unsigned int i = 0; i < arrSize; ++i){
      for(unsigned int j = 0; j < arrSize; ++j){
        cout << currProb.currState[i][j] << ' ';
      }
      cout << "\n";
    }
    expand(currProb, nodes); //adds the children nodes of currProb into queue
    //cout << "Curr size of queue: " << nodes.size() << "\n"; //visualize branching factor
    if(nodes.size() > q_maxSize){
      q_maxSize = nodes.size();
    }
    if(nodes.empty()){
      cout << "algorithm failed.\n";
      return -1;
    }
  }
  auto stop = high_resolution_clock::now(); //tracks end time of algorithm
  cout << "Success!\n";
  cout << "Solution Depth was " << currProb.g_n << ".\n";
  cout << "Number of nodes expanded: " << nodes_numExpanded << "\n";
  cout << "Max queue size: " << q_maxSize << "\n";

  auto duration = duration_cast<microseconds>(stop - start); //tracks time spent of algorithm
  cout << "Time taken to solve puzzle: " << duration.count() << "ms\n";

  return 0;
}
