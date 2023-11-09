#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float ex0(float v, float w, float r)
{
  return ((3.0f + (2.0f / (r * r))) -
          (((0.125f * (3.0f - (2.0f * v))) * (((w * w) * r) * r)) / (1.0f - v))) -
         4.5f;
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 3;
  float __attribute__((annotate("target('main') scalar(range(-5, 0) final)")))
  v[len];
  float __attribute__((annotate("scalar(range(0, 1) final)"))) w[len];
  float __attribute__((annotate("scalar(range(3.8, 7.8) final)"))) e[len];

  float res[len];

  for (int i = 0; i < len; ++i) {
    v[i] = arr[i * 3];
    w[i] = arr[i * 3 + 1];
    e[i] = arr[i * 3 + 2];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(v[j], w[j], e[j]);
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