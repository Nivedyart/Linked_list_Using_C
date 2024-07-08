#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next; 
};



// Function to create a new node
void createNode(int data, struct Node** head_ref) { 
    // Corrected the function definition to match the declaration.
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // Create new node
    newNode->data = data;      // Assign data
    newNode->next = NULL;      // Set next to NULL

    struct Node* last = *head_ref;  // Removed the extra underscore from the name 'head_ref'

    if (*head_ref == NULL) {
        *head_ref = newNode;       // Correct the node reference (new_node -> newNode)
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;           // Correct the node reference (new_node -> newNode)
}

//delete a node at a given position
void deleteAtPosition(struct Node** headRef, int position) {
    if (*headRef == NULL) { // Handle empty list case
        return; 
    }

    struct Node* temp = *headRef;

    // Special case: Delete head node (position = 0)
    if (position == 0) {
        *headRef = temp->next; // Change head to the next node
        free(temp);           // Free the old head
        return;
    }

    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If position is more than the number of nodes
    if (temp == NULL || temp->next == NULL) {
        return; 
    }

    // Node temp->next is the node to be deleted
    struct Node* next = temp->next->next;

    // Unlink the node to be deleted
    free(temp->next); 

    // Relink the remaining nodes
    temp->next = next;
}

// Function to delete all occurrences of a given key
void deleteAllOccurrences(struct Node** headRef, int key) {
    struct Node* current = *headRef;
    struct Node* prev = NULL;

    while (current != NULL) {
        // Check if the current node needs to be deleted
        if (current->data == key) {
            // If deleting the head node
            if (prev == NULL) {
                *headRef = current->next; 
            } else {
                prev->next = current->next; // Bypass the current node
            }
            struct Node* temp = current; // Store the current node temporarily
            current = current->next;      // Move to the next node
            free(temp);                   // Free the deleted node
        } else {
            prev = current;           // Update prev if not deleting
            current = current->next;  // Move to the next node
        }
    }
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n"); 
}
//delete the entire linked list
void deleteList(struct Node** headRef) {
    struct Node* current = *headRef;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next; // Store the next node before freeing
        free(current);           // Free the current node's memory
        current = nextNode;       // Move to the next node
    }

    *headRef = NULL; // Set head to NULL to indicate an empty list
}
//display the inverted linked list
void displayReverseIterative(struct Node* head) {
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;

    // Reverse the list
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev; // Update the head to point to the reversed list
    displayList(head); // Now display the reversed list
}


// Function to calculate the total memory space occupied by the list
size_t totalMemorySpace(struct Node* head) {
    size_t total = 0;
    struct Node* current = head;

    while (current != NULL) {
        total += sizeof(struct Node);
        current = current->next;
    }

    return total;
}

void deleteNodesFromData(struct Node** headRef, int targetData) {
    struct Node *current = *headRef;
    struct Node *prev = NULL;

    // Find the first node with the target data (or the end of the list)
    while (current != NULL && current->data != targetData) {
        prev = current;
        current = current->next;
    }

    // If the target data is not found, nothing to delete
    if (current == NULL) {
        return;
    }

    // Delete the remaining nodes starting from the target node
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }

    // Update the head pointer if needed
    if (prev == NULL) {
        *headRef = NULL; // Target data was in the first node
    } else {
        prev->next = NULL; // Disconnect the remaining list from the deleted part
    }
}

int main() {
    struct Node* head = NULL;

    // Create a linked list (e.g., 1 -> 3 -> 2 -> 3 -> 5)
    createNode(9, &head);
    createNode(7, &head);
    createNode(1, &head);
    createNode(3, &head);
    createNode(2, &head);
    createNode(3, &head);
    createNode(5, &head);

    printf("\n----- Original Linked List -----\n");
    displayList(head);
    printf("\n");

    // Memory space occupied:
    printf("Total memory space occupied by the list: %zu bytes\n\n", totalMemorySpace(head));


    // Delete at a specific position (e.g., position 2, which would be data 2)
    deleteAtPosition(&head, 2);
    printf("----- List after deleting node at position 2 -----\n");
    displayList(head);
    printf("\n");

    // Delete all occurrences of a value (e.g., data 3)
    deleteAllOccurrences(&head, 3);
    printf("----- List after deleting all occurrences of 3 -----\n");
    displayList(head);
    printf("\n");

    // Delete all nodes starting from data 2
    int targetData = 2;
    deleteNodesFromData(&head, targetData);
    printf("----- List after deleting all nodes from data %d onwards -----\n", targetData);
    displayList(head);
    printf("\n");

       // Reverse and display:
    printf("----- Inverted Linked List (Iterative) -----\n");
    displayReverseIterative(head);
    printf("\n");

    // Delete the entire list to clean up memory
    deleteList(&head);
    printf("----- List after complete deletion -----\n");
    displayList(head); // Should print "NULL"
    printf("\n");

    return 0;
}