#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Define the game board size
#define WIDTH 80
#define HEIGHT 25

// Define the player colors
#define PLAYER1_COLOR 0x0F
#define PLAYER2_COLOR 0x0A

// Define the game states
#define STATE_RUNNING 0
#define STATE_GAME_OVER 1

// Define the player directions
#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

// Define the player structures
typedef struct {
    int x;
    int y;
    int direction;
    int length;
    int color;
} player;

// Define the game state structure
typedef struct {
    int state;
    player player1;
    player player2;
} game_state;

// Initialize the game state
game_state game;

// Initialize the game board
char board[WIDTH][HEIGHT];

// Initialize the player positions
void init_players() {
    game.player1.x = WIDTH / 2;
    game.player1.y = HEIGHT / 2;
    game.player1.direction = DIR_RIGHT;
    game.player1.length = 3;
    game.player1.color = PLAYER1_COLOR;

    game.player2.x = WIDTH / 2 - 1;
    game.player2.y = HEIGHT / 2;
    game.player2.direction = DIR_LEFT;
    game.player2.length = 3;
    game.player2.color = PLAYER2_COLOR;
}

// Initialize the game board
void init_board() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            board[i][j] = ' ';
        }
    }
}

// Draw the game board
void draw_board() {
    // Clear the screen
    system("cls");

    // Draw the border
    for (int i = 0; i < WIDTH; i++) {
        board[i][0] = '=';
        board[i][HEIGHT - 1] = '=';
    }
    for (int j = 0; j < HEIGHT; j++) {
        board[0][j] = '|';
        board[WIDTH - 1][j] = '|';
    }

    // Draw the players
    board[game.player1.x][game.player1.y] = game.player1.color;
    board[game.player2.x][game.player2.y] = game.player2.color;

    // Draw the board
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// Update the player positions
void update_players() {
    // Update player 1
    switch (game.player1.direction) {
        case DIR_UP:
            game.player1.y--;
            break;
        case DIR_DOWN:
            game.player1.y++;
            break;
        case DIR_LEFT:
            game.player1.x--;
            break;
        case DIR_RIGHT:
            game.player1.x++;
            break;
    }

    // Update player 2
    switch (game.player2.direction) {
        case DIR_UP:
            game.player2.y--;
            break;
        case DIR_DOWN:
            game.player2.y++;
            break;
        case DIR_LEFT:
            game.player2.x--;
            break;
        case DIR_RIGHT:
            game.player2.x++;
            break;
    }
}

// Check for collisions
int check_collisions() {
    // Check for collisions with the walls
    if (game.player1.x < 0 || game.player1.x >= WIDTH || game.player1.y < 0 || game.player1.y >= HEIGHT) {
        return 1;
    }
    if (game.player2.x < 0 || game.player2.x >= WIDTH || game.player2.y < 0 || game.player2.y >= HEIGHT) {
        return 1;
    }

    // Check for collisions with the other player
    if (game.player1.x == game.player2.x && game.player1.y == game.player2.y) {
        return 1;
    }

    // Check for collisions with the player's own tail
    for (int i = 0; i < game.player1.length; i++) {
        if (game.player1.x == board[i][game.player1.y]) {
            return 1;
        }
    }
    for (int i = 0; i < game.player2.length; i++) {
        if (game.player2.x == board[i][game.player2.y]) {
            return 1;
        }
    }

    // No collisions detected
    return 0;
}

// Update the game state
void update_game_state() {
    // Update the player positions
    update_players();

    // Check for collisions
    if (check_collisions()) {
        game.state = STATE_GAME_OVER;
    }
}

// Handle the player input
void handle_input() {
    // Get the player input
    int key = getch();

    // Update the player direction
    switch (key) {
        case 'w':
            game.player1.direction = DIR_UP;
            break;
        case 's':
            game.player1.direction = DIR_DOWN;
            break;
        case 'a':
            game.player1.direction = DIR_LEFT;
            break;
        case 'd':
            game.player1.direction = DIR_RIGHT;
            break;
    }
}

// Main game loop
int main() {
    // Initialize the game state
    init_players();
    init_board();

    // Game loop
    while (game.state == STATE_RUNNING) {
        // Handle the player input
        handle_input();

        // Update the game state
        update_game_state();

        // Draw the game board
        draw_board();
    }

    // Game over
    printf("Game over!\n");

    return 0;
}
