#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void DieWithError(char* errorMessage) {
	perror(errorMessage);
	exit(1);
}

int chkInvalidInput(int* x, int* y) {
	if ((scanf_s("%d", x) + scanf_s("%d", y)) < 2) {
		perror("invalid maze type!\n");
		exit(1);
	}
	if (init(x, y)) {
		perror("calloc failed. parameter ");
		exit(1);
	}

	if (!(width % 2) || !(height % 2)) {
		perror("faild");
		exit(1);
	}
	if (width <= 0 || height <= 0) {
		perror("faild");
		exit(1);
	}
	return 0;
}

