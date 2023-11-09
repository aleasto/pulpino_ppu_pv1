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

float _cos(float f) {
    float __attribute__((annotate("scalar(range(-6.248,6.248))"))) mod = _fmod(f, 2*PI);
    float __attribute__((annotate("scalar(range(-3.142,3.142))"))) x;
    if (mod > PI) {
        x = mod - 2*PI;
    } else if (mod < -PI) {
        x = mod + 2*PI;
    } else {
        x = mod;
    }

    float __attribute__((annotate("scalar()"))) sign = 1.0;
    if (x < 0) {
        x = -x;
    }
    if (x > PI/2) {
        x = PI - x;
        sign = -1.0;
    }
    float t = 1.0f - (x*x)/2 + (x*x*x*x)/24;
    return sign * t;
}

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


float __attribute__((annotate("scalar(range(-1, 1))"))) ex0(float lat1, float lat2, float lon1, float lon2)
{
  float __attribute__((annotate("scalar()"))) dLon = lon2 - lon1;
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) s_lat1 = _sin(lat1);
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) c_lat1 = _cos(lat1);
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) s_lat2 = _sin(lat2);
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) c_lat2 = _cos(lat2);
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) s_dLon = _sin(dLon);
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) c_dLon = _cos(dLon);
  float __attribute__((annotate("scalar()"))) inner__atan = ((c_lat2 * s_dLon) / ((c_lat1 * s_lat2) - ((s_lat1 * c_lat2) * c_dLon)));
  float __attribute__((annotate("scalar()"))) tmp = _atan(inner__atan);
  return tmp;
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 4;
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) lat1[len];
  float __attribute__((annotate("scalar(range(-1, 1) final)"))) lat2[len];
  float __attribute__((annotate("scalar(range(-4, 4) final)"))) lon1[len];
  float __attribute__((annotate("scalar(range(-4, 4) final)"))) lon2[len];
  float __attribute__((annotate("scalar(range(-1, 1))"))) res[len];
  for (int i = 0; i < len; ++i) {

    lat1[i] = arr[i * 4];
    lat2[i] = arr[i * 4 + 1];
    lon1[i] = arr[i * 4 + 2];
    lon2[i] = arr[i * 4 + 3];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] = ex0(lat1[j], lat2[j], lon1[j], lon2[j]);
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
