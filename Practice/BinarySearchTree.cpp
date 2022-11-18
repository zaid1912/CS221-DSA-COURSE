#include<iostream>
using namespace std;

class tree{
    struct node{
        int data;
        node *right;
        node *left;
        node(){
            data = 0;
            right = NULL;
            left = NULL;
        }
    };

    public:
    node *root;

    tree(){
        root = NULL;
    }

    void insert(int key){
        node *temp = root;
        node *new_node = new node;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->data = key;

        if(root == NULL){
            root = new_node;
        }
        else{
            while(temp != NULL){
                if(key < temp->data){
                    if(temp->left){
                        temp = temp->left;
                    }
                    else{
                        temp->left = new_node;
                        return;
                    }
                }
                else if(key > temp->data){
                    if(temp->right){
                        temp = temp->right;
                    }
                    else{
                        temp->right = new_node;
                        break;
                    }
                }
                else{
                    cout<<"\ncant enter duplicate values\n";
                    
                }
            }
        }
    }

    void display_in_order(node *nodeptr = root){
        if(nodeptr){
            display_in_order(nodeptr->left);
            cout<<nodeptr->data;
            display_in_order(nodeptr->right);
        }

    }

};

int main(){
    tree t;
    t.insert(10);
    t.insert(22);
    t.insert(33);
    t.insert(5);
    t.insert(68);
    t.insert(-1);
    t.insert(8);

    t.display_in_order();
}