#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define N 4
#define SYMBOL 1

typedef enum {OK, EOR} errors;


void print_board(int board[N][N], bool first_print){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}


void success()
{
  printf("\033[36m");
}

void fail()
{
  printf("\033[31m");
}

void noc()
{
  printf("\033[0m");
}


int **prepare_board(){
  int *values = calloc(N * N, sizeof(int));
  int **indexs = malloc(N * sizeof(int*));

  // Create array
  for (int i=0; i < N; i++)
  {
    indexs[i] = values + i * N;

  }
  // Fill the board with 0
  for (int i=0; i < N; i++)
  {
    for (int j=0; j < N; j++)
    {
      indexs[i][j] = 0;
    }
  }

  return indexs;
}


bool is_safe(int board[N][N], int row, int column){

  printf("\033[34mis_safe => row: %d, column: %d\033[0m\n", row, column);
  
  // Check vertically
  for (int r=0; r < row; r++){
    printf("\033[34mvertically => row: %d, column: %d\033[0m\n", row, column);
    if (board[r][column] != 0){
      return false;
    }
  }
  
  // Check diagonally to left
  for (int i=0; i < (row < column? row: column); i++){
    printf("\033[34mDL => row: %d, column: %d\033[0m\n", row, column);
    if (board[row - i][column - i] != 0){
      return false;
    }
  }

  // Check diagonally to right
  for (int i=0; i < (row < column? row: column); i++){
    printf("\033[34mDR => row: %d, column: %d\033[0m\n", row, column);
    if (board[row - i][column + i] != 0){
      return false;
    }
  }

  return true;
}


int solve(int board[N][N], int row){

  printf("\033[36mSolve, row: %d\n\033[0m", row);
  if(row > N){
    return true;
  }

  for(int i = 0; i < N; i++){
    if(is_safe(board, i, row)){
      print_board(board, false);
      printf("------------------\n");
      board[row][i] = SYMBOL;
      //sleep(3);

      if(solve(board, row + 1)){
        return true;
      }
      
      board[row][i] = 0;
    }
  }
  return false;
}


int main()
{
  bool first_print = true;
  //int **arr = prepare_board();
  int arr[N][N] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  };

  if(solve(arr, 0)){
    success();
    //print_board(arr, false);
  }
  else{
    fail();
    printf("No solution found");
  }
  noc();
}
