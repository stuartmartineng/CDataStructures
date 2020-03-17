#include "linkedList.h"

LinkedListNode * createLinkedListNode(LinkedListNode * next, LinkedListNode * prev, void * data){
    LinkedListNode * node = malloc(sizeof(LinkedListNode));
    node->next = next;
    node->prev = prev;
    node->data = data;
    return node;
}

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
LinkedList * createLinkedList(void (*destroyFunc)(void * data), int (*compareFunc)(void * a, void * b)){
    LinkedList * list = malloc(sizeof(LinkedList));
    list->destroyData = destroyFunc;
    list->compareData = compareFunc;
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

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
int addToFrontLL(LinkedList * list, void * data){
    if(list == NULL){
        return 0;
    }
    LinkedListNode * node = createLinkedListNode(NULL, list->head, data);
    if(list->head != NULL){
        list->head->next = node;
    }
    list->head = node;
    if(list->tail == NULL){
        list->tail = node;
    }
    list->length++;
    return 1;
}

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
int addToBackLL(LinkedList * list, void * data){
    if(list == NULL){
        return 0;
    }
    LinkedListNode * node = createLinkedListNode(list->tail, NULL, data);
    if(list->tail != NULL){
        list->tail->prev = node;
    }
    list->tail = node;
    if(list->head == NULL){
        list->head = node;
    }
    list->length++;
    return 1;
}

/*
 * Function: insertAtIndexLL
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
int insertAtIndexLL(LinkedList * list, void * data, int index){
    if(list == NULL){
        return 0;
    }
    if(index > list->length || index < 0){
        return 0;
    }
    LinkedListNode * node = list->head;
    LinkedListNode * newNode;
    if(index == 0  || list->head == NULL){
        return addToFrontLL(list, data);
    }
    else if(index == list->length){
        return addToBackLL(list, data);
    }
    for(int i = 1; i < index; i++){
        node = node->prev;
    }
    newNode = createLinkedListNode(node, node->prev, data);
    node->prev->next = newNode;
    node->prev = newNode;
    list->length++;
    return 1;

}

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
void * removeFromIndexLL(LinkedList * list, int index){
    if(list == NULL || index < 0 || index >= list->length){
        return NULL;
    }
    LinkedListNode * node = list->head;
    void * data;
    for(int i = 0; i < index; i++){
        node = node->prev;
    }

    if(node->next != NULL){
        node->next->prev = node->prev;
    }
    else{
        list->head = node->prev;
    }
    if(node->prev != NULL){
        node->prev->next = node->next;
    }
    else{
        list->tail = node->next;
    }
    data = node->data;
    free(node);
    list->length--;
    return data;
    

}

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
int destroyLinkedList(LinkedList * list){
    if(list == NULL){
        return 0;
    }
    LinkedListNode * node = list->head;
    LinkedListNode * temp;
    while(node != NULL){
        list->destroyData(node->data);
        temp = node->prev;
        free(node);
        node = temp;
    }
    free(list);
    return 1;
}
