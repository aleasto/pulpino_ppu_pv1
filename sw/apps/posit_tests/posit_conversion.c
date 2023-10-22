#include "intrinsics.h"

int main() {
    float x = 16.0;
    printf("Converted %f back to %f\n", x, pcvt_f(fcvt_p(x)));

    float y = 0.5;
    printf("Converted %f back to %f\n", y, pcvt_f(fcvt_p(y)));

    float z = 0.1;
    printf("Converted %f back to %f\n", z, pcvt_f(fcvt_p(z)));

    float w = 0.3;
    printf("Converted %f back to %f\n", w, pcvt_f(fcvt_p(w)));

    float pi = atan(1)*4;
    printf("Converted %f back to %f\n", pi, pcvt_f(fcvt_p(pi)));
}
