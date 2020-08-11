#include <raylib.h>
#include "bar.h"
#include "ball.h"
#include "brick.h"
#include "common.h"
#include <stdlib.h>

#define BACKGROUND_COLOR (Color){255, 255, 204, 255}

int ball_brick_collide(struct ball *ball, struct brick *brick);

int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------

  const char *PAUSE_TEXT = "Game paused";
  const char *LIVES_TEXT = "Lives: %i";
  const char *GAME_OVER_TEXT = "Game over";
  const char *VICTORY_TEXT = "Congratulations! You won!";
  const char *RETRY_TEXT = "Press Enter to start a new game";
  const int FONT_SIZE = 20;

  const int N_BRICK_ROWS = 3;
  const int N_BRICK_COLUMNS = 16;
  const int BRICK_SEPARATION = 3;
  const int BRICK_WIDTH = 30;
  const int BRICK_HEIGHT = 10;
  const int EXTRA_HEIGHT = 200;

  const int SCREEN_WIDTH = N_BRICK_COLUMNS * (BRICK_WIDTH + BRICK_SEPARATION) + BRICK_SEPARATION;
  const int SCREEN_HEIGHT = N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION) + BRICK_SEPARATION + EXTRA_HEIGHT;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid");

  int pause = 0;
  int game_over = -1;
  int bricks_destroyed = 0;
  int lives = 3;
  int moveable_ball = 0;

  int i, j;
	  
  struct bar *bar = NULL;
  struct ball *ball = NULL;
  struct brick *bricks[N_BRICK_ROWS * N_BRICK_COLUMNS];

  // Init bricks.
  for (i = 0; i < N_BRICK_ROWS; i++) {
    for (j = 0; j < N_BRICK_COLUMNS; j++) {
      bricks[i + j * N_BRICK_ROWS] = NULL;
    }
  }
  


  //struct brick *brick = brick_create(1, 1, 30, 10, 2);
  struct Vector2 bar_movement;

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      //----------------------------------------------------------------------------------
      //
      // --- Bar movement.
      if (IsKeyPressed(KEY_P) && !game_over) pause = !pause;

      if (!game_over && !pause) {

	float delta = GetFrameTime();

	bar_movement.x = 0;
	bar_movement.y = 0;

	if (IsKeyDown(KEY_LEFT)) bar_movement.x -= 1;
	if (IsKeyDown(KEY_RIGHT)) bar_movement.x += 1;

	bar_move(bar, &bar_movement, delta);

	// Don't go past the edges of the screen.
	if (bar -> pos -> x - bar -> size / 2 < 0) bar -> pos -> x = bar -> size / 2; 
	else if (bar -> pos -> x + bar -> size / 2 > SCREEN_WIDTH) bar -> pos -> x = SCREEN_WIDTH - bar -> size / 2; 

	// --- Ball movement.
	if (moveable_ball) ball_move(ball, delta);
	else {
	  ball -> pos -> x = bar -> pos -> x;
	  ball -> pos -> y = bar -> pos -> y - 10;

	  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
	    // Launch the ball.
	    moveable_ball = 1;
	    ball -> dir -> x = GetRandomValue(-2, 2);
	    ball -> dir -> y = -1;
	  }
	}

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
	else if (ball -> pos -> y + ball -> radious >= SCREEN_HEIGHT) {
	  //ball -> pos -> y = SCREEN_HEIGHT - (ball -> pos -> y + ball -> radious - SCREEN_HEIGHT) - ball -> radious;
	  //ball -> dir -> y = -ball -> dir -> y;
	  lives--;
	  moveable_ball = 0;
	  if (lives <= 0) {
	    game_over = 1;
	  }
	}

	// Check collision between bar and ball.
	if (bar -> pos -> y >= ball -> pos -> y - ball -> radious &&
	    bar -> pos -> y <= ball -> pos -> y + ball -> radious &&
	    bar -> pos -> x - bar -> size / 2 <= ball -> pos -> x &&
	    bar -> pos -> x + bar -> size / 2 >= ball -> pos -> x) {

	  // TODO: Make the ball bounce in a different dir deppending on the x of the bar.
	  ball -> pos -> y = bar -> pos -> y - (ball -> pos -> y + ball -> radious - bar -> pos -> y) - ball -> radious;
	  ball -> dir -> y = -ball -> dir -> y;

	}

	// Check collision between ball and bricks.
        
	for (i = 0; i < N_BRICK_ROWS * N_BRICK_COLUMNS; i++) {
	  if (bricks[i] && ball_brick_collide(ball, bricks[i])) {
	    brick_hit(bricks[i]);
	    if (bricks[i] -> hardness < 0) {
	      brick_free(bricks[i]);
	      bricks[i] = NULL;
	    }
	    break;
	  }
	}
      }           
      else if (!pause) {
	if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
	  
	  // Sart game.
	  game_over = 0;
	  lives = 3;

	  bar = bar_create(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30, 50, 2, BLUE);
	  ball = ball_create(bar -> pos -> x, bar -> pos -> y - 10, 4, DARKPURPLE);

	  // Init bricks.
	  for (i = 0; i < N_BRICK_ROWS; i++) {
	    for (j = 0; j < N_BRICK_COLUMNS; j++) {
	      bricks[i + j * N_BRICK_ROWS] = brick_create(j * (BRICK_WIDTH + BRICK_SEPARATION) + BRICK_SEPARATION, i * (BRICK_HEIGHT + BRICK_SEPARATION) + BRICK_SEPARATION, BRICK_WIDTH, BRICK_HEIGHT, min(2, i));
	    }
	  }
	  
	}
      } 

      //----------------------------------------------------------------------------------


      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(BACKGROUND_COLOR);

      for (i = 0; i < N_BRICK_ROWS * N_BRICK_COLUMNS; i++) {
	if (bricks[i]) brick_draw(bricks[i]);
      }

      if (ball) ball_draw(ball);
      if (bar) bar_draw(bar);
      //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

      // Texts.

      // Pause.
      if (pause) DrawText(PAUSE_TEXT, SCREEN_WIDTH / 2 - MeasureText(PAUSE_TEXT, FONT_SIZE) / 2, (SCREEN_HEIGHT - FONT_SIZE) / 2, FONT_SIZE, MAGENTA);

      // Points.
      if (game_over >= 0) {
	const char * lives_text = TextFormat(LIVES_TEXT, lives);
	DrawText(lives_text, SCREEN_WIDTH / 2 - MeasureText(lives_text, FONT_SIZE) / 2, N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION), FONT_SIZE, MAGENTA);  
      }
      // Game over or victory text.
      switch (game_over) {
      case 1: 
	DrawText(GAME_OVER_TEXT, SCREEN_WIDTH / 2 - MeasureText(GAME_OVER_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2 + N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION), FONT_SIZE, MAGENTA);
	break;
      case 2:
	DrawText(VICTORY_TEXT, SCREEN_WIDTH / 2 - MeasureText(VICTORY_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2 + N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION), FONT_SIZE, MAGENTA);
	break;
      }
      // New game text.
      if (game_over) {
	DrawText(RETRY_TEXT, SCREEN_WIDTH / 2 - MeasureText(RETRY_TEXT, FONT_SIZE) / 2, (FONT_SIZE + 2) * 2 + N_BRICK_ROWS * (BRICK_HEIGHT + BRICK_SEPARATION), FONT_SIZE, MAGENTA);    
      }
      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  
  if (ball) ball_free(ball);
  if (bar) bar_free(bar);
  for (i = 0; i < N_BRICK_COLUMNS * N_BRICK_ROWS; i++) {
    if (bricks[i]) brick_free(bricks[i]);
  }
  
  //--------------------------------------------------------------------------------------

  return 0;
}

