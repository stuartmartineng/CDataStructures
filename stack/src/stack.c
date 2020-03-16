#include "stack.h"

/**internal functions**/

StackNode * createStackNode(StackNode * next, void * data){
    StackNode * node = malloc(sizeof(StackNode));
    node->next = next;
    node->data = data;
    return node;
}

/**end internal functions**/

/*
 * Function: createStack
 * ----------------------------
 * Creates a pointer to a stack data structures
 * 
 * destroyFunc: a function pointer that destroys the data type intended
 *      to be stored in the stack
 * 
 * return: a pointer to the created stack
 */
Stack * createStack(void (*destroyFunc)(void * data)){
    Stack * stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->destroyData = destroyFunc;
    stack->top = NULL;
    return stack;
}

/*
 * Function: push
 * ----------------------------
 * Adds new data to the top of the stack
 * 
 * stack: the stack to perform the push operation on.
 * data: the data to added to the top of the stack.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 */
int push(Stack * stack, void * data){
    if(stack == NULL){
        return 0;
    }
    StackNode * oldTop = stack->top;
    StackNode * node = createStackNode(oldTop, data);
    stack->top = node;
    stack->size++;
    return 1;
}

/*
 * Function: pop
 * ----------------------------
 * removes the item on the top of the stack and returns the data.
 * 
 * stack: the stack to perform the pop operation on.
 * 
 * return: a void pointer of the data stored in the top of the 
 *     stack.
 */
void * pop(Stack * stack){
    if(stack == NULL){
        return NULL;
    }
    if(stack->top == NULL){
        return NULL;
    }
    StackNode * node = stack->top;
    void * data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}

/*
 * Function: destroyStack
 * ----------------------------
 * Frees the stack and all data stored in the stack using the destroyData
 *      function pointer
 * 
 * stack: the stack to perform the destroy operation on.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 * 
 * note: If data is desired to be intact after the destruction of the stack
 *      pass a function pointer that does not destroy the data when initializing
 *      the stack.
 */
int destroyStack(Stack * stack){
    if(stack == NULL){
        return 0;
    }
    StackNode * node = stack->top;
    StackNode * temp;
    while(node != NULL){
        stack->destroyData(node->data);
        temp = node->next;
        free(node);
        node = temp;
    }
    free(stack);
    return 1;
}