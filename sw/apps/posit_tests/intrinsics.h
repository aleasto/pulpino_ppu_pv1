#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef int posit_t;

typedef struct {
    int8_t p1;
    int8_t p2;
    int8_t p3;
    int8_t p4;
} packed_p4;

typedef struct {
    int16_t p1;
    int16_t p2;
} packed_p2;

typedef union {
    int32_t raw;
    packed_p4 p4;
    packed_p2 p2;
} packed_posit;


// Posit addition via asm
// Format is identical to integer addition
// We change opcode accordingly
posit_t padd(long a, long b) {
  int result;
  __asm__(
      ".insn r 0xb, 0, 0x6A, %[result], %1, %2"
      : [result] "=r"(result)
      : "r"(a), "r"(b));
  return result;
}

posit_t psub(long a, long b) {
  int result;
  __asm__(
      ".insn r 0xb, 1, 0x6A, %[result], %1, %2"
      : [result] "=r"(result)
      : "r"(a), "r"(b));
  return result;
}

posit_t pmul(long a, long b) {
  int result;
  __asm__(
      ".insn r 0xb, 2, 0x6A, %[result], %1, %2"
      : [result] "=r"(result)
      : "r"(a), "r"(b));
  return result;
}

posit_t pdiv(long a, long b) {
  int result;
  __asm__(
      ".insn r 0xb, 4, 0x6A, %[result], %1, %2"
      : [result] "=r"(result)
      : "r"(a), "r"(b));
  return result;
}

posit_t pneg(long a) {
  int result;
  __asm__(
      ".insn r 0xb, 1, 0x6A, %[result], x0, %1"
      : [result] "=r"(result)
      : "r"(a));
  return result;
}

union fltrepr {
    float flt;
    int i;
};

posit_t fcvt_p(float f) {
  union fltrepr repr;
  int result;
  repr.flt = f;
  __asm__(
      ".insn r 0xb, 0, 0x68, %[result], %1, x0"
      : [result] "=r"(result)
      : "r"(repr.i));
  return result;
}

float pcvt_f(posit_t p) {
  union fltrepr repr;
  __asm__(
      ".insn r 0xb, 0, 0x69, %[result], %1, x0"
      : [result] "=r"(repr.i)
      : "r"(p));
  return repr.flt;
}