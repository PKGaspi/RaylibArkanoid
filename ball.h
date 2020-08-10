#include <raylib.h>

struct ball {
  struct Vector2 *pos;
  struct Vector2 *dir;
  float radious;
  Color color;
};

struct ball *ball_create(int x, int y, float radious, Color color);

void ball_move(struct ball *b, float delta);

void ball_draw(struct ball *b);

void ball_free(struct ball *b);