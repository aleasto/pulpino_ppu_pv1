#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float ex0(float v)
{
  const float p = 35000000.0f;
  const float a = 0.401f;
  const float b = 4.27e-05f;
  const float t = 300.0f;
  const float n = 1000.0f;
  const float k = 1.3806503e-23f;
  float pv = p * v;
  float __attribute__((annotate("scalar(range(401014, 3062257153))"))) ann =
      a * n * n / v;

  float pbb = p * b * b;

  float __attribute__((annotate("scalar(range(17123, 998543130625))")))
  annnbvv = a * n * n * n * b / v / v;
  float __attribute__((annotate("scalar(range(-995480895487, 35382589.0))")))
  ret = (pv + ann - pbb - annnbvv);
  return ret;
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]);
  float __attribute__((annotate("target('main') scalar(range(0, 1))"))) v[len];
  float res[len];
  for (int i = 0; i < len; ++i) {
    v[i] = arr[i];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(v[j]);
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