#include "queue.h"

/**internal functions**/

QueueNode * createQueueNode(){
    QueueNode * node = malloc(sizeof(QueueNode));
    return node;
}

/**end internal functions**/

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
 * 
 * implementation details: initializes the length of the queue to zero,
 *      and the head and the tail to NULL.
 */
Queue * createQueue(void (*destroyFunc)(void * data), void(*printFunc)(void * data)){
    Queue * queue = malloc(sizeof(Queue));
    queue->destroyData = destroyFunc;
    queue->printData = printFunc;
    queue->length = 0;
    queue->head = NULL;
    queue->tail = NULL; 
    return queue;
}

/*
 * Function: dequeue
 * ----------------------------
 * removes the next value in the data structure and returns it.
 * 
 * queue: the queue to perform the dequeue operation on.
 * 
 * return: a void pointer of the data stored in the next position in 
 *     queue.
 * 
 * implementation details: checks if the queue is NULL or empty and
 *      removes the Node stored in the head of the queue.
 */
void * dequeue(Queue * queue){
    void * data;
    QueueNode * oldHead;
    if(queue == NULL){
        return NULL;
    }    
    if(queue->head == NULL){
        return NULL;
    }
    queue->length--;
    data = queue->head->data;
    oldHead = queue->head;
    queue->head = oldHead->next;
    if(queue->head == NULL){
        queue->tail = NULL;
    }
    free(oldHead);
    return data;
}

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
 * 
 * implementation details: checks if the queue is NULL.  Proceeds to set the
 *      data as the new tail.  If the data is the first to be added to the queue
 *      the head is set equal to the tail.
 */
int enqueue(Queue * queue, void * data){
    QueueNode * node;
    if(queue == NULL){
        return 0;
    }
    if((node = createQueueNode()) == NULL){
        return 0;
    }
    node->data = data;
    node->next = NULL;
    queue->length++;
    if(queue->tail == NULL){
        queue->tail = node;
        queue->head = node;
        return 1;
    }
    queue->tail->next=node;
    queue->tail = node;
    return 1;

}

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
 * 
 * implementation details: This functions loops throught the queue freeing the
 *      data and nodes.  Once finished it frees the queue itself.
 */
int destroyQueue(Queue * queue){
    if(queue == NULL){
        return 0;
    }
    
    QueueNode * node = queue->head;
    QueueNode * temp;
    while(node != NULL){
        if(queue->destroyData != NULL){
            queue->destroyData(node->data);
        }
        temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
    return 1;
}

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
 * implementation details: iterates through the queue printing each piece
 *      of data.
 *
 */
int printQueue(Queue * queue){
    if(queue == NULL){
        return 0;
    }
    if(queue->head == NULL){
        printf("Queue is Empty\n");
        return 1;
    }
    QueueNode * node = queue->head;
    int count = 1;
    while(node != NULL){
        printf("Entry #%d:\n", count);
        queue->printData(node->data);
        count++;
        node = node->next;
    }
    return 1;
}
