#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int N;
  //int **board;
} chessboard;

chessboard create_chessboard(int N){
  chessboard cb = {N};
  return cb;
}

int main(int argc, char *argv[])
{
  chessboard cb = create_chessboard(4);
  printf("%d\n", cb.N);
}
