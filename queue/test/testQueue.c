#include "unity.h"
#include "queue.h"
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
 * Allocates and sets a structure used for testing the Queue data structure.
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

void printFunc(void * data){
    printf("%c%d", ((TestStruct*)data)->letter, ((TestStruct*)data)->num);
}

void setUp(void) {
    // set stuff up here

}

void tearDown(void) {
    // clean stuff up here
}

/*
 * Test: test_create_queue
 * ----------------------------
 * Ensure the createQueue function works as expected
 */
void test_create_queue(void){
    Queue * queue = createQueue(&destroyFunc, &printFunc);
    TEST_ASSERT_NOT_NULL_MESSAGE(queue, "createQueue returned null pointer");
    TEST_ASSERT_EQUAL_INT_MESSAGE(queue->length, 0, "queue length not defaulted to zero");
    destroyQueue(queue);
}

/*
 * Test: test_enqueue
 * ----------------------------
 * Test that items can be added to the queue
 */
void test_enqueue(void){
    TestStruct * test = createTestingStruct(1, 'a');
    Queue * queue = createQueue(&destroyFunc, &printFunc);
    TEST_ASSERT_EQUAL_INT_MESSAGE(enqueue(queue, test), 1, "enqueue failed");
    TEST_ASSERT_EQUAL_INT_MESSAGE(queue->length, 1, "enqueue did not increase queue length");
    destroyQueue(queue);

}

/*
 * Test: test_null_enqueue
 * ----------------------------
 * Test that a null queue is handled gracefully by the enqueue function
 */
void test_null_enqueue(void){
    TestStruct * test = createTestingStruct(1, 'a');
    TEST_ASSERT_EQUAL_INT_MESSAGE(enqueue(NULL, test), 0, "enqueue return incorrect error code for null queue");
    free(test);
}

/*
 * Test: test_dequeue
 * ----------------------------
 * Test that items can be removed from the queue using dequeue
 */
void test_dequeue(void){
    TestStruct * test = createTestingStruct(1, 'a');
    Queue * queue = createQueue(&destroyFunc, &printFunc);

    enqueue(queue, test);
    test = NULL;
    test = dequeue(queue);
    TEST_ASSERT_NOT_NULL_MESSAGE(test, "dequeue returned null");
    TEST_ASSERT_EQUAL_INT_MESSAGE(queue->length, 0, "queue did not track length correctly");
    free(test);
    destroyQueue(queue);
}

/*
 * Test: test_null_dequeue
 * ----------------------------
 * Test that a null queue is handled gracefully by the dequeue function
 */
void test_null_dequeue(void){
    void * data = dequeue(NULL);
    TEST_ASSERT_NULL_MESSAGE(data, "null dequeue call does not return null")
}

/*
 * Test: test_null_dequeue
 * ----------------------------
 * Test that an empty queue is handled gracefully by the dequeue function
 */
void test_empty_dequeue(void){
    Queue * queue = createQueue(&destroyFunc, &printFunc);
    TestStruct * test = createTestingStruct(1, 'a');


    void * data = dequeue(queue);
    TEST_ASSERT_NULL_MESSAGE(data, "empty dequeue call does not return null");
    enqueue(queue, test);
    data = dequeue(queue);
    free(data);
    data = dequeue(queue);
    TEST_ASSERT_NULL_MESSAGE(data, "empty dequeue call does not return null after enqueue has been called")
    destroyQueue(queue);
}

/*
 * Test: test_multiple_enqueue_dequeue
 * ----------------------------
 * Test that a queue can be dequeued to empty and requeue successfully
 */
void test_multiple_enqueue_dequeue(void){
    Queue * queue = createQueue(&destroyFunc, &printFunc);
    TestStruct * test = createTestingStruct(1, 'a');

    int num = enqueue(queue, test);
    TEST_ASSERT_EQUAL_INT_MESSAGE(num, 1, "enqueue returns failure code");
    test = dequeue(queue);
    TEST_ASSERT_NOT_NULL_MESSAGE(test, "dequeue returns null");

    num = enqueue(queue, test);
    TEST_ASSERT_EQUAL_INT_MESSAGE(num, 1, "2nd enqueue returns failure code");
    test = dequeue(queue);
    TEST_ASSERT_NOT_NULL_MESSAGE(test, "2nd dequeue returns null");
    free(test);
    destroyQueue(queue);
    
}

/*
 * Test: test_large_queue
 * ----------------------------
 * Test that a queue can handle a large amount of items.
 */
void test_large_queue(void){
    Queue * queue = createQueue(&destroyFunc, &printFunc);
    TestStruct * test;
    for(int i = 0; i < 1000000; i++){
        test = createTestingStruct(i, 'a');
        enqueue(queue, test);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(queue->length, 1000000, "Large enqueue did not work");

    for(int i = 0; i < 500000; i++){
        test = (TestStruct*)dequeue(queue);
        free(test);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(queue->length, 500000, "Large dequeue did not work");
    test = (TestStruct*)dequeue(queue);
    TEST_ASSERT_EQUAL_INT_MESSAGE(test->num, 500000, "dequeue returns wrong item");
    free(test);
    destroyQueue(queue);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_queue);
    RUN_TEST(test_enqueue);
    RUN_TEST(test_null_enqueue);
    RUN_TEST(test_dequeue);
    RUN_TEST(test_null_dequeue);
    RUN_TEST(test_empty_dequeue);
    RUN_TEST(test_multiple_enqueue_dequeue);
    RUN_TEST(test_large_queue);

    return UNITY_END();
}