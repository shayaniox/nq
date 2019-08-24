#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
  int N;
  int **board;
} chessboard;

chessboard create_chessboard(int N){
  chessboard cb = {N, prepare_board(N)};
  return cb;
}

int main(int argc, char *argv[])
{
  chessboard cb = create_chessboard(4);
  printf("%d\n", cb.N);
  printf("%d\n", cb.board[0][1]);
}
