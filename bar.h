#include <raylib.h>

struct bar {
  Vector2 *pos;
  int size;
};

struct bar *bar_create(int x, int y, int size);

void bar_move(struct bar *b, struct Vector2 *dir, float delta);

void bar_draw(struct bar *b);

void bar_free(struct bar *b);