#include <stdbool.h>
#include <cstddef>

typedef struct stack_object {
	struct stack_object *previous;
	void *value;
} stack_object_t;

struct stack {
	size_t element_size;
	stack_object_t *peek_object;	
};

typedef stack stack_t;

/*
 * Initializes new stack.
 */
stack_t stack_create(size_t element_size);

bool stack_is_empty(stack_t *s);

void *stack_peek(stack_t *s);

/*
 * @returns Returns false if the element couldn't be pushed to the stack, because of failed memory allocation.
 * Returns true if the element was successfully pushed to the stack.
 */
bool stack_push(stack_t *s, void *element);

/*
 * Popped element has to be freed if it is malloced.
 */
void *stack_pop(stack_t *s);

/*
 * Frees all values saved in the stack.
 */
void stack_destroy(stack_t *s);

/*
 * Tries to find searched_value in the stack using given comapre_func.
 *
 * @returns Returns index from the top of the stack. 
 * If the value is at the top of the stack, returns 0, because no pop is needed to get to that element.
 */
int stack_search(stack_t *s, void *searched_value, bool (*compare_func)(void *, void *)); 

