#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float ex0(float y, float yd)
{

  float __attribute__((annotate("scalar(range(-50, 50))"))) yc = 0.0f;
  float __attribute__((annotate("scalar(range(-2000, 2000))"))) u = 0.0f;
  float __attribute__((annotate("scalar(range(-2, 2))"))) xc0 = 0.0f;
  float __attribute__((annotate("scalar(range(-4, 4))"))) xc1 = 0.0f;
  float i = 0.0f;
  float __attribute__((annotate("scalar(range(-4, 4))"))) e = 1.0f;
  int tmp = e > 0.01f;
  float v = y - yd;
  float __attribute__((annotate("scalar(range(-4, 4))"))) pre_abs = 0.0f;
  float __attribute__((annotate("target('tmp') scalar(range(-50, 50))"))) tmp_1;
  if (v < -1.0f) {
    tmp_1 = -1.0f;
  } else if (1.0f < v) {
    tmp_1 = 1.0f;
  } else {
    tmp_1 = v;
  }
  while (tmp) {
    yc = tmp_1;

    u = (564.48f * xc0) + (-1280.0f * yc);

    xc0 = (0.499f * xc0) + (-0.05f * xc1 + yc);
    xc1 = (0.01f * xc0) + (xc1);
    i = i + 1.0f;
    pre_abs = yc - xc1;
    if (pre_abs < 0) {
      e = -pre_abs;
    } else {
      e = pre_abs;
    }
    tmp = e > 0.01f;
  }
  return xc1;
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 2;
  float __attribute__((annotate("target('main') scalar(range(0, 50))"))) y[len];
  float __attribute__((annotate("scalar(range(0, 50))"))) yd[len];

  float res[len];
  for (int i = 0; i < len; ++i) {

    y[i] = arr[i * 2];
    yd[i] = arr[i * 2 + 1];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(y[j], yd[j]);
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
