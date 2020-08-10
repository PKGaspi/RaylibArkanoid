#include "raylib.h"
#include "bar.h"
#include "ball.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 250;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid");

    struct bar *bar = bar_create(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30, 30);
    struct ball *ball = ball_create(30, 30, 20, VIOLET);
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
        if (ball -> pos -> x - ball -> radious <= 0) {
            ball -> pos -> x = -(ball -> pos -> x - ball -> radious) + ball -> radious;
            ball -> dir -> x = -ball -> dir -> x;
        }
        else if (ball -> pos -> x + ball -> radious >= SCREEN_WIDTH) {
            ball -> pos -> x = SCREEN_WIDTH - (ball -> pos -> x + ball -> radious - SCREEN_WIDTH) - ball -> radious;
            ball -> dir -> x = -ball -> dir -> x;
        }
        if (ball -> pos -> y - ball -> radious <= 0) {
            ball -> pos -> y = -(ball -> pos -> y - ball -> radious) + ball -> radious;
            ball -> dir -> y = -ball -> dir -> y;
        }
        else if (ball -> pos -> y + ball -> radious >= SCREEN_HEIGHT) {
            ball -> pos -> y = SCREEN_HEIGHT - (ball -> pos -> y + ball -> radious - SCREEN_HEIGHT) - ball -> radious;
            ball -> dir -> y = -ball -> dir -> y;
        }

        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

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