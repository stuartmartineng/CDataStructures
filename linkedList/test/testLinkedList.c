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
    return ((TestStruct*)a)->num - ((TestStruct*)b)->num;
}


void setUp(void) {
    // set stuff up here

}

void tearDown(void) {
    // clean stuff up here
}

/*
 * Test: test_create_stack
 * ----------------------------
 * Ensure the createStack function works as expected
 */
void test_create_linked_list(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TEST_ASSERT_NOT_NULL_MESSAGE(list, "createLinkedList returned NULL");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->length, "list length not initiliazed to zero");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->sorted, "sorted flag did not initialize to one");
    destroyLinkedList(list);
}

/*
 * Test: test_add_to_front
 * ----------------------------
 * Test the add to front function.
 */
void test_add_to_front(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');

    int code = addToFrontLL(list, test1);

    TEST_ASSERT_NOT_NULL_MESSAGE(list->head, "head NULL after add to front");
    TEST_ASSERT_NOT_NULL_MESSAGE(list->tail, "tail NULL after add to front");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->length, "incorrect length after add to front");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "error code received on first call");
    code = addToFrontLL(list, test2);

    TEST_ASSERT_EQUAL_INT_MESSAGE(2, ((TestStruct*)list->head->data)->num, "Item added to wrong side");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, ((TestStruct*)list->tail->data)->num, "Tail item incorrect");
    TEST_ASSERT_MESSAGE(list->head->prev->data == test1, "Did not set heads prev succesfully");
    TEST_ASSERT_MESSAGE(list->tail->next->data == test2, "Did not set tails next succesfully");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "incorrect length after second add to front");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "error code received on second call");

    destroyLinkedList(list);
}

/*
 * Test: test_add_to_front_null
 * ----------------------------
 * Test the add to front function handles NULL list gracefully.
 */
void test_add_to_front_null(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    int code = addToFrontLL(NULL, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, code, "NULL addToFrontLL did not return error code");
    free(test1);
}

/*
 * Test: test_add_to_back
 * ----------------------------
 * Test the add to back function.
 */
void test_add_to_back(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');

    int code = addToBackLL(list, test1);

    TEST_ASSERT_NOT_NULL_MESSAGE(list->head, "head NULL after add to back");
    TEST_ASSERT_NOT_NULL_MESSAGE(list->tail, "tail NULL after add to back");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->length, "incorrect length after add to back");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "error code received on first call");

    code = addToBackLL(list, test2);

    TEST_ASSERT_EQUAL_INT_MESSAGE(2, ((TestStruct*)list->tail->data)->num, "Item added to wrong side");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, ((TestStruct*)list->head->data)->num, "head item incorrect");
    TEST_ASSERT_MESSAGE(list->head->prev->data == test2, "Did not set heads prev succesfully");
    TEST_ASSERT_MESSAGE(list->tail->next->data == test1, "Did not set tails next succesfully");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "incorrect length after second add to back");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "error code received on second call");
    destroyLinkedList(list);
}

/*
 * Test: test_add_to_back_null
 * ----------------------------
 * Test the add to front function.
 */
void test_add_to_back_null(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    int code = addToBackLL(NULL, test1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, code, "NULL addToBackLL did not return error code");
    free(test1);
}

/*
 * Test: test_insert_in_empty_list
 * ----------------------------
 * Test the insert function on an empty list.
 */
void test_insert_in_empty_list(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    int code = insertAtIndexLL(list, test1, 0);

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "failure code return from insert into empty list");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->length, "list length incorrect after insert into empty list");
    TEST_ASSERT_NOT_NULL_MESSAGE(list->head, "head NULL after insert into empty list");
    TEST_ASSERT_NOT_NULL_MESSAGE(list->tail, "tail NULL after insert into empty list");

    destroyLinkedList(list);    

}

/*
 * Test: test_insert_out_of_lower_bounds
 * ----------------------------
 * Test the insert function handles negative index gracefully.
 */
void test_insert_out_of_lower_bounds(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    int code = insertAtIndexLL(list, test1, -1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, code, "wrong code return for negative index input");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->length, "List length is incorrect");
    free(test1);
    destroyLinkedList(list);
}

/*
 * Test: test_insert_out_of_upper_bounds
 * ----------------------------
 * Test the insert function handles negative index gracefully.
 */
void test_insert_out_of_upper_bounds(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    int code = insertAtIndexLL(list, test1, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, code, "wrong code return for too high index input");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->length, "List length is incorrect");
    free(test1);
    destroyLinkedList(list);
}

/*
 * Test: test_insert_at_tail
 * ----------------------------
 * Test the insert function can insert at the end of the list.
 */
void test_insert_at_tail(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);

    addToFrontLL(list, test1);
    int code = insertAtIndexLL(list, test2, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "Failure error code returned");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->data == test1, "head of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->data == test2, "tail of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->next->data == test1, "next of tail is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->prev->data == test2, "prev of head is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "list length is incorrect");

    destroyLinkedList(list);
}

/*
 * Test: test_insert_at_head
 * ----------------------------
 * Test the insert function can insert at the front of the list.
 */
