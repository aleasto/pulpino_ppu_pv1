#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif


float ex0(float x1, float x2)
{
  float __attribute__((annotate("scalar()"))) t = (((3.0f * x1) * x1) + (2.0f * x2)) - x1;
  float __attribute__((annotate("scalar()"))) t_42_ = (((3.0f * x1) * x1) - (2.0f * x2)) - x1;
  float __attribute__((annotate("scalar()"))) d = (x1 * x1) + 1.0f;
  float __attribute__((annotate("scalar()"))) s = t / d;
  float __attribute__((annotate("scalar()"))) s_42_ = t_42_ / d;
  return x1 + (((((((((2.0f * x1) * s) * (s - 3.0f)) +
                    ((x1 * x1) * ((4.0f * s) - 6.0f))) *
                   d) +
                  (((3.0f * x1) * x1) * s)) +
                 ((x1 * x1) * x1)) +
                x1) +
               (3.0f * s_42_));
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 2;
  float __attribute__((annotate("target('main') scalar(range(-5, 5))")))
  x1[len];
  float __attribute__((annotate("scalar(range(-20, 5))"))) x2[len];

  float res[len];

  for (int i = 0; i < len; ++i) {
    x1[i] = arr[i * 2];
    x2[i] = arr[i * 2 + 1];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(x1[j], x2[j]);
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