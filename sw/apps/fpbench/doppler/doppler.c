#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float ex0(float u, float v, float T)
{
  float __attribute__((annotate(" target('x0') scalar()"))) t1 = 331.4f + (0.6f * T);
  return (-t1 * v) / ((t1 + u) * (t1 + u));
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 3;
  float
      __attribute__((annotate("target('main') scalar(range(-500, 500) final)")))
      u[len];
  float __attribute__((annotate("scalar(range(-20, 20000) final)"))) v[len];
  float __attribute__((annotate("scalar(range(-50, 50) final)"))) T[len];

  float res[len];

  for (int i = 0; i < len; ++i) {
    u[i] = arr[i * 3];
    v[i] = arr[i * 3 + 1];
    T[i] = arr[i * 3 + 2];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(u[j], v[j], T[j]);
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
