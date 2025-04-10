#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10
#define BLOCK_SIZE 3
#define MAX_BLOCKS 19

int grid[GRID_SIZE][GRID_SIZE] = {0};
int score = 0;

int blocks[MAX_BLOCKS][BLOCK_SIZE][BLOCK_SIZE] = {
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
    {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
    {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
    {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 0, 0}, {1, 1, 0}},
    {{0, 0, 1}, {0, 0, 1}, {0, 1, 1}},
    {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
    {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 1, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 0, 0}, {0, 0, 0}},
    {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
    {{0, 0, 1}, {0, 0, 1}, {0, 1, 1}},
    {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 1, 0}, {1, 0, 0}},
    {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

int current_choices[3] = {-1, -1, -1};
int used_choices[3] = {0, 0, 0};

void generate_choices() {
    for (int i = 0; i < 3; i++) {
        current_choices[i] = rand() % MAX_BLOCKS;
        used_choices[i] = 0;
    }
}

void print_grid() {
    printf("Score: %d\n", score);
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int can_place_block(int block[3][3], int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (block[i][j] == 1) {
                if (x + i >= GRID_SIZE || y + j >= GRID_SIZE || grid[x + i][y + j] == 1)
                    return 0;
            }
        }
    }
    return 1;
}

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

void place_block(int block[3][3], int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (block[i][j] == 1)
                grid[x + i][y + j] = 1;
        }
    }
}

int clear_lines() {
    int lines_cleared = 0;
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
                grid[i][j] = 0;
            }
            lines_cleared++;
        }
    }
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
                grid[i][j] = 0;
            }
            lines_cleared++;
        }
    }
    score += lines_cleared;
    return lines_cleared;
}

void print_block(int block[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", block[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int all_used() {
    return used_choices[0] && used_choices[1] && used_choices[2];
}

int main() {
    srand(time(NULL));
    generate_choices();

    while (1) {
        print_grid();

        if (all_used()) {
            printf("New blocks made!\n");
            generate_choices();
        }

        if (!any_valid_placement_exists()) {
            printf("Game over! Sorry ¯_(ツ)_/¯.\n");
            break;
        }

        printf("Blocks to choose from:\n");
        for (int i = 0; i < 3; i++) {
            if (!used_choices[i]) {
                printf("Block choice %d (index %d):\n", i, current_choices[i]);
                print_block(blocks[current_choices[i]]);
            } else {
                printf("Block choice %d: (used)\n", i);
            }
        }

        int choice, x, y;
        printf("Choose a block index (0, 1, or 2) or -1 to quit: ");
        if (scanf("%d", &choice) != 1 || (choice >= 0 && choice < 3 && used_choices[choice])) {
            printf("Invalid or already used choice. Try again brudda.\n");
            while(getchar() != '\n');
            continue;
        }
        if (choice < 0) break;

        printf("Enter top-left position to place the block (row col): ");
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