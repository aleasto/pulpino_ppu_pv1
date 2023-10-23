#include "intrinsics.h"

int main() {
    float x = 16.0f;
    float y = 0.5f;

    printf("%f + %f = %f\n", x, y, pcvt_f( padd(fcvt_p(x), fcvt_p(y)) ));
    printf("%f - %f = %f\n", x, y, pcvt_f( psub(fcvt_p(x), fcvt_p(y)) ));
    printf("%f * %f = %f\n", x, y, pcvt_f( pmul(fcvt_p(x), fcvt_p(y)) ));
    printf("%f / %f = %f\n", x, y, pcvt_f( pdiv(fcvt_p(x), fcvt_p(y)) ));
}
