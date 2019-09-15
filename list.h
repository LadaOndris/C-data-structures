
#ifndef _LIST_C_
#define _LIST_C_

#include <stddef.h>

// Opaque pointer
typedef struct list *list_t;

/*
 * Functions which is executed for an element in the list, when 
 * the element is being deallocated. 
 * In the following operations deallocation of an element occurs:
 * - list_destroy
 * - list_clear
 * - list_remove_at
 *
 * The function should be used if the element added to the list were 
 * malloced or any of the nested fields contained in a struct
 * were malloced and are needed to be freed.
 */
typedef void (*free_item_func)(void *);

typedef int (*compare_func)(const void *, const void*);

/*
 * Allocates new list structures and initializes it.
 * If allocation failed, returns null.
 */
list_t list_create(size_t element_size, free_item_func free_func);

/*
 * Deallocates all contained elements and the list itself.
 */
void list_destroy(list_t l);

/* 
 * Returns true if there is no element in the list, otherwise false.
 */
bool list_is_empty(list_t l);

/*
 * Clears all elements in the list. 
 * Calls free_item_func function on each item, if such function was provided in list_create.
 */
void list_clear(list_t l);

/*
 * Returns number of elements contained in the list.
 */
size_t list_size(list_t l);

/*
 * Copies data from where the value points to and saves it at the end of the list. 
 * @returns Returns true if value is successfully added, otherwise false.
 */
bool list_add(list_t l, const void *value);

/*
 * @returns Returns a pointer pointing to the value at the specified index in the list.
 */
void *list_get(list_t l, int index);

/*
 * Removes an element from the list at the specified index.
 * @returns  Returns true if the element was successfully removed, otherwise false.
 * Removing fails if the index is out of bounds and returns false.
 */
bool list_remove_at(list_t l, int index);

/*
 * Searches for an element which would be equal 
 * to the one pointed to by the element given as a parameter.
 * For comparison uses the compare_func function.
 * @returns Returns true if such an element was found, otherwise false.
 */
bool list_contains(list_t l, void *element, compare_func cmp_func);

/*
 * Sorts the elements in a list.
 * For comparison uses the compare_func function.
 */
void list_sort(list_t l, compare_func cmp_func);


#endif
