#include<iostream>
using  namespace std;

template<class T>
class list{
    private:
    struct node{
        node *next;
        T data;
    };
    node *headptr;

    public:

    list(){
        headptr = NULL;
    }

    void insertAtHead(T key){
        node *newnode = new node;
        newnode->data = key;
        newnode->next = headptr;
        headptr = newnode;
        // delete newnode;
    }

    void insertAtTail(T key){ //time complexity?????
        node *temp = new node;
        node *traverse = headptr;
        temp->data = key;
        temp->next = NULL;
        if(headptr == NULL){
            headptr = temp;
            return;
        }
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        traverse->next = temp;
        // delete temp;
        // delete traverse;
    }

    void display(){  //displays all the elements in list
        node *temp = headptr;
        do{
            cout<<temp->data<<endl;
            temp = temp->next;
        }while(temp != NULL);
    }

    void delete_node(T key){
        if(headptr == NULL){
            cout<<"\nthe linked list is empty\n";
            return;
        }
        else{
            node *temp1 = headptr;
            node *temp2 = headptr->next;
            while(temp2->data != key || temp2 == NULL){
                temp1 = temp2;
                temp2 = temp2->next;
            }
            if(temp2->data == key){
                temp1->next = temp2->next;
                cout<<"\nnode deleted\n";
            }
            
        }
    }
};

int main(){
        list<int>l;
        l.insertAtHead(2);
        l.insertAtTail(1);
        l.insertAtHead(3);
        l.insertAtTail(5);
        l.display();
        cout<<endl;
        l.delete_node(1);
        l.display();

}
