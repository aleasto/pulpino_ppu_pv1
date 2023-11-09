#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float __attribute__((annotate("scalar()"))) PI = 3.1415926535897931;

float _fmod(float x, float y)
{
  // precond: y != 0, y > 0
  if (x > 0) {
    while (x >= y) {
      x -= y;
    }
  } else {
    while (x <= -y) {
      x += y;
    }
  }
  return x;
}

float _sin(float f)
{
  float __attribute__((annotate("scalar(range(-3.142,3.142))"))) mod = _fmod(f, PI);
  float __attribute__((annotate("scalar(range(-1.571,1.571))"))) x;
  if (mod > PI/2)
    x = PI - mod;
  else if (mod < -PI/2)
    x = -PI - mod;
  else
    x = mod;
  return x - (x*x*x)/6 + (x*x*x*x*x)/120;
}


float ex0(float radius, float theta)
{
  float __attribute__((annotate("scalar(range(-10, 10))"))) radiant = theta * (PI / 180.0f);
  float __attribute__((annotate("scalar(range(-1, 1))"))) c = _sin(radiant);
  return radius * c;
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 2;
  float __attribute__((annotate("target('main') scalar(range(1, 10))")))
  radius[len];
  float __attribute__((annotate("scalar(range(0, 360))"))) theta[len];

  float res[len];
  for (int i = 0; i < len; ++i) {

    radius[i] = arr[i * 2];
    theta[i] = arr[i * 2 + 1];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(radius[j], theta[j]);
  }

#ifndef NO_TIMER
  stop_timer();
  printf("TIME: %d\n", get_time());
#endif

  printf("Values Begin\n");
  for (int j = 0; j < len; ++j) {
    printf("%f\n", res[j]);
  }
  printf("Values End\n");
  return 0;
}
