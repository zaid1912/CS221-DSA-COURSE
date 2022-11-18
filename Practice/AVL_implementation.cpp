#include <iostream>
using namespace std;

class AVL
{
private:
    struct node
    {
        int data;
        node *left;
        node *right;
        int height;

        node()
        {
            left = NULL;
            right = NULL;
            height = 0;
        }
    };
    node *root;

    void displayInOrder(node *nodeptr)
    {
        if (nodeptr)
        {
            displayInOrder(nodeptr->left);
            cout << nodeptr->data << " ";
            displayInOrder(nodeptr->right);
        }
    }
    void displayPreOrder(node *nodeptr)
    {
        if (nodeptr)
        {
            cout << nodeptr->data << " ";
            displayPreOrder(nodeptr->left);
            displayPreOrder(nodeptr->right);
        }
    }

public:
    AVL()
    {
        root = NULL;
    }

    int height(node *nodeptr)
    {
        if (nodeptr == NULL)
        {
            return -1;
        }
        else
        {
            return nodeptr->height;
        }
    }

    int Max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    node *SingleRotateWithLeft(node *k2)
    {
        node *k1 = new node;
        k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = Max(height(k2->left), height(k2->right)) + 1;
        k1->height = Max(height(k1->left), k2->height) + 1;
        return k1;
    }

    node *SingleRotateWithRight(node *k1)
    {
        node *k2 = new node;
        k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = Max(height(k1->left), height(k1->right)) + 1;
        k2->height = Max(height(k2->right), k1->height) + 1;
        return k2;
    }

    node *DoubleRotateWithLeft(node *k3)
    {
        k3->left = SingleRotateWithRight(k3->left);
        return SingleRotateWithLeft(k3);
    }

    node *DoubleRotateWithRight(node *k1)
    {
        k1->right = SingleRotateWithLeft(k1->right);
        return SingleRotateWithRight(k1);
    }

    node *insert_node(int key, node *nodeptr)
    {
        // cout<<"a";
        if (nodeptr == NULL)
        {
            nodeptr = new node;
            nodeptr->data = key;
        }
        else
        {
            if (key < nodeptr->data)
            {
                nodeptr->left = insert_node(key, nodeptr->left);
                if (height(nodeptr->left) - height(nodeptr->right) == 2)
                {
                    if (key < nodeptr->left->data)
                    {
                        nodeptr = SingleRotateWithLeft(nodeptr);
                    }
                    else
                    {
                        nodeptr = DoubleRotateWithLeft(nodeptr);
                    }
                }
            }
            else
            {
                if (key > nodeptr->data)
                {
                    nodeptr->right = insert_node(key, nodeptr->right);
                    if (height(nodeptr->right) - height(nodeptr->left) == 2)
                    {
                        if (key > nodeptr->right->data)
                        {
                            nodeptr = SingleRotateWithRight(nodeptr);
                        }
                        else
                        {
                            nodeptr = DoubleRotateWithRight(nodeptr);
                        }
                    }
                }
            }
        }
        nodeptr->height = Max(height(nodeptr->left), height(nodeptr->right)) + 1;
        return nodeptr;
    }

    void insertion(int key)
    {
        root = insert_node(key, root);
    }

    void showInOrder()
    {
        displayInOrder(root);
    }
    void showPreOrder()
    {
        displayPreOrder(root);
    }
};

int main()
{
    AVL a;
    a.insertion(3);
    a.insertion(2);
    a.insertion(1);
    a.insertion(4);
    a.insertion(5);
    a.insertion(6);
    a.insertion(7);
    a.showPreOrder();
}