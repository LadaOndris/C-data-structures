#include "stack.h"
#include <stdlib.h>
#include <cstddef>

stack_object_t *stack_object_create() {
	stack_object_t *object = (stack_object_t *)malloc(sizeof(stack_object_t));
	if (object == NULL)
		return NULL;
	object->previous = NULL;
	object->value = NULL;
	return object;
}

void stack_object_destroy(stack_object_t *object) {
	free(object->value);
	free(object);
}

stack_t stack_create(size_t element_size) {
	stack_t s;
	s.element_size = element_size;
	s.peek_object = NULL;
	return s;
}

bool stack_is_empty(stack_t *s) {
	return s->peek_object == NULL;
}

void *stack_peek(stack_t *s) {
	if (s->peek_object == NULL)
		return NULL;
	return s->peek_object->value;
}

bool stack_push(stack_t *s, void *value) {
	stack_object_t *obj = stack_object_create();
	if (obj == NULL)
		return false;
	obj->previous = s->peek_object;
	obj->value = value;	
	s->peek_object = obj;
	return true;
}

void *stack_pop(stack_t *s) {
	// Get the value at the top of the stack
	stack_object_t *peek_object = s->peek_object;
	if (stack_is_empty(s)) {
		return NULL;
	}
	void *popped_value = peek_object->value;
	// Lower the top of the stack
	s->peek_object = peek_object->previous;
	// Free the helper stack object
	free(peek_object);
	// Return value
	return popped_value;
}

void stack_destroy(stack_t *s) {
	stack_object_t *peek_obj = s->peek_object;
	while (peek_obj != NULL) {
		stack_object_t *previous = peek_obj->previous;
		stack_object_destroy(peek_obj);
		peek_obj = previous;
	}
	s->peek_object = NULL;	
}

int stack_search(stack_t *s, void *searched_value, bool (*compare_func)(void *, void *)) {
	stack_object_t *current_obj = s->peek_object;
	int index = 0;

	while (current_obj != NULL) {
		if (compare_func(current_obj->value, searched_value)) {
			return index;
		}	
		index++;
		current_obj = current_obj->previous;
	}
	return -1; // Not found
}


