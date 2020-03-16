#include "unity.h"
#include "stack.h"
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
void test_create_stack(void){
    Stack * stack = createStack(&destroyFunc);
    TEST_ASSERT_NOT_NULL_MESSAGE(stack, "createStack returned null pointer");
    TEST_ASSERT_EQUAL_INT_MESSAGE(stack->size, 0, "stack size not defaulted to zero");
    destroyStack(stack);
}

/*
 * Test: test_push
 * ----------------------------
 * Test the push function works as expected.
 */
void test_push(void){
    Stack * stack = createStack(&destroyFunc);
    TestStruct * test = createTestingStruct(1, 'a');

    int code = push(stack, test);

    TEST_ASSERT_NOT_NULL_MESSAGE(stack->top, "top of stack is NULL after push");
    TEST_ASSERT_NOT_NULL_MESSAGE(stack->top->data, "data not stored in stack");
    TEST_ASSERT_EQUAL_INT_MESSAGE(((TestStruct*)stack->top->data)->num, 1, "incorrect data stored in stack");
    TEST_ASSERT_EQUAL_INT_MESSAGE(stack->size, 1, "incorrect stack size after push");
    TEST_ASSERT_EQUAL_INT_MESSAGE(code, 1, "incorrect status code return from push");

    destroyStack(stack);
}

/*
 * Test: test_null_push
 * ----------------------------
 * Test the push function handles a NULL stack gracefully.
 */
void test_null_push(void){
    TestStruct * test = createTestingStruct(1, 'a');
    int code = push(NULL, test);
    TEST_ASSERT_EQUAL_INT_MESSAGE(code, 0, "incorrect status code return from push");
    free(test);
}

/*
 * Test: test_pop
 * ----------------------------
 * Test the push function handles a NULL stack gracefully.
 */
void test_pop(void){
    TestStruct * test = createTestingStruct(1, 'a');
    TestStruct * test2 = createTestingStruct(2, 'a');
    Stack * stack = createStack(&destroyFunc);

    push(stack, test);
    push(stack, test2);

    test = pop(stack);

    TEST_ASSERT_NOT_NULL_MESSAGE(test, "pop returned NULL");
    TEST_ASSERT_EQUAL_INT_MESSAGE(stack->size, 0, "count incorrect after pop");
    TEST_ASSERT_EQUAL_INT_MESSAGE(test->num, 2, "pop returned incorrect data");
    destroyStack(stack);
    free(test);
}

/*
 * Test: test_null_pop
 * ----------------------------
 * Test the pop function handles a NULL stack gracefully.
 */
void test_null_pop(void){
    void * data = pop(NULL);
    TEST_ASSERT_NULL_MESSAGE(data, "pop returned did not return NULL for NULL stack");
}

/*
 * Test: test_null_pop
 * ----------------------------
 * Test the pop function handles a empty stack gracefully.
 */
void test_empty_pop(void){
    Stack * stack = createStack(&destroyFunc);
    void * data = pop(stack);
    TEST_ASSERT_NULL_MESSAGE(data, "pop returned did not return NULL for empty stack");
    TEST_ASSERT_EQUAL_INT_MESSAGE(stack->size, 0, "size of stack is incorrect after pop on empty stack");
    destroyStack(stack);
}

/*
 * Test: test_multiple_pop_push
 * ----------------------------
 * Test that a stack can be popped to empty and repushed successfully
 */
void test_multiple_pop_push(void){
    TestStruct * test = createTestingStruct(1, 'a');
    Stack * stack = createStack(&destroyFunc);
    push(stack, test);
    test = pop(stack);
    push(stack, test);
    test = pop(stack);

    TEST_ASSERT_NOT_NULL_MESSAGE(test, "2nd pop return NULL");
    TEST_ASSERT_EQUAL_INT_MESSAGE(test->num, 1, "2nd pop return incorrect data");
    free(test);
    destroyStack(stack);


}

/*
 * Test: test_large_stack
 * ----------------------------
 * Test that a stack can handle a large amount of items.
 */
void test_large_queue(void){
    Stack * stack = createStack(&destroyFunc);
    TestStruct * test;

    for(int i = 0; i < 1000000; i++){
        test = createTestingStruct(i, 'a');
        push(stack, test);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(1000000, stack->size, "stack size incorrect after massive push");
    test = pop(stack);
    TEST_ASSERT_NOT_NULL_MESSAGE(test, "pop returns null after massive push");
    TEST_ASSERT_EQUAL_INT_MESSAGE(999999, test->num, "incorrect pop return after massive push");

    for(int i = 0; i < 250000; i++){
        free(test);
        test = pop(stack);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(749999, stack->size, "stack size incorrect after massive pop");
    TEST_ASSERT_EQUAL_INT_MESSAGE(749999, test->num, "incorrect pop return after massive pop");
    free(test);
    destroyStack(stack);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_stack);
    RUN_TEST(test_push);
    RUN_TEST(test_null_push);
    RUN_TEST(test_push);
    RUN_TEST(test_null_pop);
    RUN_TEST(test_empty_pop);
    RUN_TEST(test_multiple_pop_push);
    RUN_TEST(test_large_queue);

    return UNITY_END();
}