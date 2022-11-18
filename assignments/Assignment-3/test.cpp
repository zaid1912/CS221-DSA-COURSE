#include<iostream>
using namespace std;

class BST{
    private:
    struct node{
        int data;
        node *left = NULL;
        node *right = NULL;
        int count = 0;
    };
    node *root;
    public:

    BST(){
        root = NULL;
    }

    void InsertNode(int key){
        node *newnode = new node;
        node *traverse;

        if(this->root == NULL){
            newnode->data = key;
            newnode->count++;
            newnode->left = newnode->right = NULL;
            root = newnode;
            cout<<"\nnode added...root\n";
        }
        else{
            traverse = root;
            newnode->data = key;
            while(traverse != NULL){
                if(traverse->data == key){
                    traverse->count++;
                    // traverse->left = traverse->right = NULL;
                    cout<<"\nduplicate value is stored..."<<key<<endl;
                    break;
                }
                else if(key < traverse->data){
                    if(traverse->left != NULL){
                        traverse = traverse->left;
                        if(traverse->data == key){
                            traverse->count++;
                            cout<<"\nduplicate value is stored..."<<key<<endl;
                            break;
                        }
                    }
                    else{
                        traverse->left = newnode;
                        cout<<"\nnode added...left\n";
                        break;
                    }

                }
                else if(key > traverse->data){
                    if(traverse->right != NULL){
                        traverse = traverse->right;
                        if(traverse->data == key){
                            traverse->count++;
                            cout<<"\nduplicate value is stored..."<<key<<endl;
                            break;
                        }
                    }
                    else{
                        traverse->right = newnode;
                        cout<<"\nnode added...right\n";
                        break;
                    }
                }
            }

        }
    }
    
};

int main(){
    BST tree;
    tree.InsertNode(20);
    tree.InsertNode(24);
    tree.InsertNode(12);
    tree.InsertNode(20);
    tree.InsertNode(12);
    tree.InsertNode(16);
    tree.InsertNode(21);
    tree.InsertNode(22);
    tree.InsertNode(21);
    return 0;
}