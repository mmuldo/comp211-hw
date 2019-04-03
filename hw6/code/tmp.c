#include <stdio.h>
#include "hw6.h"

int main(void) {
	int A[] = {-2,-1,-6,-3,-5,-4};
	merge3(A, 0, 2, 4, 6);

	for (int i=0; i<6; i++){
		printf("%d\n", A[i]);
	}

	return 0;
}
