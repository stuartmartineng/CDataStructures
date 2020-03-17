#include <stdlib.h>
#ifndef STACK_H
#define STACK_H
/*
 * Struct: Node
 * ----------------------------
 * A data structure that holds the data of the stack.  A new Node is
 *      created for each item added to the stack
 *      
 * next: the next item in the stack
 * data: the data stored in the Node
 * 
 */
typedef struct stackNode{
    struct stackNode * next;
    void * data;
}StackNode;

/*
 * Struct: Stack
 * ----------------------------
 * Represents a LIFO stack data structure.
 *      
 * head: The top of the stack.
 * destroyData: A function pointer that is used to free the data
 *      stored in the Stack.
 * 
 */
typedef struct stack{
    StackNode * top;
    void (*destroyData)(void * data);
    int size;

}Stack;


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
Stack * createStack(void (*destroyFunc)(void * data));

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
int push(Stack * stack, void * data);

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
void * pop(Stack * stack);

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
int destroyStack(Stack * stack);

#endif
