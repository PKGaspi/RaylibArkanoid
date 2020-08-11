#include <raylib.h>
#include "bar.h"
#include "ball.h"
#include "brick.h"
#include "common.h"

#define BACKGROUND_COLOR (Color){255, 255, 204, 255}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    const int N_BRICK_ROWS = 3;
    const int N_BRICK_COLUMNS = 16;
    const int BRICK_SEPARATION = 3;
    const int BRICK_WIDTH = 30;
    const int BRICK_HEIGHT = 10;
    const int EXTRA_HEIGHT = 200;

    const int SCREEN_WIDTH = N_BRICK_COLUMNS * (BRICK_WIDTH + BRICK_SEPARATION) + BRICK_SEPARATION;
    const int SCREEN_HEIGHT = N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION) + BRICK_SEPARATION + EXTRA_HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid");

    struct bar *bar = bar_create(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30, 50, 2, BLUE);
    struct ball *ball = ball_create(30, 30, 4, DARKPURPLE);

    // Init bricks.
    struct brick *bricks[N_BRICK_ROWS * N_BRICK_COLUMNS];
    int i, j;
    for (i = 0; i < N_BRICK_ROWS; i++) {
        for (j = 0; j < N_BRICK_COLUMNS; j++) {
            bricks[i + j * N_BRICK_ROWS] = brick_create(j * (BRICK_WIDTH + BRICK_SEPARATION) + BRICK_SEPARATION, i * (BRICK_HEIGHT + BRICK_SEPARATION) + BRICK_SEPARATION, BRICK_WIDTH, BRICK_HEIGHT, min(2, i));
        }
    }

    //struct brick *brick = brick_create(1, 1, 30, 10, 2);
    struct Vector2 bar_movement, ball_movement;

    ball_movement.x = 1;
    ball_movement.y = 1;

    ball -> dir = &ball_movement;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        //
        // --- Bar movement.
        bar_movement.x = 0;
        bar_movement.y = 0;

        if (IsKeyDown(KEY_LEFT)) bar_movement.x -= 1;
        if (IsKeyDown(KEY_RIGHT)) bar_movement.x += 1;

        bar_move(bar, &bar_movement, delta);

        // Don't go past the edges of the screen.
        if (bar -> pos -> x - bar -> size / 2 < 0) bar -> pos -> x = bar -> size / 2; 
        else if (bar -> pos -> x + bar -> size / 2 > SCREEN_WIDTH) bar -> pos -> x = SCREEN_WIDTH - bar -> size / 2; 

        // --- Ball movement.
        ball_move(ball, delta);

        // Bounce on the edges of the screen.
        // Left wall.
        if (ball -> pos -> x - ball -> radious <= 0) {
            ball -> pos -> x = -(ball -> pos -> x - ball -> radious) + ball -> radious;
            ball -> dir -> x = -ball -> dir -> x;
        }
        // Right wall.
        else if (ball -> pos -> x + ball -> radious >= SCREEN_WIDTH) {
            ball -> pos -> x = SCREEN_WIDTH - (ball -> pos -> x + ball -> radious - SCREEN_WIDTH) - ball -> radious;
            ball -> dir -> x = -ball -> dir -> x;
        }
        // Ceiling.
        if (ball -> pos -> y - ball -> radious <= 0) {
            ball -> pos -> y = -(ball -> pos -> y - ball -> radious) + ball -> radious;
            ball -> dir -> y = -ball -> dir -> y;
        }
        // Flor.
        //else if (ball -> pos -> y + ball -> radious >= SCREEN_HEIGHT) {
        //    ball -> pos -> y = SCREEN_HEIGHT - (ball -> pos -> y + ball -> radious - SCREEN_HEIGHT) - ball -> radious;
        //    ball -> dir -> y = -ball -> dir -> y;
        //}

        // Check collision between bar and ball.
        if (bar -> pos -> y >= ball -> pos -> y - ball -> radious &&
            bar -> pos -> y <= ball -> pos -> y + ball -> radious &&
            bar -> pos -> x - bar -> size / 2 <= ball -> pos -> x &&
            bar -> pos -> x + bar -> size / 2 >= ball -> pos -> x) {

            // TODO: Make the ball bounce in a different dir deppending on the x of the bar.
            ball -> pos -> y = bar -> pos -> y - (ball -> pos -> y + ball -> radious - bar -> pos -> y) - ball -> radious;
            ball -> dir -> y = -ball -> dir -> y;
        
        }

        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BACKGROUND_COLOR);

            for (i = 0; i < N_BRICK_ROWS * N_BRICK_COLUMNS; i++) {
                brick_draw(bricks[i]);
            }
            
            ball_draw(ball);
            bar_draw(bar);
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}