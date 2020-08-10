#include <raylib.h>

struct bar {
  struct Vector2 *pos;
  int size;
  float thick;
  Color color;
};

struct bar *bar_create(int x, int y, int size, float thick, Color color);

void bar_move(struct bar *b, struct Vector2 *dir, float delta);

void bar_draw(struct bar *b);

void bar_free(struct bar *b);