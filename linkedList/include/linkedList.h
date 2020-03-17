#include <stdlib.h>
#include <stdio.h>

/*
 * Struct: Node
 * ----------------------------
 * A struct that holds the data of the stack.  A new Node is
 *      created for each item added to the linked list
 *      
 * next: the next item in the linked list
 * prev: the previous item stored in the linked list
 * data: the data stored in the Node
 * 
 */
typedef struct linkedListNode{
    struct linkedListNode * next;
    struct linkedListNode * prev;
    void * data;
}LinkedListNode;

/*
 * Struct: LinkedList
 * ----------------------------
 * Represents a Linked List data structure.
 *      
 * head: the front of the linked list; index 0.
 * tail: the end of the linked list
 * destroyData: a function pointer that is used to free the data
 *      stored in the linked list
 * compareData: a function pointer that is used to compare two items
 *      in the linked list
 * 
 */
typedef struct linkedList{
    LinkedListNode * head;
    LinkedListNode * tail;
    void (*destroyData)(void * data);
    int (*compareData)(void * a, void * b);
    int length;
}LinkedList;

/*
 * Function: createLinkedList
 * ----------------------------
 * Creates a pointer to a linked list data structures
 * 
 * destroyFunc: a function pointer that destroys the data type intended
 *      to be stored in the stack
 * compareFunc: a function pointer that compares two of the intended data type.
 * 
 * return: a pointer to the created linked list
 */
LinkedList * createLinkedList(void (*destroyFunc)(void * data), int (*compareFun)(void * a, void * b));

/*
 * Function: addToFrontLL
 * ----------------------------
 * Adds new data to the front of the list
 * 
 * list: the linked list to perform the add to front operation on.
 * data: the data to added to the front of the list.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 */
int addToFrontLL(LinkedList * list, void * data);

/*
 * Function: addToBackLL
 * ----------------------------
 * Adds new data to the back of the list
 * 
 * list: the linked list to perform the add to back operation on.
 * data: the data to added to the back of the list.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 */
int addToBackLL(LinkedList * list, void * data);

/*
 * Function: addToBackLL
 * ----------------------------
 * Adds new data to the position of the index
 * 
 * list: the linked list to perform the insert operation on.
 * data: the data to be inserted.
 * index: the index of where to insert the data
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 */
int insertAtIndexLL(LinkedList * list, void * data, int index);

/*
 * Function: removeFromIndexLL
 * ----------------------------
 * removes item from position of the index and returns it.
 * 
 * list: the linked list to perform the remove operation on.
 * index: the index of the data to be removed.
 * 
 * return: a pointer of the data of the removed item.
 */
void * removeFromIndexLL(LinkedList * list, int index);


/*
 * Function: destroyLinkedList
 * ----------------------------
 * Frees the linked list and all data stored in the linked list using
 *      the destroyData function pointer
 * 
 * list: the linked list to perform the destroy operation on.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 * 
 * note: If data is desired to be intact after the destruction of the stack
 *      pass a function pointer that does not destroy the data when initializing
 *      the stack.
 */
int destroyLinkedList(LinkedList * list);