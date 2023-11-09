#include <stdio.h>
#define TRUE 1
#define FALSE 0
#include "data.h"

#ifndef NO_TIMER
#include <timer.h>
#endif

float __attribute__((annotate("scalar()"))) PI = 3.1415926535897931;

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

float _atan(float x)
{
  // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6010512/
  return 8*x/(3+_sqrt(25+(80*x*x)/3));
}

float ex0(float x, float y)
{
  float __attribute__((annotate("scalar(range(-3,3))"))) radiant = _atan((y / x));
  return radiant * (180.0f / PI);
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 2;
  float __attribute__((annotate("target('main') scalar(range(1, 100))")))
  x[len];
  float __attribute__((annotate("scalar(range(1, 100))"))) y[len];

  float res[len];
  for (int i = 0; i < len; ++i) {

    x[i] = arr[i * 2];
    y[i] = arr[i * 2 + 1];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(x[j], y[j]);
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
