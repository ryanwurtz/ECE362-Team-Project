#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "oled_display.c" //spi

#define GRID_SIZE 10
#define BLOCK_SIZE 3
#define MAX_BLOCKS 19

void update_score_display(int score, int high_score); //defining function from oled_display

//the grid. a digital frontier. I tried to picture clusters of information as they moved through the computer. What did they look like? Ships? Motorcycles?
int grid[GRID_SIZE][GRID_SIZE] = {0};
int score = 0;
int high_score = 0;  // 👈 NEW: track the highest score

int blocks[MAX_BLOCKS][BLOCK_SIZE][BLOCK_SIZE] = { //da predefined blocks
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},  // Horizontal line
    {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}},  // Vertical line
    {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},  // 2x2 square + extra cell
    {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},  // T-shape
    {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}},  // T-shape (alt)
    {{1, 0, 0}, {1, 0, 0}, {1, 1, 0}},  // L-shape
    {{0, 0, 1}, {0, 0, 1}, {0, 1, 1}},  // Reverse L
    {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},  // Z-shape
    {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},  // S-shape
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},  // Single block
    {{1, 1, 0}, {0, 0, 0}, {0, 0, 0}},  // 2x1 block
    {{1, 0, 0}, {1, 0, 0}, {0, 0, 0}},  // 2x1 vertical
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},  // 3x1 horizontal
    {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}},  // 3x1 vertical
    {{0, 0, 1}, {0, 0, 1}, {0, 1, 1}},  // Corner block
    {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},  // 2x2 square
    {{1, 0, 0}, {1, 1, 0}, {1, 0, 0}},  // T-shape tall
    {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},  // Diagonal zigzag
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}   // Single block
};

//stores indices of the 3 current blocks for player to choose
int current_choices[3] = {-1, -1, -1};
int used_choices[3] = {0, 0, 0};

//randomly makes 3 new blocks
void generate_choices() {
    for (int i = 0; i < 3; i++) {
        current_choices[i] = rand() % MAX_BLOCKS;
        used_choices[i] = 0;
    }
}

void print_grid() { //Print the current game grid and score
    printf("Score: %d | High Score: %d\n", score, high_score);  // 👈 UPDATED
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int can_place_block(int block[3][3], int x, int y) { //check if a block can be placed at (row, col)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (block[i][j] == 1) {
                //check if out of bounds
                if (x + i >= GRID_SIZE || y + j >= GRID_SIZE || grid[x + i][y + j] == 1)
                    return 0;
            }
        }
    }
    return 1;
}

//checks if any of the 3 current blocks has at least one valid placement
int any_valid_placement_exists() {
    for (int i = 0; i < 3; i++) {
        if (used_choices[i]) continue;
        for (int x = 0; x <= GRID_SIZE - BLOCK_SIZE; x++) {
            for (int y = 0; y <= GRID_SIZE - BLOCK_SIZE; y++) {
                if (can_place_block(blocks[current_choices[i]], x, y)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//actually place a block
void place_block(int block[3][3], int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (block[i][j] == 1)
                grid[x + i][y + j] = 1;
        }
    }
}

//clear rows or columns and update score
int clear_lines() {
    int lines_cleared = 0;
    for (int i = 0; i < GRID_SIZE; i++) { //check rows
        int full = 1;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = 0;
            }
            lines_cleared++;
        }
    }
    for (int j = 0; j < GRID_SIZE; j++) { //check columns
        int full = 1;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[i][j] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int i = 0; i < GRID_SIZE; i++) {
                grid[i][j] = 0;
            }
            lines_cleared++;
        }
    }
    score += lines_cleared; //update score based on the number of lines cleared
    if (score > high_score) {// 👈 NEW: update high score
        high_score = score;
    }
    update_score_display(score, high_score); //calling the function from oled_display.c
    return lines_cleared;
}

void print_block(int block[3][3]) { //print a block to console
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", block[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int all_used() { //check if all blocks are used
    return used_choices[0] && used_choices[1] && used_choices[2];
}

int main() {
    srand(time(NULL)); //random blocks
    generate_choices(); //make block choices
    while (1) {
        print_grid();

        if (all_used()) {
            printf("New blocks made!\n");
            generate_choices(); //refresh if used
        }

        if (!any_valid_placement_exists()) {
            printf("Game over! Sorry ¯_(ツ)_/¯.\n");
            break;
        }

        printf("Blocks to choose from:\n"); //display blocks to use
        for (int i = 0; i < 3; i++) {
            if (!used_choices[i]) {
                printf("Block choice %d (index %d):\n", i, current_choices[i]);
                print_block(blocks[current_choices[i]]);
            } else {
                printf("Block choice %d: (used)\n", i);
            }
        }

        int choice, x, y; //input
        printf("Choose a block index (0, 1, or 2) or -1 to quit: ");
        if (scanf("%d", &choice) != 1 || (choice >= 0 && choice < 3 && used_choices[choice])) {
            printf("Invalid or already used choice. Try again brudda.\n");
            while(getchar() != '\n');
            continue;
        }
        if (choice < 0) break;

        printf("Enter top-left position to place the block (row col): "); //placement location
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Wrong format dude. Please enter two integers (row col).\n");
            while(getchar() != '\n');
            continue;
        }

        if (can_place_block(blocks[current_choices[choice]], x, y)) {
            place_block(blocks[current_choices[choice]], x, y);
            used_choices[choice] = 1;
            clear_lines();
        } else {
            printf("Invalid placement big dawg. Try again.\n");
        }
    }

    printf("Game ended. Final grid:\n");
    print_grid();
    return 0;
}