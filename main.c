#include <stdio.h>
#include <stdlib.h>
#include <time.h> //random number generator like rand() and srand()

#define GRID_SIZE 10 // Size of the game grid (10x10)
#define NUM_BLOCKS 3 // Number of predefined block types

int grid[GRID_SIZE][GRID_SIZE] = {0}; // Game grid initialized with zeros

// Example predefined blocks
int blocks[NUM_BLOCKS][3][3] = {
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}, // 3x1 horizontal block
    {{1, 1}, {1, 1}},                 // 2x2 square block
    {{1, 0}, {1, 0}, {1, 0}}           // 3x1 vertical block
};

// Function to print the current state of the game grid
void print_grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", grid[i][j]); // Print each cell
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a block can be placed at a given position
int can_place_block(int block[3][3], int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (block[i][j] == 1) { // Check only occupied cells of the block
                if (x + i >= GRID_SIZE || y + j >= GRID_SIZE || grid[x + i][y + j] == 1)
                    return 0; // Return false if out of bounds or space is occupied
            }
        }
    }
    return 1; // Block can be placed
}

// Function to place a block on the grid
void place_block(int block[3][3], int x, int y, int size) {
    if (can_place_block(block, x, y, size)) { // Ensure placement is valid
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (block[i][j] == 1)
                    grid[x + i][y + j] = 1; // Mark the occupied cells on the grid
            }
        }
    }
}

// Function to check and clear full rows and columns
void clear_lines() {
    // Check rows for completion
    for (int i = 0; i < GRID_SIZE; i++) {
        int full = 1;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                full = 0; // Row is not full
                break;
            }
        }
        if (full) { // Clear full row
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = 0;
            }
        }
    }
    // Check columns for completion
    for (int j = 0; j < GRID_SIZE; j++) {
        int full = 1;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[i][j] == 0) {
                full = 0; // Column is not full
                break;
            }
        }
        if (full) { // Clear full column
            for (int i = 0; i < GRID_SIZE; i++) {
                grid[i][j] = 0;
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator for block selection

    // Simulate placing 5 blocks randomly on the grid
    for (int i = 0; i < 5; i++) {
        int block_idx = rand() % NUM_BLOCKS; // Randomly select a block type
        int x = rand() % (GRID_SIZE - 2); // Random x position (adjusted for size)
        int y = rand() % (GRID_SIZE - 2); // Random y position (adjusted for size)
        
        place_block(blocks[block_idx], x, y, 3); // Attempt to place the block
        clear_lines(); // Check and clear full rows or columns
        print_grid(); // Print updated grid state
    }
    return 0;
}
