#include <stdlib.h>
#include <stdio.h>

/*
 * Struct: Node
 * ----------------------------
 * A data structure that holds the data of queue.  A new Node is
 *      created for each value added to the queue
 *      
 * next: the next node in the queue
 * data: the data stored in the Node
 * 
 */
typedef struct queueNode{
    struct queueNode * next;
    void * data;
}QueueNode;

/*
 * Struct: Queue
 * ----------------------------
 * Represents the Queue data structure.
 *      
 * head: The first Node in the queue and the next to be removed.
 * tail: The last Node in the queue and the last to be removed.
 * destroyData: A function pointer that is used to free the data
 *      stored in the Queue.
 * printData: A function pointer used to print the data in the Queue.
 * 
 */
typedef struct queue{
    QueueNode * head;
    QueueNode * tail;
    void (*destroyData)(void * data);
    void (*printData)(void * data);
    int length;

}Queue;


/*
 * Function: createQueue
 * ----------------------------
 * Creates a pointer to a queue data structures
 * 
 * destroyFunc: a function pointer that destroys the data type intended
 *      to be stored in the queue
 * printFunc: a function pointer that prints the data type intended to
 *      be stored in the queue
 * 
 * return: a pointer to the created queue
 */
Queue * createQueue(void (*destroyFunc)(void * data), void(*printFunc)(void * data));

/*
 * Function: dequeue
 * ----------------------------
 * removes the next value in the data structure and returns it.
 * 
 * queue: the queue to perform the dequeue operation on.
 * 
 * return: a void pointer of the data stored in the next position in 
 *     queue.
 */
void * dequeue(Queue * queue);

/*
 * Function: enqueue
 * ----------------------------
 * Adds new data to the end of the queue
 * 
 * queue: the queue to perform the enqueue operation on.
 * data: the data to added to the end of the queue.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 */
int enqueue(Queue * queue, void * data);

/*
 * Function: destroyQueue
 * ----------------------------
 * Frees the queue and all data stored in the queue using the destroyData
 *      function pointer
 * 
 * queue: the queue to perform the destroy operation on.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 * 
 * note: If data is desired to be intact after the destruction of the queue
 *      pass a function pointer that does not destroy the data when initializing
 *      the queue.
 */
int destroyQueue(Queue * queue);

/*
 * Function: printQueue
 * ----------------------------
 * prints all of the data in the queue as per the printData funtion pointer
 * 
 * queue: the queue to perform the print operation on.
 * 
 * return: an integer indicating the success or failure of the operation
 * 0: failure
 * 1: success
 *
 */
int printQueue(Queue * queue);


