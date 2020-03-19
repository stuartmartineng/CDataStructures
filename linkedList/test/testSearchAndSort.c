#include "unity.h"
#include "LinkedList.h"
/*
 * Struct: TestStruct
 * ----------------------------
 * A data structure used for testing
 */
typedef struct testingStruct{
    int num;
    char letter;
}TestStruct;

/*
 * Function: createTestingStruct
 * ----------------------------
 * Allocates and sets a structure used for testing the Stack data structure.
 * 
 * Created to keep DRY (Don't Repeated Yourself)
 */
TestStruct * createTestingStruct(int num, char c){
    TestStruct * test = malloc(sizeof(TestStruct));
    test->num = num;
    test->letter = c;
    return test;
}

void destroyFunc(void * data){
    free(data);
}

int compareFunc(void * a, void * b){
    if(((TestStruct*)a)->num == ((TestStruct*)b)->num){
        return ((TestStruct*)a)->letter - ((TestStruct*)b)->letter;
    }
    return ((TestStruct*)a)->num - ((TestStruct*)b)->num;
}
/*
 * Test: test_search_null
 * ----------------------------
 * Test that searchLL returns -1 for a NULL list.
 */
void test_search_null(void){
    
    int index = searchLL(NULL, NULL);
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, index, "NULL search did not return -1");
}

/*
 * Test: test_search_empty
 * ----------------------------
 * Test that searchLL returns -1 for an empty list.
 */
void test_search_empty(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test = createTestingStruct(1, 'a');

    int index = searchLL(list, test);
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, index, "empty search did not return -1");
    free(test);
    destroyLinkedList(list);
}

/*
 * Test: test_search_absent
 * ----------------------------
 * Test that searchLL returns -1 for an absent item.
 */
void test_search_absent(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'c');
    TestStruct * testAbsent = createTestingStruct(100, 'z');

    addToBackLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);

    int index = searchLL(list, testAbsent);
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, index, "absent search did not return -1");

    free(testAbsent);
    destroyLinkedList(list);
}

/*
 * Test: test_search
 * ----------------------------
 * Test the regular operation of search.
 */
void test_search(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(1, 'b');
    TestStruct * test3 = createTestingStruct(2, 'c');
    TestStruct * test4 = createTestingStruct(4, 'a');
    TestStruct * test5 = createTestingStruct(1, 'a');

    addToBackLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);
    addToBackLL(list, test4);
    addToBackLL(list, test5);

    int index;

    index = searchLL(list, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, index, "test1 did not find correct index");

    index = searchLL(list, test2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, index, "test2 did not find correct index");

    index = searchLL(list, test3);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, index, "test3 did not find correct index");

    index = searchLL(list, test4);
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, index, "test4 did not find correct index");

    index = searchLL(list, test5);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, index, "test5 did not find correct index");

    destroyLinkedList(list);
}

/*
 * Test: test_insert_sorted_null
 * ----------------------------
 * Test the insert sorted function handles a NULL list gracefully.
 */
void test_insert_sorted_null(void){
    int code = insertSortedLL(NULL, NULL);

    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, code, "Wrong code returned for NULL list input");
}

/*
 * Test: test_insert_sorted_unsorted
 * ----------------------------
 * Test the insert sorted function will not attempt insort into unsorted linked list.
 */
void test_insert_sorted_unsorted(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    list->sorted = 0;
    int code = insertSortedLL(list, NULL);

    TEST_ASSERT_EQUAL_INT_MESSAGE(-1, code, "Wrong code returned for unsorted list input");
    destroyLinkedList(list);
}

/*
 * Test: test_insert_sorted
 * ----------------------------
 * Test the normal functionality of the insertSortedLL function.
 */
