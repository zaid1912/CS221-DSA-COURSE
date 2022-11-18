#include<iostream>
using  namespace std;

// template<class T>
class list{
    private:
    struct node{
        node *next;
        node *prev;
        int data;
    };
    node *headptr;
    // node *prev;
    // node *next;
    // T data;
    // static node *headptr;

    public:

    list(){
        // headptr->next = NULL;
        // headptr->prev = NULL;
        headptr = NULL;

    }
    void insertAtHead(int key){
        node *ptrNew = new node;
        ptrNew->data = key;
        ptrNew->prev = NULL;
        ptrNew->next = headptr;
        // headptr->prev = ptrNew;
        headptr = ptrNew;
    }

    void insertAtTail(int key){ //time complexity?????
        node *temp = new node;
        temp->data = key;
        temp->next = NULL;

        node *traverse = new node;
        if(headptr == NULL){
            temp->prev = NULL;
            headptr = temp;
            return;
        }
        traverse = headptr;
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        traverse->next = temp;
        // temp->prev = traverse;
    }

    void display(){  //displays all the elements in list
        node *temp = headptr;
        do{
            cout<<temp->data<<endl;
            temp = temp->next;
        }while(temp != NULL);
    }

    // void delete_node(T key){
    //     if(headptr == NULL){
    //         cout<<"\nthe linked list is empty\n";
    //         return;
    //     }
    //     else{
    //         node *temp1 = headptr;
    //         node *temp2 = headptr->next;
    //         while(temp2->data != key || temp2 == NULL){
    //             temp1 = temp2;
    //             temp2 = temp2->next;
    //         }
    //         if(temp2->data == key){
    //             temp1->next = temp2->next;
    //             cout<<"\nnode deleted\n";
    //         }
            
    //     }
    // }
};

// node<int>* node<int>::headptr = NULL;

int main(){
        list l;
        l.insertAtHead(2);
        l.insertAtTail(1);
        l.insertAtHead(3);
        l.insertAtTail(5);
        l.display();
        cout<<endl;
        // l.delete_node(1);
        // l.display();

}
