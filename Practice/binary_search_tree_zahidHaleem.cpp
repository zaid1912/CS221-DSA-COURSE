#include<iostream>
using namespace std;

class bst{
    private:

    struct node{
        node *left;
        node *right;
        int data;
    };

    node *root;
    void destroySubTree(node *);
    void deleteNode(int, node *&);
    void makeDeletion(node *&);
    void displayInOrder(node *);
    void displayPreOrder(node *);
    void displayPostOrder(node *);

    public:

    bst(){
        root = NULL;
    }

    void InsertNode(int);
    bool searchNode(int);
    void remove(int);
    void ShowInOrder()
    {
        displayInOrder(root);
    }
    void ShowPreOrder()
    {
        displayPreOrder(root);
    }
    void ShowPostOrder()
    {
        displayPostOrder(root);
    }
};

void bst::InsertNode(int key)
{
    node *newnode = new node;
    node *traverse;

    if (this->root == NULL)
    {
        newnode->data = key;
        newnode->left = newnode->right = NULL;
        root = newnode;
        cout << "\nnode added...root\n";
    }
    else
    {
        traverse = root;
        newnode->data = key;
        newnode->left = newnode->right = NULL;
        while (traverse != NULL)
        {
            if (key < traverse->data)
            {
                if (traverse->left != NULL)
                {
                    traverse = traverse->left;
                }
                else
                {
                    traverse->left = newnode;
                    cout << "\nnode added...left\n";
                    break;
                }
            }
            else if (key > traverse->data)
            {
                if (traverse->right != NULL)
                {
                    traverse = traverse->right;
                }
                else
                {
                    traverse->right = newnode;
                    cout << "\nnode added...right\n";
                    break;
                }
            }
            else{
                cout<<"\nduplicate values cant be stored\n";
            }
        }
    }
}

void bst::displayInOrder(node *nodeptr)
{
    if (nodeptr)
    {
        displayInOrder(nodeptr->left);
        
        cout << nodeptr->data << endl;
        
        displayInOrder(nodeptr->right);
    }
}

void bst::displayPreOrder(node *nodeptr)
{
    if (nodeptr)
    {
        cout << nodeptr->data << endl;
        displayPreOrder(nodeptr->left);
        displayPreOrder(nodeptr->right);
    }
}

void bst::displayPostOrder(node *nodeptr)
{
    if (nodeptr)
    {
        displayPreOrder(nodeptr->left);
        displayPreOrder(nodeptr->right);
        cout << nodeptr->data << endl;
    }
}

bool bst::searchNode(int key)
{
    node *traverse = root;
    if (traverse == NULL)
    {
        cout << "\nthe tree is empty\n";
        return false;
    }
    else
    {
        while (traverse != NULL)
        {
            if (traverse->data == key)
            {
                return true;
            }
            else if (key < traverse->data)
            {
                traverse = traverse->left;
            }
            else
            {
                traverse = traverse->right;
            }
        }
        return false;
    }
}

void bst::remove(int key)
{
    //node_to_delete stored the node that has the same value of key. This node is returned by the function search_delete
    //checks if this node contains duplicate values, if it does then a value of count is decremented
    deleteNode(key, root);
    cout<<"\nnode deleted\n";
    
}

void bst::deleteNode(int num, node *&nodeptr){
    if(num < nodeptr->data){
        deleteNode(num, nodeptr->left);
    }
    else if(num > nodeptr->data){
        deleteNode(num, nodeptr->right);
    }
    else{
        makeDeletion(nodeptr);
    }
}

void bst::makeDeletion(node *&nodeptr){
    node *temp;
    if(nodeptr == NULL){
        cout<<"\nCannot delete empty node\n";
    }
    else if(nodeptr->right == NULL){
        temp = nodeptr;
        nodeptr = nodeptr->left;
        delete temp;
    }
    else if(nodeptr->left == NULL){
        temp = nodeptr;
        nodeptr = nodeptr->right;
        delete temp;
    }
    //if the node has two children
    else{
        //move one node to right
        temp = nodeptr->right;
        //go to the end left node 
        while(temp->left){
            temp = temp->left;
        }
        //reattach the left subtree
        temp->left = nodeptr->left;
        temp = nodeptr;
        //reattach the right subtree
        nodeptr = nodeptr->right;
        delete temp;
    }

}

int main(){
    bst t1;
    t1.InsertNode(10);
    t1.InsertNode(5);
    t1.InsertNode(12);
    t1.InsertNode(6);
    t1.ShowInOrder();
    t1.remove(5);
    t1.ShowInOrder();
}