void test_insert_sorted(void){
    char errorString[100];
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    TestStruct * test3 = createTestingStruct(3, 'a');
    TestStruct * test4 = createTestingStruct(4, 'a');
    TestStruct * test5 = createTestingStruct(4, 'a');
    int index;

    index = insertSortedLL(list, test2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, index, "index inserting test2 is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->length, "length should be 1");
    
    index = insertSortedLL(list, test4);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, index, "index inserting test4 is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "length should be 2");
    
    index = insertSortedLL(list, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, index, "index inserting test1 is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, list->length, "length should be 3");
    
    index = insertSortedLL(list, test3);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, index, "index inserting test3 is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, list->length, "length should be 4");

    index = insertSortedLL(list, test5);
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, index, "index inserting test3 is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(5, list->length, "length should be 5");

    LinkedListNode * node = list->head;
    int answers[5] = {1, 2, 3, 4, 4};
    for(int i = 0; i < 5; i++){
        sprintf(errorString, "Forward iterate error at list index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(answers[i], ((TestStruct*)node->data)->num, errorString);
        node = node->prev;
    }

    node = list->tail;
    for(int i = 4; i >= 0; i--){
        sprintf(errorString, "Backward iterate error at list index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(answers[i], ((TestStruct*)node->data)->num, errorString);
        node = node->next;
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "list was marked as not sorted");

    destroyLinkedList(list);
}


/*
 * Test: test_sorted_flag_add_to_back
 * ----------------------------
 * Test the the sorted flag for add to back.
 */
void test_sorted_flag_add_to_back(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    
    addToBackLL(list, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag did not remain 1 after first item added");
    
    addToBackLL(list, test2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->sorted, "sorted flag did switch to 0 after second item added");
    destroyLinkedList(list);
}

/*
 * Test: test_sorted_flag_add_to_front
 * ----------------------------
 * Test the the sorted flag for add to front.
 */
void test_sorted_flag_add_to_front(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    
    addToFrontLL(list, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag did not remain 1 after first item added");
    
    addToFrontLL(list, test2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->sorted, "sorted flag did switch to 0 after second item added");
    destroyLinkedList(list);
}

/*
 * Test: test_sorted_flag_insert_remove
 * ----------------------------
 * Test the the sorted flag for insert and remove
 */
void test_sorted_flag_insert_remove(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    TestStruct * test3 = createTestingStruct(2, 'a');
    void * data;

    insertAtIndexLL(list, test1, 0);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag did not remain 1 after first item added");
    
    insertAtIndexLL(list, test2, 0);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->sorted, "sorted flag did not switch to 0 after second item added");
    
    insertAtIndexLL(list, test3, 0);

    data = removeFromIndexLL(list, 0);
    free(data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->sorted, "sorted flag switched to one after third item removed");

    data = removeFromIndexLL(list, 0);
    free(data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag did not switch to one after second item removed");

    destroyLinkedList(list);
}

/*
 * Test: test_sort_sorted
 * ----------------------------
 * Test the the sortLL function using a sorted list
 */
void test_sort_sorted(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    TestStruct * test3 = createTestingStruct(3, 'a');
    TestStruct * test4 = createTestingStruct(4, 'a');
    TestStruct * test5 = createTestingStruct(5, 'a');
    TestStruct * test6 = createTestingStruct(6, 'a');
    TestStruct * test7 = createTestingStruct(7, 'a');
    TestStruct * test8 = createTestingStruct(8, 'a');

    insertSortedLL(list, test1);
    insertSortedLL(list, test2);
    insertSortedLL(list, test3);
    insertSortedLL(list, test4);
    insertSortedLL(list, test5);
    insertSortedLL(list, test6);
    insertSortedLL(list, test7);
    insertSortedLL(list, test8);

    sortLL(list);

    LinkedListNode * node = list->head;

    char errorString[100];
    //Check forward
    for(int i = 0; node != NULL; i++){
        sprintf(errorString, "Error at index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i+1, ((TestStruct*)node->data)->num, errorString);
        node = node->prev;
    }
    node = list->tail;

    //Check backwards
    for(int i = 8; node != NULL; i--){
        sprintf(errorString, "Error at index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i, ((TestStruct*)node->data)->num, errorString);
        node = node->next;
    }
    destroyLinkedList(list);

}

/*
 * Test: test_sort_reverse_sorted
 * ----------------------------
 * Test the the sortLL function using a reverse sorted list
 */
void test_sort_reverse_sorted(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    TestStruct * test3 = createTestingStruct(3, 'a');
    TestStruct * test4 = createTestingStruct(4, 'a');
    TestStruct * test5 = createTestingStruct(5, 'a');
    TestStruct * test6 = createTestingStruct(6, 'a');
    TestStruct * test7 = createTestingStruct(7, 'a');
    TestStruct * test8 = createTestingStruct(8, 'a');
    TestStruct * test9 = createTestingStruct(9, 'a');

    addToFrontLL(list, test1);
    addToFrontLL(list, test2);
    addToFrontLL(list, test3);
    addToFrontLL(list, test4);
    addToFrontLL(list, test5);
    addToFrontLL(list, test6);
    addToFrontLL(list, test7);
    addToFrontLL(list, test8);
    addToFrontLL(list, test9);

    sortLL(list);

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag was not set to 1 after sorting");

    LinkedListNode * node = list->head;

    char errorString[100];
    //Check forward
    for(int i = 0; node != NULL; i++){
        sprintf(errorString, "Error at index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i+1, ((TestStruct*)node->data)->num, errorString);
        node = node->prev;
    }
    node = list->tail;

    //Check backwards
    for(int i = 9; node != NULL; i--){
        sprintf(errorString, "Error at index: %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i, ((TestStruct*)node->data)->num, errorString);
        node = node->next;
    }

    destroyLinkedList(list);

}

/*
 * Test: test_sort_null
 * ----------------------------
 * Test the the sortLL function handles a NULL list gracefully
 */
void test_sort_null(void){
    int code = sortLL(NULL);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, code, "returned wrong code for null list input");
}

/*
 * Test: test_sort_empty
 * ----------------------------
 * Test the the sortLL function handles an empty list gracefully
 */
void test_sort_empty(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    int code = sortLL(list);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "returned wrong code for empty list input");
    destroyLinkedList(list);
}

/*
 * Test: test_sort_one_item
 * ----------------------------
 * Test the the sortLL function handles a one item list gracefully
 */
void test_sort_one_item(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test = createTestingStruct(1, 'a');
    addToBackLL(list, test);
    int code = sortLL(list);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "returned wrong code for one item list input");
    destroyLinkedList(list);
}

void setUp(void) {
    // set stuff up here

}

void tearDown(void) {
    // clean stuff up here
}

int main(void) {

    UNITY_BEGIN();
    
    //search tests
    RUN_TEST(test_search_null);
    RUN_TEST(test_search_empty);
    RUN_TEST(test_search_absent);
    RUN_TEST(test_search);

    //insertSorted tests
    RUN_TEST(test_insert_sorted_null);
    RUN_TEST(test_insert_sorted_unsorted);
    RUN_TEST(test_insert_sorted);

    //test sorted flag
    RUN_TEST(test_sorted_flag_add_to_back);
    RUN_TEST(test_sorted_flag_add_to_front);
    RUN_TEST(test_sorted_flag_insert_remove);

    //merge sort tests
    RUN_TEST(test_sort_sorted);
    RUN_TEST(test_sort_reverse_sorted);
    RUN_TEST(test_sort_null);
    RUN_TEST(test_sort_empty);
    RUN_TEST(test_sort_one_item);

    return UNITY_END();
}