#include <iostream>

using std::cout;
using std::endl;

template<class T>

class Stack 
{
    struct Node {
        T data;
        Node *next;

        Node(T data) {
            this->data = data;
        }
    };

    Node *head = nullptr;
    Node *curr;
    int size = 0;

public:

    void push(T data) {
        Node *newnode = new Node(data);

        newnode->next = head;
        head = newnode;
        
        size++;
    }

    T pop() {
        
        T x = -1;

        if(isEmpty()) {
            return x;
        }else if(size == 1) {
            x = head->data;
            delete head;
            head = nullptr;

            size--;
            return x;
        }else {
            Node *temp = head;
            head = head->next;
            x = temp->data;
            delete temp;
            temp = nullptr;

            size--;
            return x;
        }
    }

    T peek(int index) {

        if(index < 1 || index > size)
            return -1;
        else {
            curr = head;

            for(int i = 0; i < index - 1; i++) 
                curr = curr->next;

            
            return ((curr != nullptr) ? curr->data : -1);
        }
    }

    T stackTop(){return ((isEmpty()) ? -1 : head->data);}
    bool isEmpty(){return head == nullptr;}
};
