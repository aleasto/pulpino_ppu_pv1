#include <math.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float _sqrt(float n)
{
  // https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method
  float __attribute__((annotate("scalar()"))) x=n/2;
  while(1) {
    x=0.5*(x+(n/x));
    if(x*x >= n-0.1 && x*x <= n+0.1)
      break;
  }
  return x;
}

float ex0(float a, float b, float c) {
  float s = ((a + b) + c) / 2.0;
  return _sqrt((((s * (s - a)) * (s - b)) * (s - c)));
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 3;
  float __attribute__((annotate("target('main') scalar(range(-9, 9) final)")))
  a[len];
  float __attribute__((annotate("scalar(range(-9, -9) final)"))) b[len];
  float __attribute__((annotate("scalar(range(-9, 9) final)"))) c[len];

  float res[len];

  for (size_t i = 0; i < len; ++i) {
    a[i] = arr[i * 3];
    b[i] = arr[i * 3 + 1];
    c[i] = arr[i * 3 + 2];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(a[j], b[j], c[j]);
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