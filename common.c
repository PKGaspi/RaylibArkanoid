#include "common.h"
#include <math.h>

float max(float a, float b) {
  if (a > b) return a;
  return b;
}
float min(float a, float b) {
  if (a < b) return a;
  return b;
}

float vector2_length(struct Vector2 *v) {

  return sqrt(v -> x * v -> x + v -> y * v -> y);

}
void vector2_normalize(struct Vector2 *v) {
  
  if (v -> x == 0 && v -> y == 0) return;

  float length = vector2_length(v);
  v -> x = v -> x / length;
  v -> y = v -> y / length;

}