int ball_brick_collide(struct ball *ball, struct brick *brick) {

  if (ball -> pos -> x >= brick -> pos -> x - brick -> size -> x &&
      ball -> pos -> x <= brick -> pos -> x + brick -> size -> x) {
    // Top face.
    if (ball -> pos -> y + ball -> radious >= brick -> pos -> y - brick -> size -> y &&
	ball -> pos -> y + ball -> radious <= brick -> pos -> y) {

      ball -> pos -> y = 2 * (brick -> pos -> y - brick -> size -> y) - ball -> pos -> y - ball -> radious * 2;
      ball -> dir -> y = -ball -> dir -> y;
      return 1;

    }
    // Bottom face.
    else if (ball -> pos -> y - ball -> radious <= brick -> pos -> y + brick -> size -> y &&
	     ball -> pos -> y - ball -> radious >= brick -> pos -> y) {

      ball -> pos -> y = 2 * (brick -> pos -> y + brick -> size -> y) - ball -> pos -> y + ball -> radious * 2;
      ball -> dir -> y = -ball -> dir -> y;
      return 1;

    }
  }

  else if (ball -> pos -> y >= brick -> pos -> y - brick -> size -> y &&
	   ball -> pos -> y <= brick -> pos -> y + brick -> size -> y) {
    // Left face.
    if (ball -> pos -> x + ball -> radious >= brick -> pos -> x - brick -> size -> x &&
        ball -> pos -> x + ball -> radious <= brick -> pos -> x) {

      ball -> pos -> x = 2 * (brick -> pos -> x - brick -> size -> x) - ball -> pos -> x - ball -> radious * 2;
      ball -> dir -> x = -ball -> dir -> x;
      return 1;

    }
    // Right face.
    else if (ball -> pos -> x - ball -> radious <= brick -> pos -> x + brick -> size -> x &&
	     ball -> pos -> x - ball -> radious >= brick -> pos -> x) {

      ball -> pos -> x = 2 * (brick -> pos -> x + brick -> size -> x) - ball -> pos -> x + ball -> radious * 2;
      ball -> dir -> x = -ball -> dir -> x;
      return 1;

    }
  }
  return 0;
}
