#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10
#define NUM_BLOCKS 3

int grid[GRID_SIZE][GRID_SIZE] = {0};

int blocks[NUM_BLOCKS][3][3] = {
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}, // 3x1 block
    {{1, 1}, {1, 1}},                 // 2x2 block
    {{1, 0}, {1, 0}, {1, 0}}           // 3x1 vertical block
};

void print_grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int can_place_block(int block[3][3], int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (block[i][j] == 1) {
                if (x + i >= GRID_SIZE || y + j >= GRID_SIZE || grid[x + i][y + j] == 1)
                    return 0; 
            }
        }
    }
    return 1;
}

// Function to place a block
void place_block(int block[3][3], int x, int y, int size) {
    if (can_place_block(block, x, y, size)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (block[i][j] == 1)
                    grid[x + i][y + j] = 1;
            }
        }
    }
}

// Function to check and clear full lines
void clear_lines() {
    // Check rows
    for (int i = 0; i < GRID_SIZE; i++) {
        int full = 1;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = 0; // Clear row
            }
        }
    }
    // Check columns
    for (int j = 0; j < GRID_SIZE; j++) {
        int full = 1;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[i][j] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int i = 0; i < GRID_SIZE; i++) {
                grid[i][j] = 0; // Clear column
            }
        }
    }
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < 5; i++) { 
        int block_idx = rand() % NUM_BLOCKS;
        int x = rand() % (GRID_SIZE - 2);
        int y = rand() % (GRID_SIZE - 2);
        place_block(blocks[block_idx], x, y, 3);
        clear_lines();
        print_grid();
    }
    return 0;
}
