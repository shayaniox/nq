#include <stdio.h>
#define N 64
#define chessboard "-----------------\n"  \
  "| %c |   |   |   |\n" \
  "-----------------\n"  \
  "|   |   |   |   | \n"  \
  "-----------------\n"  \
  "|   |   |   |   | \n"  \
  "-----------------\n"  \
  "|   |   |   |   | \n"  \
  "-----------------\n"

void success()
{
  printf("\033[36m");
}


void noc()
{
  printf("\033[0m");
}


void solve(){

}

int main()
{
  char rows[N][N];

  success();
  printf(chessboard, N);
  noc();
}