void test_insert_at_head(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);

    insertAtIndexLL(list, test1, 0);
    int code = insertAtIndexLL(list, test2, 0);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "Failure error code returned");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->data == test2, "head of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->data == test1, "tail of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->next->data == test2, "next of tail is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->prev->data == test1, "prev of head is incorrect");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "list length is incorrect");

    destroyLinkedList(list);
}

/*
 * Test: test_insert_at_middle
 * ----------------------------
 * Test the insert function can insert in the middle of the list.
 */
void test_insert_at_middle(void){
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'c');
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);

    addToFrontLL(list, test1);
    addToBackLL(list, test3);
    
    int code = insertAtIndexLL(list, test2, 1);

    LinkedListNode * node = list->head->prev;
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, code, "Failure error code returned");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->data == test1, "head of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->data == test3, "tail of list is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->next->data == test2, "next of tail is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->prev->data == test2, "prev of head is incorrect");
    TEST_ASSERT_MESSAGE((TestStruct*)node->next->data == test1, "node next not set correctly");
    TEST_ASSERT_MESSAGE((TestStruct*)node->prev->data == test3, "node prev not set correctly");
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, list->length, "list length is incorrect");

    destroyLinkedList(list);
}

/*
 * Test: test_remove_null
 * ----------------------------
 * Test the remove function handles null list gracefully.
 */
void test_remove_null(void){
    void * data = removeFromIndexLL(NULL, 0);
    TEST_ASSERT_NULL_MESSAGE(data, "return from null call to remove was not null");
    
}

/*
 * Test: test_remove_empty_list
 * ----------------------------
 * Test the remove function handles empty list gracefully.
 */
void test_remove_empty_list(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    void * data = removeFromIndexLL(list, 0);
    TEST_ASSERT_NULL_MESSAGE(data, "return from empty list call to remove was not null");
    destroyLinkedList(list);
}

/*
 * Test: test_remove_empty_list
 * ----------------------------
 * Test the remove function handles empty list gracefully.
 */
void test_remove_out_of_lower_bounds(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    addToBackLL(list, test1);
    void * data = removeFromIndexLL(list, -1);
    TEST_ASSERT_NULL_MESSAGE(data, "return from out of lower bounds call to remove was not null");

    destroyLinkedList(list);
}

/*
 * Test: test_remove_out_of_upper_bounds
 * ----------------------------
 * Test the remove function handles empty list gracefully.
 */
void test_remove_out_of_upper_bounds(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    addToBackLL(list, test1);
    void * data = removeFromIndexLL(list, 1);
    TEST_ASSERT_NULL_MESSAGE(data, "return from out of upper bounds call to remove was not null");

    destroyLinkedList(list);
}

/*
 * Test: test_remove_first_index
 * ----------------------------
 * Test the remove function on the first index.
 */
void test_remove_first_index(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'b');
    addToFrontLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);
    void * data = removeFromIndexLL(list, 0);

    TEST_ASSERT_MESSAGE(data == test1, "remove from index returned incorrect data");
    TEST_ASSERT_MESSAGE((TestStruct*)list->head->data == test2, "head was not reset correctly");
    TEST_ASSERT_NULL_MESSAGE(list->head->next, "new heads next not set correctly");
    TEST_ASSERT_MESSAGE(list->head->prev->data == test3, "new heads prev not set correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "list length not set correctly");
    free(data);
    destroyLinkedList(list);
}

/*
 * Test: test_remove_last_index
 * ----------------------------
 * Test the remove function on the last index.
 */
void test_remove_last_index(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    addToFrontLL(list, test1);
    addToBackLL(list, test2);

    void * data = removeFromIndexLL(list, list->length-1);

    TEST_ASSERT_MESSAGE(data == test2, "remove from index returned incorrect data");
    TEST_ASSERT_MESSAGE((TestStruct*)list->tail->data == test1, "tail was not reset correctly");
    TEST_ASSERT_NULL_MESSAGE(list->tail->prev, "new tails prev not set correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, list->length, "list length not set correctly");
    free(data);
    destroyLinkedList(list);
}

/*
 * Test: test_remove_middle_index
 * ----------------------------
 * Test the remove function on the last index.
 */
void test_remove_middle_index(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'c');
    addToBackLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);

    void * data = removeFromIndexLL(list, 1);

    TEST_ASSERT_MESSAGE(data == test2, "remove from index returned incorrect data");
    TEST_ASSERT_MESSAGE(list->tail->next == list->head, "tails next was not reset correctly");
    TEST_ASSERT_MESSAGE(list->head->prev == list->tail, "heads prev was not reset correctly");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, list->length, "list length not set correctly");
    free(data);
    destroyLinkedList(list);
}

/*
 * Test: test_remove_last_entry
 * ----------------------------
 * Test the remove function on the only element in a list.
 */
