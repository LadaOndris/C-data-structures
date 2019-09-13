#include "CppUTest/TestHarness.h"
#include "stack.h"

TEST_GROUP(StackTestGroup)
{
	   
};

TEST(StackTestGroup, EmptyAfterCreate)
{
	stack_t s = stack_create(sizeof(int));
	
	CHECK(stack_is_empty(&s));

	stack_destroy(&s);
}

TEST(StackTestGroup, Peek_IfStackEmpty_ReturnsNull) {
	stack_t s = stack_create(sizeof(int));
	int *element = (int *)stack_peek(&s);
	
	CHECK(element == NULL);

	stack_destroy(&s);
}

TEST(StackTestGroup, Peek_IfNotEmpty_ReturnsCorrectValue) {
	stack_t s = stack_create(sizeof(int));
	int *element = (int *)malloc(sizeof(int));
	if (element == NULL) {
		FAIL("malloc failed");	
	}
	*element = 5;
	if (!stack_push(&s, element)) {
		FAIL("failed push");
	}	
	
	int *peeked_element = (int *)stack_peek(&s);
	
	CHECK(*peeked_element == 5);

	stack_destroy(&s);
}

TEST(StackTestGroup, Push_ToEmptyStack_ThenIsNotEmpty) {
	stack_t s = stack_create(sizeof(int));
	int *element = (int *)malloc(sizeof(int));
	if (element == NULL) {
		FAIL("malloc failed");	
	}
	*element = 5;

	if (!stack_push(&s, element)) {
		FAIL("failed push");
	}	
	printf("%d", stack_is_empty(&s));	
	CHECK_FALSE(stack_is_empty(&s));

	stack_destroy(&s);
}

typedef struct {
	int value1;
	char value2;
	long value3;
} test_struct_t;

TEST(StackTestGroup, Push_ToEmptyStack_ContainsCorrectValue) {
	stack_t s = stack_create(sizeof(int));
	test_struct_t *element = (test_struct_t *)malloc(sizeof(test_struct_t));
	if (element == NULL) {
		FAIL("malloc failed");	
	}
	element->value1 = 5000;
	element->value2 = 120;
	element->value3 = 100000;

	if (!stack_push(&s, element)) {
		FAIL("failed push");
	}
	test_struct_t *peeked_element = (test_struct_t *)stack_peek(&s);
	CHECK(peeked_element->value1 == 5000);
	CHECK(peeked_element->value2 == 120);
	CHECK(peeked_element->value3 == 100000);

	stack_destroy(&s);
}

TEST(StackTestGroup, Pop_EmptyStack_ReturnsNull) {
	stack_t s = stack_create(sizeof(long));
	
	CHECK(stack_pop(&s) == NULL);

	stack_destroy(&s);
}

TEST(StackTestGroup, Pop_FilledStack_IsEmpty) {
	stack_t s = stack_create(sizeof(long));

	int num_of_iterations = 10;
	for (int i = 0; i < num_of_iterations; i++) {
		long *value = (long *) malloc(sizeof(long));
		if (value == NULL) {
			FAIL("malloc failed");	
		}
		*value = i;
		if (!stack_push(&s, value)) {
			FAIL("failed push");
		}
	}
	for (int i = 0; i < num_of_iterations; i++) {
		stack_pop(&s);
	}
	CHECK(stack_is_empty(&s));

	stack_destroy(&s);
}

TEST(StackTestGroup, Pop_FilledStack_InCorrectOrder) {
	stack_t s = stack_create(sizeof(long));

	int num_of_iterations = 10;
	for (int i = 0; i < num_of_iterations; i++) {
		long *value = (long *) malloc(sizeof(long));
		if (value == NULL) {
			FAIL("malloc failed");	
		}
		*value = i;
		if (!stack_push(&s, value)) {
			FAIL("failed push");
		}
	}
	for (int i = num_of_iterations - 1; i >= 0; i--) {
		long *value = (long *)stack_pop(&s);
		CHECK(*value == i);
	}

	stack_destroy(&s);
}

bool search_function(void *value1, void *value2) {
	return *(int *)value1 == *(int *)value2;
}

TEST(StackTestGroup, Search_EmptyStack_ReturnsNegative) {
	stack_t s = stack_create(sizeof(int));

	int searched_value = 5;
	int result = stack_search(&s, &searched_value, search_function); 
	CHECK(result < 0);

	stack_destroy(&s);
}

TEST(StackTestGroup, Search_NotFoundElement_ReturnsNegative) {
	stack_t s = stack_create(sizeof(int));

	for (int i = 0; i < 10; i++) {
		long *value = (long *) malloc(sizeof(long));
		if (value == NULL) {
			FAIL("malloc failed");	
		}
		*value = 0;
		if (!stack_push(&s, value)) {
			FAIL("failed push");
		}
	}
	
	int searched_value = 5;
	int result = stack_search(&s, &searched_value, search_function); 
	CHECK(result < 0);

	stack_destroy(&s);
}

TEST(StackTestGroup, Search_SearchedValueAtTheTop_ReturnsZero) {
	stack_t s = stack_create(sizeof(int));

	for (int i = 10; i < 15; i++) {
		long *value = (long *) malloc(sizeof(long));
		if (value == NULL) {
			FAIL("malloc failed");
		}
		*value = i;
		if (!stack_push(&s, value)) {
			FAIL("failed push");
		}
	}
	
	int searched_value = 14;
	int result = stack_search(&s, &searched_value, search_function); 
	CHECK_EQUAL(0, result);

	stack_destroy(&s);
}

TEST(StackTestGroup, Search_SearchedValueAtTheBottom_ReturnsMaximalIndex) {
	stack_t s = stack_create(sizeof(int));

	for (int i = 10; i < 15; i++) {
		long *value = (long *) malloc(sizeof(long));
		if (value == NULL) {
			FAIL("malloc failed");
		}
		*value = i;
		if (!stack_push(&s, value)) {
			FAIL("failed push");
		}
	}
	
	int searched_value = 10;
	int result = stack_search(&s, &searched_value, search_function); 
	CHECK_EQUAL(4, result);

	stack_destroy(&s);
}

