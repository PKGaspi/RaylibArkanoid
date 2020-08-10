#include "raylib.h"
#include "bar.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    struct bar *bar = bar_create(100, 400, 30);
    struct Vector2 bar_movement, ball_movement;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        bar_movement.x = 0;
        bar_movement.y = 0;

        if (IsKeyDown(KEY_LEFT)) bar_movement.x -= 1;
        if (IsKeyDown(KEY_RIGHT)) bar_movement.x += 1;

        bar_move(bar, &bar_movement, GetFrameTime());

        if (bar -> pos -> x - bar -> size / 2 < 0) bar -> pos -> x = bar -> size / 2; 
        else if (bar -> pos -> x + bar -> size / 2 > SCREEN_WIDTH) bar -> pos -> x = SCREEN_WIDTH - bar -> size / 2; 
        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

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