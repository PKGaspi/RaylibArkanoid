#include <raylib.h>

struct brick {
  struct Vector2 *pos;
  struct Vector2 *size;
  int hardness;
};

struct brick *brick_create(int x, int y, int width, int height, int hardness);

void brick_hit(struct brick *b);

void brick_draw(struct brick *b);

void brick_free(struct brick *b);