#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node()
    {
        data = 0;
        next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class LinkedList{
public:
    Node* head;
    LinkedList()
    {
        head = NULL;
    }

    void insertItem(int data)
    {

        Node* newNode = new Node(data);
        if(head == NULL)
        {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        return;
    }

    void printList()
    {
        Node* temp = head;
        if (head == NULL)
        {
            cout<<"0"<<endl;
            return;
        }

        while(temp != NULL)
        {
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        return;
    }

    void addToItem(int value, int loc)
    {
        Node* temp = head;
        for(int i = 0; i < loc; i++)
        {
            temp = temp->next;
        }
        temp->data = temp->data + value;
        return;
    }

    int getItem(int loc)
    {
        Node* temp = head;
        for (int i = 0; i < loc; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }

};
