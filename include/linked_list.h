// Created by Logan Richardson & Vidhi Patel on 7/25/23.

/**
 * Node structure for storing each data point
 * data: int - The data to be stored
 * next: Node_t * - Next node for the linked list, null if not needed
 * lock: pthread_mutex_t - Thread lock to control access to the node
 */
typedef struct Node_t {
    int data;
    struct Node_t * next;
    pthread_mutex_t lock;
} Node;

/**
 * Structure for creating a linked list
 * Used for the chaining resolution
 * head : Node * - Which points to the head
 * lock: pthread_mutex_t - Lock to control access to the linked list
 * size: int - Number of nodes in the linked list
 */
typedef struct Linked_List_t {
    Node * head;
    int size;
    pthread_mutex_t lock;
} LinkedList;

// Node Methods
Node* node_create(int data, Node *next);

void node_destroy(Node *node);

// Linked List Methods
LinkedList* linked_list_create();

void linked_list_destroy(LinkedList *list);

void linked_list_insert(LinkedList *list, int data);

void linked_list_in_order_insert(LinkedList *list, int data);

void linked_list_in_order_insert_with_hand_over_hand_locking(LinkedList * list, int data);

void linked_list_in_order_insert_with_cas(LinkedList *list, int data);

void linked_list_remove(LinkedList *list, int data);

void linked_list_print(LinkedList *list);


