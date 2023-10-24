#include <stdio.h>

#define N 3
int main() {
    float __attribute__((annotate("scalar()"))) x;

    for (float __attribute((annotate("scalar()"))) i = 0; i < N; i++) {
        x = i / N + i;
        printf("%f\n", x);
    }
}
