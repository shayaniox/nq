#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define SYMBOL    1
#define WAITING   0
#define PRINTABLE true


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


int **prepare_board(int n){
  int *values = calloc(n * n, sizeof(int));
  int **indexes = malloc(n * sizeof(int*));

  // Create array
  for (int i=0; i < n; i++)
  {
    indexes[i] = values + i * n;

  }
  // Fill the board with 0
  for (int i=0; i < n; i++)
  {
    for (int j=0; j < n; j++)
    {
      indexes[i][j] = 0;
    }
  }

  return indexes;
}


typedef struct {
  int n;
  int **board;
} chessboard;


chessboard create_chessboard(int n){
  chessboard cb = {n, prepare_board(n)};
  return cb;
}


void print_board(chessboard cb, bool up){
  if(up){
    printf("\033[%dA", cb.n);
  }
  for(int i = 0; i < cb.n; i++){
    for(int j = 0; j < cb.n; j++){
      printf("%d ", cb.board[i][j]);
    }
    printf("\n");
  }
}


bool is_safe(chessboard cb, int row, int column){

  int r, c;

  // Check vertically
  for (r=0; r < row; r++){
    if (cb.board[r][column] != 0){
      return false;
    }
  }

  // Check diagonally to left
  for (r=row, c=column; (r >= 0) && (cb.n - 1 >= c); r--, c++){
    if (cb.board[r][c] != 0){
      return false;
    }
  }

  // Check diagonally to right
  for (r=row, c=column; (r >= 0) && (c >= 0); r--, c--){
    if (cb.board[r][c] != 0){
      return false;
    }
  }
  return true;
}


int solve(chessboard cb, int row){

  if(row >= cb.n){
    return true;
  }

  for(int i = 0; i < cb.n; i++){
    if(is_safe(cb, row, i)){
      cb.board[row][i] = SYMBOL;
      if(PRINTABLE) {print_board(cb, true); sleep(WAITING);}

      if(solve(cb, row + 1)){
        return true;
      }

      cb.board[row][i] = 0;
      if(PRINTABLE) {print_board(cb, true); sleep(WAITING);}
    }
  }
  return false;
}


int handle_input(int argc, char **argv){
  if(argc < 2){
    printf("Enter N as dimension.\n");
    exit(1);
  }
  if(atoi(argv[1]) == 0){
    printf("Either N dimension type is invalid or is zero valued.\n");
    exit(1);
  }
  return atoi(argv[1]);
}


int main(int argc, char **argv)
{
  int n = handle_input(argc, argv);
  system("clear");
  chessboard cb = create_chessboard(n);

  if(solve(cb, 0)){
    success();
    print_board(cb, PRINTABLE);
  }
  else{
    fail();
    printf("No solution found!!!\n");
  }
  noc();
}
