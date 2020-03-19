#include "linkedList.h"

/**internal functions**/

LinkedListNode * createLinkedListNode(LinkedListNode * next, LinkedListNode * prev, void * data){
    LinkedListNode * node = malloc(sizeof(LinkedListNode));
    node->next = next;
    node->prev = prev;
    node->data = data;
    return node;
}

/*
 * Function: merge
 * ----------------------------
 * merges two sorted list of items into one sorted list of items.
 * This function is used by the mergeSort function
 * 
 * list: The list structure that contains the comparison function that
 *      should be used for comparison
 * a: The first sorted list to be merged.
 * b: The second sorted list to be merged
 * 
 * return: a merged sorted list
 */
LinkedListNode * merge(LinkedList * list, LinkedListNode * a, LinkedListNode * b){
    LinkedListNode * node = createLinkedListNode(NULL, NULL, NULL);
    LinkedListNode * head = node;
    while(a != NULL || b != NULL){
        if(b == NULL || (a != NULL && list->compareData(a->data, b->data) < 0)){
            node->prev = a;
            a = a->prev;
        }
        else{
            node->prev = b;
            b = b->prev;
        }
        node->prev->next = node;
        node = node->prev;        
    }
    head->prev->next = NULL;
    list->tail = node;
    node = head->prev;
    free(head);
    return node;
}

/*
 * Function: split
 * ----------------------------
 * splits a unsorted list into two unsorted list
 * 
 * node: the head of the list to be sorted.
 * 
 * return: the head of the second list
 * note: the pointer originally passed into the function acts
 *      as the first lists head after splitting.
 */
LinkedListNode * split(LinkedListNode * node){
    LinkedListNode * half = node;
    LinkedListNode * full = node;
    while(full->prev != NULL && full->prev->prev != NULL){
        half = half->prev;
        full = full->prev->prev;
    }
    half = half->prev;
    half->next->prev = NULL;
    half->next = NULL;

    return half;
}

/*
 * Function: mergeSort
 * ----------------------------
 * sorts a doubly linked list using the mergesort algorithm
 * 
 * list: the linked list data structure to be sorted.
 * first: the head of an unsorted list that must be sorted.
 * 
 * return: the list passed in using first after sorting.
 */
void * mergeSort(LinkedList * list, LinkedListNode * first){
    LinkedListNode * second;

    if(first == NULL || first->prev == NULL){
        return first;
    }

    second = split(first);

    first = mergeSort(list, first);
    second = mergeSort(list, second);


    first = merge(list, first, second);
    return first;
}

/**end internal functions**/

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
    list->sorted = 1;
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
    if(list->length > 1){
        list->sorted = 0;
    }
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
    if(list->length > 1){
        list->sorted = 0;
    }
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
    if(list->length > 1){
        list->sorted = 0;
    }
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
    if(list->length < 2){
        list->sorted = 1;
    }
    return data;
}

/*
 * Function: getLL
 * ----------------------------
 * retrieve the item at the given index.
 * 
 * list: the linked list to perform the get operation on.
 * index: the index of the data to be retreive.
 * 
 * return: a pointer of the data at the given index.
 */
void * getLL(LinkedList * list, int index){
    if(list == NULL || index < 0 || index > list->length - 1 || list->head == NULL){
        return NULL;
    }
    LinkedListNode * node;
    if(index > list->length/2){
        node = list->tail;
        for(int i = list->length - 1; i > index; i--){
            node = node->next;
        }
    }
    else{
        node = list->head;
        for(int i = 0; i < index; i++){
            node = node->prev;
        }
    }
    return node->data;
}

/*
 * Function: searchLL
 * ----------------------------
 * Sequentially checks each item.
 * 
 * list: the linked list to perform the search operation on.
 * data: the item to be found.
 * 
 * return: the index of the item searched for.  -1 if not found.
 */
int searchLL(LinkedList * list, void * data){
    if(list == NULL){
        return -1;
    }
    int count = 0;
    LinkedListNode * node = list->head;
    while(node != NULL){
        if(list->compareData(data, node->data) == 0){
            return count; 
        }
        node = node->prev;
        count++;
    }
    return -1;
}

/*
 * Function: insertSortedLL
 * ----------------------------
 * insert an item into a sorted list.
 * 
 * list: the linked list to perform the insert operation on.
 * data: the item to be inserted into the list.
 * 
 * return: the index the item was inserted to.  -1 if failed.
 */
int insertSortedLL(LinkedList * list, void * data){
    if(list == NULL || list->sorted == 0){
        return -1;
    }
    LinkedListNode * node = list->head;
    LinkedListNode * newNode;
    int index = 0;
    while(node != NULL){
        if(list->compareData(node->data, data) > 0){
            newNode = createLinkedListNode(node->next, node, data);
            if(node->next == NULL){
                list->head = newNode;
            }
            else{
                node->next->prev = newNode;
            }
            node->next = newNode;
            list->length++;
            return index;
        }
        index++;
        node = node->prev;
    }
    addToBackLL(list, data);
    list->sorted = 1;
    return index;
}

/*
 * Function: sortLL
 * ----------------------------
 * Sorts the linked list using a merge sort algorithm
 * 
 * list: the linked list to perform sort operation on.
 * 
 * return: 1 if sucessful. 0 if failed.
 */
int sortLL(LinkedList * list){
    if(list == NULL){
        return 0;
    }
    list->head = mergeSort(list, list->head);
    list->sorted = 1;
    return 1;    
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