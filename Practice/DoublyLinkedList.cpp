`#include <iostream>
using namespace std;

class list
{
    struct node
    {
        int data;
        node *next;
        node *prev;
    };
    node *head;

public:
    list()
    {
        head = NULL;
    }

    void insert(int key)
    {
        node *newnode = new node;
        newnode->data = key;
        newnode->next = NULL;
        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            node *traverse = head;
            node *temp = head->next;
            while (temp != NULL)
            {
                temp = temp->next;
                traverse = traverse->next;
            }
            temp = newnode;
            traverse->next = temp;
            temp->prev = traverse;
        }
    }
    void display(){
        node *traverse = head;
        while(traverse != NULL){
            cout<<traverse->data<<" ";
            traverse = traverse->next;
        }
    }
};

int main(){
    list l;
    l.insert(12);
    l.insert(11);
    l.insert(14);
    l.insert(1);
    l.insert(2);
    l.insert(10);
    cout<<"\ndisplaying: ";
    l.display();

}