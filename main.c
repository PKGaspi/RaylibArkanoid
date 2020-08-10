#include "raylib.h"
#include "bar.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

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