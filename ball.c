#include "ball.h"
#include "common.h"
#include <stdlib.h>

const float BALL_MOVEMENT_SPEED = 200;

struct ball *ball_create(int x, int y, float radious, Color color) {

  struct ball *b = malloc(sizeof(struct ball));
  if (!b) return NULL;

  struct Vector2 *pos = malloc(sizeof(struct Vector2));
  pos -> x = x;
  pos -> y = y;

  struct Vector2 *dir = malloc(sizeof(struct Vector2));

  b -> pos = pos;
  b -> dir = dir;
  b -> radious = radious;
  b -> color = color;

  return b;

}

void ball_move(struct ball *b, float delta) {

  struct Vector2 *norm_dir = malloc(sizeof(struct Vector2));
  norm_dir -> x = b -> dir -> x;
  norm_dir -> y = b -> dir -> y;
  vector2_normalize(norm_dir);

  b -> pos -> x += norm_dir -> x * BALL_MOVEMENT_SPEED * delta;
  b -> pos -> y += norm_dir -> y * BALL_MOVEMENT_SPEED * delta;

  free(norm_dir);

}

void ball_draw(struct ball *b) {

  DrawCircleV(*b -> pos, b -> radious, b -> color);

}

void ball_free(struct ball *b) {

  free(b -> pos);
  free(b);

}
