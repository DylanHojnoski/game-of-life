#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct position {
    int row;
    int col;
};

void printGrid(int rows, int cols, int grid[][cols]) {
    for (int i = -1; i <= rows; i++) {
        for (int j = -1; j <= cols; j++) {
            if ((i == -1 && j == -1) || (i == rows && j == -1) || (i == -1 && j == cols) || (i == rows && j == cols)) {
                printf("+");
            }
            else if (i == -1 || i == rows) {
                printf("-");
            }
            else if (j == -1 || j == cols) {
                printf("|");
            }
            else if (grid[i][j] == 0) {
                printf(" ");
            }
            else {
                printf("▉");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void delay(int seconds) {
    int miliSeconds = seconds * 1000;
    clock_t startTime = clock();

    while (clock() < startTime + miliSeconds);
}

int main(int argc, char *argv[])
{
    int rows = 0;
    int cols = 0; 

    scanf("%d %d", &rows, &cols);

    int grid[rows][cols];
    int cur = 0;
    struct position curPos = {0, 0};

    // build grid
    for (int i = 0; i < rows*cols; i++) {

        scanf("%d", &cur);
        grid[curPos.row][curPos.col] = cur;

        if (curPos.col < cols - 1) {
            curPos.col++;
        }
        else {
            curPos.col = 0;
            curPos.row++;
        }
    }

    int (*prevGrid)[rows][cols] = &grid;
    int grid2[rows][cols];
    int (*newGrid)[rows][cols] = &grid2;
    int i = 1;

    while (i == 1) {
        printGrid(rows, cols, (*prevGrid));
        delay(100);
        curPos.row = 0;
        curPos.col = 0;
        int changed = 0;

        // go to each cell and see if it changes
        for (int i = 0; i < rows*cols; i++) {
            int neighbors = 0;

            // up
            if (curPos.row - 1 >= 0 && (*prevGrid)[curPos.row-1][curPos.col] != 0) {
                neighbors++;
            }
            // down
            if (curPos.row + 1 < rows && (*prevGrid)[curPos.row+1][curPos.col] != 0) {
                neighbors++;
            }
            // right
            if (curPos.col + 1 < cols  && (*prevGrid)[curPos.row][curPos.col+1] != 0) {
                neighbors++;
            }
            // left 
            if (curPos.col - 1 >= 0 && (*prevGrid)[curPos.row][curPos.col-1] != 0) {
                neighbors++;
            }
            // up  right
            if (curPos.row - 1 >= 0 && curPos.row + 1 < rows && (*prevGrid)[curPos.row-1][curPos.col+1] != 0) {
                neighbors++;
            }
            // up left 
            if (curPos.row - 1 >= 0 && curPos.row - 1 >= 0 && (*prevGrid)[curPos.row-1][curPos.col-1] != 0) {
                neighbors++;
            }
            // down right
            if (curPos.row + 1 < cols  && curPos.row + 1 < rows  && (*prevGrid)[curPos.row+1][curPos.col+1] != 0) {
                neighbors++;
            }
            // down left
            if (curPos.row + 1 >= 0 && curPos.row - 1 >= 0 && (*prevGrid)[curPos.row+1][curPos.col-1] != 0) {
                neighbors++;
            }

            if ((*prevGrid)[curPos.row][curPos.col] != 0) {
                if (neighbors < 2) {
                    (*newGrid)[curPos.row][curPos.col] = 0;
                }
                else if (neighbors == 2 || neighbors == 3) {
                    (*newGrid)[curPos.row][curPos.col] = 1;
                }
                else {
                    (*newGrid)[curPos.row][curPos.col] = 0;
                }
            }
            else {
                if (neighbors == 3) {
                    (*newGrid)[curPos.row][curPos.col] = 1;
                }
                else {
                    (*newGrid)[curPos.row][curPos.col] = 0;
                }
            }

            if ((*prevGrid)[curPos.row][curPos.col] != (*newGrid)[curPos.row][curPos.col]) {
                changed = 1;
            }

            if (curPos.col < cols - 1) {
                curPos.col++;
            }
            else {
                curPos.col = 0;
                curPos.row++;
            }
        }

        // assign the new grid to be the previous grid
        int (*temp)[rows][cols] = prevGrid;
        prevGrid = newGrid;
        newGrid = temp;

        // if nothing changed then break
        if (changed == 0) {
            break;
        }
    }
}
