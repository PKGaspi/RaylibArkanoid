#include <raylib.h>
#include "bar.h"
#include "common.h"
#include <stdlib.h>

const float BAR_MOVEMENT_SPEED = 350; // Pixels per second.

struct bar *bar_create(int x, int y, int size, Color color) {

  struct bar *b = malloc(sizeof(struct bar));
  if (!b) return NULL;

  struct Vector2 *v = malloc(sizeof(struct Vector2));
  v -> x = x;
  v -> y = y;

  b -> pos = v;
  b -> size = size;
  b -> color = color;

  return b;

}

void bar_move(struct bar *b, struct Vector2 *dir, float delta) {

  struct Vector2 *norm_dir = malloc(sizeof(struct Vector2));
  norm_dir -> x = dir -> x;
  norm_dir -> y = dir -> y;
  vector2_normalize(norm_dir);

  b -> pos -> x += norm_dir -> x * BAR_MOVEMENT_SPEED * delta;
  b -> pos -> y += norm_dir -> y * BAR_MOVEMENT_SPEED * delta;

  free(norm_dir);

}

void bar_draw(struct bar *b) {

  DrawLine(b -> pos -> x - b -> size / 2, b -> pos -> y, b -> pos -> x + b -> size / 2, b -> pos -> y, b -> color);

}

void bar_free(struct bar *b) {

  free(b -> pos);
  free(b);

}