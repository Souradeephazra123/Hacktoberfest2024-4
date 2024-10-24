// C++ program for merge sort on doubly linked list

#include <iostream>
using namespace std;

class Node {
  public:
    int data;
    Node *next;
    Node *prev;

    Node(int x) {
        data = x;
        next = NULL;
        prev = NULL;
    }
};

// Function to split the doubly linked list into two halves
Node *split(Node *head) {
    Node *fast = head;
    Node *slow = head;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->next != NULL 
           && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Split the list into two halves
    Node *temp = slow->next;
    slow->next = NULL;
    if (temp != NULL) {
        temp->prev = NULL;
    }
    return temp;
}

// Function to merge two sorted doubly linked lists
Node *merge(Node *first, Node *second) {
  
    // If either list is empty, return the other list
    if (first == NULL) {
        return second;
    }
    if (second == NULL) {
        return first;
    }

    // Pick the smaller value between first and second nodes
    if (first->data < second->data) {

        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next = merge(first->next, second);
        if (first->next != NULL) {
            first->next->prev = first;
        }
        first->prev = NULL;
        return first;
    }
    else {
        // Recursively merge the rest of the lists
        // and link the result to the current node
        second->next = merge(first, second->next);
        if (second->next != NULL) {
            second->next->prev = second;
        }
        second->prev = NULL;
        return second;
    }
}

// Function to perform merge sort on a doubly linked list
Node *MergeSort(Node *head) {
  
    // Base case: if the list is empty or has only one node, 
      // it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    Node *second = split(head);

    // Recursively sort each half
    head = MergeSort(head);
    second = MergeSort(second);

    // Merge the two sorted halves
    return merge(head, second);
}

void printList(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
      
      // Create a hard-coded doubly linked list:
    // 10 <-> 8 <-> 5 <-> 2
    Node *head = new Node(10);
    head->next = new Node(8);
    head->next->prev = head;
    head->next->next = new Node(5);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(2);
    head->next->next->next->prev = head->next->next;

    head = MergeSort(head);

    printList(head);

    return 0;
}
