#include "stack.h"
#include "list.h"
#include <stdlib.h>

int main() {
	stack_t s = stack_create(sizeof(int));
	int *value = (int *)malloc(sizeof(int));
	stack_push(&s, value);
	stack_destroy(&s);

	list_t l = list_create(sizeof(int), NULL);
	
	list_destroy(l);
	return 0;
}


