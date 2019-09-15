
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

struct list {
	size_t size;
	size_t capacity;
	size_t item_size;
	char *data;
	free_item_func free_func;
};

static size_t INCREASE_CAPACITY_COEFFICIENT = 2;
static size_t INITIAL_CAPACITY = 4;

list_t list_create(size_t item_size, free_item_func free_func) {
	list_t l = (list_t) malloc(sizeof(struct list));
	if (l == NULL)
		return NULL;
	l->size = 0;
	l->capacity = 0;
	l->item_size = item_size;
	l->data = NULL;
	l->free_func = free_func;
	return l;
}

static void list_destroy_items(list_t l) {
	if (l->free_func) {
		for (size_t i = 0; i < l->size; i++) {
			l->free_func((l->data + (i * l->item_size)));
		}
	}
	free(l->data);
	l->data = NULL;
	l->capacity = 0;
	l->size = 0;
}

void list_destroy(list_t l) {
	if (l == NULL)
		return;
	list_destroy_items(l);
	free(l);
	l = NULL;
}

bool list_is_empty(list_t l) {
	return list_size(l) == 0;
}

void list_clear(list_t l) {
	list_destroy_items(l);
}

size_t list_size(list_t l) {
	return l->size;
}

static bool list_increase_capacity(list_t l, size_t new_capacity) {
	void *data = reallocarray(l->data, l->item_size, new_capacity);
	if (data == NULL)
		return false;
	l->data = (char *)data;	
	l->capacity = new_capacity;
	return true;
}

/*
 * If there is no space for new element, increases the list's capacity.
 * @returns Returns true if the capacity is successfully increased.
 */
static bool list_increase_capacity_if_needed(list_t l) {
	if (l->size + 1 > l->capacity) {
		size_t new_capacity;
		if (l->capacity == 0)		
			new_capacity = INITIAL_CAPACITY;
		else
			new_capacity = l->capacity * INCREASE_CAPACITY_COEFFICIENT;
		return list_increase_capacity(l, new_capacity);
	}
	return true;
}

static void list_set_value(list_t l, int index, const void *item) {
	void *dest = (l->data + (index * l->item_size)); 
	const void *src = item;
	memcpy(dest, src, l->item_size);
}	

bool list_add(list_t l, const void *value) {
	if (!list_increase_capacity_if_needed(l)) 
		return false;
	list_set_value(l, l->size, value);
	l->size++;
	return true;
}

static bool is_index_in_bounds(list_t l, int index) {
	return index >= 0 && (size_t)index < l->size;
}

void *list_get(list_t l, int index) {
	if (!is_index_in_bounds(l, index)) {
		return NULL;
	}
	return l->data + (index * l->item_size);
}

bool list_remove_at(list_t l, int index) {
	if (!is_index_in_bounds(l, index)) {
		return false;
	}
	// Free the removed element
	char *dest = (l->data + (index * l->item_size));

	if (l->free_func) {
		l->free_func(dest);
	}

	int move_by = l->size - index - 1;
	void *src = dest + l->item_size;
	memmove(dest, src, move_by * l->item_size);

	l->size--;
	return true;
}

bool list_contains(list_t l, void *searched_for_element, compare_func cmp_func) {
	for (size_t i = 0; i < l->size; i++) {
		void *element = list_get(l, i);
		bool equals = cmp_func(searched_for_element, element) == 0;
		if (equals) {
			return true;
		}
	}
	return false;
}

void list_sort(list_t l, compare_func cmp_func) {
	qsort(l->data, l->size, l->item_size, cmp_func);
}

