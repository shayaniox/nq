#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define N 4
#define SYMBOL 1
#define WAITING 0
#define PRINTABLE true


void print_board(int **board, bool up){
  if(up){
    printf("\033[%dA", N);
  }
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
  int **indexes = malloc(N * sizeof(int*));

  // Create array
  for (int i=0; i < N; i++)
  {
    indexes[i] = values + i * N;

  }
  // Fill the board with 0
  for (int i=0; i < N; i++)
  {
    for (int j=0; j < N; j++)
    {
      indexes[i][j] = 0;
    }
  }

  return indexes;
}


bool is_safe(int **board, int row, int column){

  int r, c;

  // Check vertically
  for (r=0; r < row; r++){
    if (board[r][column] != 0){
      return false;
    }
  }

  // Check diagonally to left
  for (r=row, c=column; (r >= 0) && (N - 1 >= c); r--, c++){
    if (board[r][c] != 0){
      return false;
    }
  }

  // Check diagonally to right
  for (r=row, c=column; (r >= 0) && (c >= 0); r--, c--){
    if (board[r][c] != 0){
      return false;
    }
  }
  return true;
}


int solve(int **board, int row){

  if(row >= N){
    return true;
  }

  for(int i = 0; i < N; i++){
    if(is_safe(board, row, i)){
      board[row][i] = SYMBOL;
      if(PRINTABLE) {print_board(board, true); sleep(WAITING);}

      if(solve(board, row + 1)){
        return true;
      }

      board[row][i] = 0;
      if(PRINTABLE) {print_board(board, true); sleep(WAITING);}
    }
  }
  return false;
}


// FIXME: Uncomment when `chessboard` type created
//void handle_input(int argc, char **argv){
//  if(argc < 2){
//    printf("Enter N as dimension\n");
//    exit(1);
//  }
//  if(atoi(argv[1]) == 0){
//    printf("Either N dimension type is invalid or is zero valued");
//    exit(1);
//  }
//}


int main(int argc, char **argv)
{
  system("clear");
  int **arr = prepare_board();

  if(solve(arr, 0)){
    success();
    print_board(arr, PRINTABLE);
  }
  else{
    fail();
    printf("No solution found!!!\n");
  }
  noc();
}