void test_remove_last_entry(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    addToFrontLL(list, test1);

    void * data = removeFromIndexLL(list, 0);

    TEST_ASSERT_MESSAGE(data == test1, "remove from index returned incorrect data");
    TEST_ASSERT_NULL_MESSAGE(list->tail, "tail not set to NULL");
    TEST_ASSERT_NULL_MESSAGE(list->head, "head not set to NULL");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, list->length, "list length not set correctly");
    free(data);
    destroyLinkedList(list);
}

/*
 * Test: test_get_null
 * ----------------------------
 * Test the get function handles a NULL linked list gracefully.
 */
void test_get_null(void){
    void * data = getLL(NULL, 0);
    TEST_ASSERT_NULL_MESSAGE(data, "null get call did not return null");
}

/*
 * Test: test_get_empty
 * ----------------------------
 * Test the get function handles an empty linked list gracefully.
 */
void test_get_empty(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    void * data = getLL(list, 0);
    TEST_ASSERT_NULL_MESSAGE(data, "empty list get call did not return null");
    destroyLinkedList(list);
}

/*
 * Test: test_get_out_of_lower_bounds
 * ----------------------------
 * Test the get function handles an out of lower bounds index gracefully.
 */
void test_get_out_of_lower_bounds(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    addToBackLL(list, test1);
    void * data = getLL(list, -1);
    TEST_ASSERT_NULL_MESSAGE(data, "out of lower bounds index get call did not return null");
    destroyLinkedList(list);
}

/*
 * Test: test_get_out_of_upper_bounds
 * ----------------------------
 * Test the get function handles an out of upper bounds index gracefully.
 */
void test_get_out_of_upper_bounds(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    addToBackLL(list, test1);
    void * data = getLL(list, 1);
    TEST_ASSERT_NULL_MESSAGE(data, "out of upper bounds index get call did not return null");
    destroyLinkedList(list);
}

/*
 * Test: test_get_even
 * ----------------------------
 * Test the get function with a list with an even length.
 */
void test_get_even(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'c');
    TestStruct * test4 = createTestingStruct(4, 'd');
    TestStruct * test5 = createTestingStruct(5, 'e');
    TestStruct * test6 = createTestingStruct(6, 'f');
    void * data;
    char errorString[100];

    addToBackLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);
    addToBackLL(list, test4);
    addToBackLL(list, test5);
    addToBackLL(list, test6);
    
    for(int i = 0; i < 6; i++){
        data = getLL(list, i);
        sprintf(errorString, "Failed to find the correct value for i = %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i+1, ((TestStruct*)data)->num, errorString);
    }
    destroyLinkedList(list);
}

/*
 * Test: test_get_odd
 * ----------------------------
 * Test the get function with a list with an odd length.
 */
void test_get_odd(void){
    LinkedList * list = createLinkedList(&destroyFunc, &compareFunc);
    TestStruct * test1 = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'b');
    TestStruct * test3 = createTestingStruct(3, 'c');
    TestStruct * test4 = createTestingStruct(4, 'd');
    TestStruct * test5 = createTestingStruct(5, 'e');
    TestStruct * test6 = createTestingStruct(6, 'f');
    TestStruct * test7 = createTestingStruct(7, 'g');
    void * data;
    char errorString[100];

    addToBackLL(list, test1);
    addToBackLL(list, test2);
    addToBackLL(list, test3);
    addToBackLL(list, test4);
    addToBackLL(list, test5);
    addToBackLL(list, test6);
    addToBackLL(list, test7);
    
    for(int i = 0; i < 7; i++){
        data = getLL(list, i);
        sprintf(errorString, "Failed to find the correct value for i = %d", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(i+1, ((TestStruct*)data)->num, errorString);
    }
    destroyLinkedList(list);
}

int main(void) {

    UNITY_BEGIN();
    
    //create test
    RUN_TEST(test_create_linked_list);
 
    //add tests
    RUN_TEST(test_add_to_front);
    RUN_TEST(test_add_to_front_null);
    RUN_TEST(test_add_to_back);
    RUN_TEST(test_add_to_back_null);
 
    //insert tests
    RUN_TEST(test_insert_in_empty_list);
    RUN_TEST(test_insert_out_of_lower_bounds);
    RUN_TEST(test_insert_out_of_upper_bounds);
    RUN_TEST(test_insert_at_tail);
    RUN_TEST(test_insert_at_head);
    RUN_TEST(test_insert_at_middle);

    //remove tests
    RUN_TEST(test_remove_null);
    RUN_TEST(test_remove_empty_list);
    RUN_TEST(test_remove_out_of_lower_bounds);
    RUN_TEST(test_remove_out_of_upper_bounds);
    RUN_TEST(test_remove_first_index);
    RUN_TEST(test_remove_last_index);
    RUN_TEST(test_remove_middle_index);
    RUN_TEST(test_remove_last_entry);

    //get tests
    RUN_TEST(test_get_null);
    RUN_TEST(test_get_empty);
    RUN_TEST(test_get_out_of_lower_bounds);
    RUN_TEST(test_get_out_of_upper_bounds);
    RUN_TEST(test_get_even);
    RUN_TEST(test_get_odd);
    

    return UNITY_END();
}