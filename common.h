#include <raylib.h>

enum DIRECTION {
  DIR_OTHER,
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT
};

float max(float a, float b);
float min(float a, float b);

float vector2_length(struct Vector2 *v);
void vector2_normalize(struct Vector2 *v);