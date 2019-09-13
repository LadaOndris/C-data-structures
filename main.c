#include "stack.h"
#include <stdlib.h>

int main() {
	stack_t s = stack_create(sizeof(int));
	int *value = (int *)malloc(sizeof(int));
	stack_push(&s, value);
	stack_destroy(&s);

	return 0;
}


