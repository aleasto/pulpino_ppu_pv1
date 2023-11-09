#include <math.h>
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

float ex0(float t, float resistance, float frequency, float inductance,
          float maxVoltage)
{
  float impedance_re = resistance;
  float __attribute__((annotate("scalar(range(-1, 4) final)"))) impedance_im = ((2.0f * PI) * frequency) * inductance;
  float __attribute__((annotate("scalar(range(-1, 2503) final)"))) denom = (impedance_re * impedance_re) + (impedance_im * impedance_im);
  float __attribute__((annotate("scalar()"))) re_tmp = (maxVoltage * impedance_re) ;
  float __attribute__((annotate("scalar()"))) im_tmp = (maxVoltage * impedance_im) ;
   im_tmp = -im_tmp;

  float __attribute__((annotate("scalar()"))) current_re = re_tmp / denom;
  float __attribute__((annotate("scalar()"))) current_im = im_tmp / denom;
  float __attribute__((annotate("scalar(range(-1, 11) final)"))) maxCurrent =
      _sqrt(((current_re * current_re) + (current_im * current_im)));


  float __attribute__((annotate("scalar(range(-1, 4) final)"))) theta = _atan((current_im / current_re));
  return maxCurrent * _cos(2.0f * PI * frequency * t);
}

int main()
{
  static const int len = sizeof(arr) / sizeof(arr[0]) / 5;
  float __attribute__((annotate("target('main') scalar(range(-2, 300) final)")))
  t[len];
  float __attribute__((annotate("scalar(range(-10, 50) final)"))) resistance[len];
  float __attribute__((annotate("scalar(range(-10, 100) final)"))) frequency[len];
  float __attribute__((annotate("scalar(range(-2, 2) final)")))
  inductance[len];
  float __attribute__((annotate("scalar(range(-2, 12) final)"))) maxVoltage[len];
  float __attribute__((annotate("scalar()"))) res[len];
  for (int i = 0; i < len; ++i) {

    t[i] = arr[i * 5];
    resistance[i] = arr[i * 5 + 1];
    frequency[i] = arr[i * 5 + 2];
    inductance[i] = arr[i * 5 + 3];
    maxVoltage[i] = arr[i * 5 + 4];
  }

#ifndef NO_TIMER
  reset_timer();
  start_timer();
#endif

  for (int j = 0; j < len; ++j) {
    res[j] =
        ex0(t[j], resistance[j], frequency[j], inductance[j], maxVoltage[j]);
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