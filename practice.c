#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_safe(int index[2][2], int row, int column){

  // Check horizontally
    for (int c=0; c < column; c++){
        if (index[row][c] != 0){
        return false;
        }
    }

  // Check vertically
    for (int r=0; r < row; r++){
        if (index[r][column] != 0){
            return false;
        }
    }

  // Check diagonally
    for (int i=0; i < (row? row < column: column); i++){
    printf("%d, %d\n", (row - i), column - i);
    if (index[row - i][column - i] != 0){
        return false;
    }
    }

    return true;
}

int main(void)
{
    int row = 0;
    int col = 1;
    printf("%d\n", row? row<col: col);
}
