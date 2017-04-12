#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <ctime>
using namespace std;

#define for_r(n,i,f) for(int n = i; n < f; n++)

class sudokuBoard{
private:
  static const int size = 9;
  vector< vector<int> > board;
  vector< vector<bool> > given;

public:
  bool debug = false;
  bool info  = false;
  int callCtr;
  int btrackCtr;
  sudokuBoard(vector< vector<int> > board){
    callCtr = 0;
    btrackCtr = 0;
    board.resize(size, vector<int>(size));
    given.resize(size, vector<bool>(size));
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        given[i][j] = board[i][j] > 0 ? true : false;
      }
    }
    this->board = board;
  }
  sudokuBoard(){
    callCtr = 0;
    btrackCtr = 0;
    board.resize(size, vector<int>(size));
    given.resize(size, vector<bool>(size));
  }
  bool solve(int i, int j){

    callCtr ++;
    if(i >= size && j >= size){
      return true;
    }

    if(debug) printBoard();

    int ni,nj;
    for(ni = 0; ni < size; ni++){
      for(nj = 0; nj < size; nj++){
        if(!given[ni][nj] && (ni != i || nj != j) && board[ni][nj] == 0)
          goto l;
      }
    }
    l:
    //serch possible numbers
    unordered_set<int> possible = getPossible(i, j);

    if(debug){
    cout<<"\nprinting possibles at "<<i<<","<<j<<":"<<endl;
    for( const auto& e: possible){
      cout<< e << " ";
    }
    cout<<endl;
    //loop through them and pass up true
    cout<<"new i, j is "<<ni<<","<<nj<<endl;
    }
    for (const auto& elem: possible) {
      if(debug) cout<<"trying "<<elem<<" at "<<i<<","<<j<<endl;
      board[i][j] = elem;
      if(solve(ni, nj)) return true;
      board[i][j] = 0;
    }
    //must have made a mistake previously
    btrackCtr++;
    return false;
  }
  unordered_set<int> getPossible(int i, int j){
    unordered_set<int> nums,full;
    if(board[i][j] < 0 || board[i][j] > 9)
      return nums;
    //cout<<"same col"<<endl;
    for_r(row, 0, size){
      nums.insert(board[row][j]);
      //cout<<board[row][j]<<" ";
    }

    //cout<<"\nsame row"<<endl;
    for_r(col, 0, size){
      nums.insert(board[i][col]);
      //cout<<board[i][col]<<" ";
    }
    //cout<<"\nsame box"<<endl;
    for(int k = (i/3)*3; k < (i/3)*3 + 3; k++){
      for(int l = (j/3)*3; l < (j/3)*3 + 3; l++){
        nums.insert(board[k][l]);
        //cout<<board[k][l]<<" ";
      }
    }
    //cout<<endl;
    //cout<<"nums"<<endl;
    //for(auto& e: nums){
    //  cout<<e<<" ";
    //}
    //cout<<endl;
    for(int i = 1; i< 10; i++){
      full.insert(i);
    }
    for (const auto& elem: nums) {
      full.erase(elem);
    }
    return full;

  }


  bool solver(){
    int i,j;
    for(i = 0; i < size; i++){
      for(j = 0; j < size; j++){
        //cout<<i<<" "<<j<<endl;
        if(!given[i][j])
          goto l;
      }
    }
    l:
    if(debug) cout<<"\ncalling solve with "<<i<<" "<<j<<endl;
    int start_s=clock();
    bool ans = solve(i, j);
    int stop_s=clock();
    if(info) {
      cout<<"\n..............................."<<endl;
      cout<<"Number of call to solve  : "<< callCtr<<endl;
      cout<<"Number of backtrack      : "<< btrackCtr<<endl;
      cout<<"Execution time in seconds: "<<((stop_s-start_s)/double(CLOCKS_PER_SEC))<<endl;
    }
    return ans;

  }
  bool check(){

    for(int i = 0; i< size; i++){
      for (int j = 0; j < size; j++) {
        if(board[i][j] > 9 || board[i][j] < 1)
          return false;
      }
    }

    unordered_set<int> nums;
    for(int i = 0; i < size; i++){

      for(int j = 0; j<size; j++){
        if(nums.find(board[i][j]) != nums.end())
          return false;
        nums.insert(board[i][j]);
      }
      nums.clear();
    }

    for(int i = 0; i < size; i++){

      for(int j = 0; j<size; j++){
        if(nums.find(board[j][i]) != nums.end())
          return false;
        nums.insert(board[j][i]);
      }
      nums.clear();
    }

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        nums.clear();
        for(int k = i*3; k < 3; k++){
          for(int l = j*3; l < 3; l++){
            if(nums.find(board[k][l]) != nums.end())
              return false;
            nums.insert(board[k][l]);
          }
        }
      }
    }
    return true;
  }
  void printBoard(){
    cout<<"\t";
    for(int i = 0; i < size*2 + 7; i++){
      cout<<(((i) % 8 == 0) ? "+":"-");
    }
    cout<<endl;

    for(int i = 0; i < size; i++){
      cout<<"\t| ";
      for(int j = 0; j < size; j++){
        if(given[i][j]){
        cout<<"\033[1;31m"+to_string(board[i][j])+" \033[0m";
        }else{
          cout << (board[i][j] == 0 ? " ": to_string(board[i][j])) + " ";
        }
        if((j+1) % 3 == 0)cout<<"| ";
      }

      if((i+1) % 3 == 0){
        cout<<"\n\t";
        for(int i = 0; i < size*2 + 7; i++){
          cout<<(((i) % 8 == 0) ? "+":"-");
        }
      }
      cout<<endl;
    }
  }
  bool getProblem(){
    int a;
    for_r(i, 0 , size){
      for_r(j, 0, size){

        cin>>a;
        if(a < 0 || a > 9) {
          cerr<<"\ninput to board is out of range"<<endl;
          return false;
        }
        board[i][j] = a;
        given[i][j] = board[i][j] == 0 ? false : true;
      }
    }
    return true;
  }

};
int main(int argc, char *argv[]){


sudokuBoard sudoku;

  if(argc == 2 && string(argv[1]) == "-d"){
    sudoku.debug = true;
    sudoku.info = true;
  }

sudoku.getProblem();
sudoku.printBoard();

cout<<"calling solver"<<endl;

cout<<boolalpha<<sudoku.solver()<<endl;

cout<<"returned form solver"<<endl;
sudoku.printBoard();

cout<<boolalpha<<sudoku.check()<<endl;

return 0;
}
