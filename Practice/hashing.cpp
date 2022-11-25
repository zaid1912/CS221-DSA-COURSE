#include<iostream>
using namespace std;

class hash_list{
    private: 
    struct node{
        node *next;
        int data;
    };
    node *head;
    public:
    hash_list(){
        head = NULL;
    }
    void chaining(int key){
        node *newnode = new node;
        newnode->data = key;
        newnode->next = NULL;
        if(head == NULL){
            cout<<" inserted at head ";
            head = newnode;
            return;
        }
        else{
            node *traverse = head;
            while(traverse->next != NULL){
                traverse = traverse->next;

            }
            traverse->next = newnode;
            cout<<" inserted ";
        }
    }

    void print(){
        node *traverse = head;
        if(head == NULL){
            cout<<"empty\n";
        }
        else{
            while(traverse != NULL){
                cout<<traverse->data<<" ";
                traverse = traverse->next;
            } 
        }
    }


};
int hash_function(int key, int n){
    return(key % n);
}

void insert(int key, hash_list *map, int n){
    int hashed_index = hash_function(key, n);
    cout<<endl<<hashed_index;
    cout<<endl<<&map[hashed_index];
    map[hashed_index].chaining(key);

}

int main(){
    int n = 5;
    hash_list *map = new hash_list[5];
    insert(9, map, n);
    insert(34, map, n);
    insert(19, map, n);
    insert(23, map, n);
    insert(30, map, n);
    insert(29, map, n);
    insert(17, map, n);
    insert(2, map, n);
    insert(1, map, n);
    insert(90, map, n);
    insert(10, map, n);
    cout<<"\nstored keys: \n";
    for(int i = 0; i<n; i++){
        map[i].print();
        cout<<endl;
    }
    
    return 0;
}