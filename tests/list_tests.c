#include "CppUTest/TestHarness.h"
#include "list.h"

TEST_GROUP(ListTestGroup)
{
	list_t l;

	void setup() {
		l = list_create(sizeof(int), NULL);
		if (!l) {
			FAIL("list_created failed");
		}
	}		

	void teardown() {
		list_destroy(l);	
	}
};

TEST(ListTestGroup, Create_EmptyAfterCreate)
{
	CHECK(list_is_empty(l));	
}

TEST(ListTestGroup, Size_OfEmptyList_IsZero) {
	CHECK_EQUAL(0, list_size(l));
}	

TEST(ListTestGroup, Add_ToEmptyList_IncreasesSize) {
	int a = 4;	
	if (!list_add(l, &a)) {
		FAIL("list_add failed");
	}

	CHECK_EQUAL(1, list_size(l));
}

TEST(ListTestGroup, Add_ToEmptyListMultipleElements_SizeIsCorrect) {
	for (int i = 0; i < 1000; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}

		CHECK_FALSE(list_is_empty(l));
		CHECK_EQUAL((size_t)i + 1, list_size(l));
	}
}

TEST(ListTestGroup, Get_FromNonEmptyList_GetsCorrectValue) {
	for (int i = 0; i < 10; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}
	int index = 5;	
	int expected_value = 5;
	CHECK_EQUAL(expected_value, *(int *)list_get(l, index));
}

TEST(ListTestGroup, Clear_NonEmptyList_ClearsItCorrectly) {
	for (int i = 0; i < 10; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}

	list_clear(l);

	CHECK_EQUAL(0, list_size(l));
	CHECK(list_is_empty(l));
}

TEST(ListTestGroup, IsEmpty_OfNonEmptyList_ReturnsFalse) {
	int val = 5;
	if (!list_add(l, &val)) {
		FAIL("list_add failed");
	}
	
	CHECK_FALSE(list_is_empty(l));	
}

TEST(ListTestGroup, Remove_FromNonEmptyList_DecreasesSize) {
	// Add 10 items to the list
	for (int i = 0; i < 10; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}
	// And now remove 3 items
	list_remove_at(l, 0); // Remove first
	list_remove_at(l, 8); // Remove last
	list_remove_at(l, 4); // Remove somewhere in the middle

	// List contains the right count 
	CHECK_EQUAL(7, list_size(l));
	CHECK_EQUAL(8, *(int *)list_get(l, 6));
	CHECK_EQUAL(1, *(int *)list_get(l, 0));
}	

TEST(ListTestGroup, Remove_FourElementsOutOfFive_LeavesOneElement) {
	// Add 5 items to the list with values 0, 1, 2, 3, 4
	for (int i = 0; i < 5; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}

	list_remove_at(l, 0); // remove 0
	list_remove_at(l, 0); // remove 1
	list_remove_at(l, 2); // remove 4
	list_remove_at(l, 0); // remove 2

	// leaves value 3 untouched
	CHECK_EQUAL(1, list_size(l));	
	CHECK_FALSE(list_is_empty(l));
	CHECK_EQUAL(3,  *(int *)list_get(l, 0));
}

static int int_compare_func(const void *v1, const void *v2) {
	return *(int*)v1 - *(int*)v2;
}

TEST(ListTestGroup, Contains_NoSuchElementInList_ReturnsFalse) {
	for (int i = 0; i < 5; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}

	int searched_for = 5;	
	CHECK_FALSE(list_contains(l, &searched_for, int_compare_func));
}

TEST(ListTestGroup, Contains_ElementIsInList_ReturnsTrue) {
	for (int i = 0; i < 5; i++) {
		if (!list_add(l, &i)) {
			FAIL("list_add failed");
		}
	}

	int searched_for = 4;	
	CHECK(list_contains(l, &searched_for, int_compare_func));

}

TEST(ListTestGroup, Sort_NonEmptyList_ListSequenceIsCorrect) {
	int values_length = 9;
	int values[9] = { 1, 4, 41, 2, 3, 8, 4, 10, 0 };
	int sorted[9] = { 0, 1, 2, 3, 4, 4, 8, 10, 41 };

	for (int i = 0; i < values_length; i++) {
		if (!list_add(l, &values[i])) {
			FAIL("list_add failed");
		}
	}

	list_sort(l, int_compare_func);
	
	for (int i = 0; i < values_length; i++) {
		CHECK_EQUAL(sorted[i], *(int *)list_get(l, i));
	}
}

