#include "fourier.hpp"
#include <stdio.h>
#include <stdlib.h>

#ifndef NO_TIMER
extern "C" {
#include <timer.h>
}
#endif

#define N_DATA 4
static int indices[N_DATA];
static Complex __attribute((annotate("target('x') " ANNOTATION_COMPLEX_RANGE))) x[N_DATA];
static Complex __attribute((annotate("target('f') " ANNOTATION_COMPLEX(,)))) f[N_DATA];

int main(int argc, char* argv[])
{
	int i ;
	int K = N_DATA;

	for(i = 0;i < K ; i++)
	{
		x[i].real = i < (K / 2) ? 1.0 : 0.0;
		x[i].imag = 0 ;
	}

#ifndef NO_TIMER
	reset_timer();
	start_timer();
#endif

	radix2DitCooleyTykeyFft(K, indices, x, f) ;

#ifndef NO_TIMER
	stop_timer();
	printf("TIME: %d\n", get_time());
#endif

	for(i = 0;i < K ; i++)
	{
		printf("%f %f %d\n", f[i].real, f[i].imag, indices[i]);
	}

	return 0 ;
}
