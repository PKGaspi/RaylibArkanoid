#include "stdlib.h"
#include <raylib.h>
#include "brick.h"
#include "common.h"

Color BRICK_COLOR_1 [3] = {GREEN, YELLOW, RED};
Color BRICK_COLOR_2 [3] = {LIME, GOLD, MAROON};
Color BRICK_OUTLINE_COLOR = BLACK;

struct brick *brick_create(int x, int y, int width, int height, int hardness) {

  struct brick *b = malloc(sizeof(struct brick));
  if (!b) return NULL;

  struct Vector2 *pos = malloc(sizeof(struct Vector2));
  pos -> x = x;
  pos -> y = y; 

  struct Vector2 *size = malloc(sizeof(struct Vector2));
  size -> x = width;
  size -> y = height;

  b -> pos = pos;
  b -> size = size;
  b -> hardness = hardness;

  return b;

}

void brick_hit(struct brick *b) {
  b -> hardness--;
}

void brick_draw(struct brick *b) {

  struct Vector2 v1;
  v1.x = b -> pos -> x;
  v1.y = b -> pos -> y;    
  struct Vector2 v2;
  v2.x = b -> pos -> x;
  v2.y = b -> pos -> y + b -> size -> y;    
  struct Vector2 v3;
  v3.x = b -> pos -> x + b -> size -> x;
  v3.y = b -> pos -> y;    
  struct Vector2 v4;
  v4.x = b -> pos -> x + b -> size -> x;
  v4.y = b -> pos -> y + b -> size -> y;    
  struct Vector2 v5;
  v5.x = b -> pos -> x + b -> size -> x / 2;
  v5.y = b -> pos -> y + b -> size -> y / 2;    

  DrawTriangle(v1, v2, v5, BRICK_COLOR_2[(int)max(b -> hardness, 0)]);
  DrawTriangle(v5, v4, v3, BRICK_COLOR_2[(int)max(b -> hardness, 0)]);
  DrawTriangle(v1, v5, v3, BRICK_COLOR_1[(int)max(b -> hardness, 0)]);
  DrawTriangle(v2, v4, v5, BRICK_COLOR_1[(int)max(b -> hardness, 0)]);

  DrawLineV(v1, v2, BRICK_OUTLINE_COLOR);
  DrawLineV(v1, v3, BRICK_OUTLINE_COLOR);
  DrawLineV(v2, v4, BRICK_OUTLINE_COLOR);
  DrawLineV(v3, v4, BRICK_OUTLINE_COLOR);
  DrawLineV(v1, v4, BRICK_OUTLINE_COLOR);
  DrawLineV(v2, v3, BRICK_OUTLINE_COLOR);

}

void brick_free(struct brick *b) {

  free(b -> pos);
  free(b -> size);
  free(b);

}