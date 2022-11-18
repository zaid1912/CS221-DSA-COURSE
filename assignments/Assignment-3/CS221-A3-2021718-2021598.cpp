/*
 * File: Assignment-3
 *
 * Author-1: Shehryar Ahmad (2021598)
 * Author-2: Zaid Bin Muzammil (2021718)
 *
 * Description: Binary Search Tree plus(same value can be stored multiple times)
*/

#include <iostream>
using namespace std;

class BST
{
private:
    struct node
    {
        int data;
        node *left = NULL;
        node *right = NULL;
        int count = 0;
    };

    node *root;
    void destroySubTree(node *);
    void deleteNode(int, node *&);
    void makeDeletion(node *&);
    void displayInOrder(node *);
    void displayPreOrder(node *);
    void displayPostOrder(node *);
    node* search_delete(int);

public:
    // constructor
    BST()
    {
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
/**
 * @brief adds a new value to the tree. constructs a new node of struct type node and traverses through the tree(goes left or right) depending upon the value of the parameter and adds the new node such that the tree remains binary search. the count variable of the node is incremented if the key is already stored
 * 
 * @param key the integer value that needs to be added to the tree
 */
void BST::InsertNode(int key)
{
    node *newnode = new node;
    node *traverse;

    if (this->root == NULL)
    {
        newnode->data = key;
        newnode->count++;
        newnode->left = newnode->right = NULL;
        root = newnode;
        cout << "\nnode added...root\n";
    }
    else
    {
        traverse = root;
        newnode->data = key;
        while (traverse != NULL)
        {
            if (traverse->data == key)
            {
                traverse->count++;
                // traverse->left = traverse->right = NULL;
                cout << "\nduplicate value is stored..." << key << endl;
                break;
            }
            else if (key < traverse->data)
            {
                if (traverse->left != NULL)
                {
                    traverse = traverse->left;
                    if (traverse->data == key)
                    {
                        traverse->count++;
                        cout << "\nduplicate value is stored..." << key << endl;
                        break;
                    }
                }
                else
                {
                    newnode->count++;
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
                    if (traverse->data == key)
                    {
                        traverse->count++;
                        cout << "\nduplicate value is stored..." << key << endl;
                        break;
                    }
                }
                else
                {
                    newnode->count++;
                    traverse->right = newnode;
                    cout << "\nnode added...right\n";
                    break;
                }
            }
        }
    }
}
/**
 * @brief displays the current values of the tree such that the values are in order...This is done by recursion. displays the node number of times its count value is. Let's suppose if a value is stored thrice(duplicate values) then that value will be printed thrice.
 * 
 * @param nodeptr initaially we are calling ShowInOrder public member function that calls this function with a parameter bein the reference to the root of the tree and each time this function is called recursively, the pointer parameter is changed depending upon the traversing node values
 */
void BST::displayInOrder(node *nodeptr)
{
    if (nodeptr)
    {
        displayInOrder(nodeptr->left);
        for (int i = 0; i < nodeptr->count; i++)
        {
            cout << nodeptr->data << endl;
        }
        displayInOrder(nodeptr->right);
    }
}
/**
 * @brief displays the current values of the tree such that the values are pre order...This is done by recursion. displays the node number of times its count value is. Let's suppose if a value is stored thrice(duplicate values) then that value will be printed thrice.
 * 
 * @param nodeptr initaially we are calling ShowPreOrder public member function that calls this function with a parameter bein the reference to the root of the tree and each time this function is called recursively, the pointer parameter is changed depending upon the traversing node values
 */
void BST::displayPreOrder(node *nodeptr)
{
    if (nodeptr)
    {
        for (int i = 0; i < nodeptr->count; i++)
        {
            cout << nodeptr->data << endl;
        }
        displayPreOrder(nodeptr->left);
        displayPreOrder(nodeptr->right);
    }
}
/**
 * @brief displays the current values of the tree such that the values are post order...This is done by recursion. displays the node number of times its count value is. Let's suppose if a value is stored thrice(duplicate values) then that value will be printed thrice.
 * 
 * @param nodeptr initaially we are calling ShowPostOrder public member function that calls this function with a parameter bein the reference to the root of the tree and each time this function is called recursively, the pointer parameter is changed depending upon the traversing node values
 */
void BST::displayPostOrder(node *nodeptr)
{
    if (nodeptr)
    {
        displayPreOrder(nodeptr->left);
        displayPreOrder(nodeptr->right);
        for (int i = 0; i < nodeptr->count; i++)
        {
            cout << nodeptr->data << endl;
        }
    }
}
/**
 * @brief traverses through the tree and checks if the tree is empty, if not it checks whether the passed parameter is stored somewhere in the tree
 * 
 * @param key the value that needs to be seached for
 * @return true if the value is found 
 * @return false if the value is not found
 */
bool BST::searchNode(int key)
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
/**
 * @brief traverses through the tree and find the node whose value matches the passed parameter. This function is called from another function(remove())
 * 
 * @param key the value that needs to be deleted
 * @return BST::node* returns the node that needs to be deleted
 */
BST::node* BST::search_delete(int key)
{
    node *traverse = root;
    while (traverse != NULL)
    {
        if (traverse->data == key)
        {
            return traverse;
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
}
/**
 * @brief deletes the node that needs to be deleted. when that node is found, it calls the function of DeleteNode. If a duplicate value needs to be deleted, its count is decremented
 * 
 * @param key the value of the node that needs to be deleted
 */
void BST::remove(int key)
{
    //node_to_delete stored the node that has the same value of key. This node is returned by the function search_delete
    node *node_to_delete = search_delete(key);
    //checks if this node contains duplicate values, if it does then a value of count is decremented
    if (node_to_delete->count > 1)
    {
        cout<<"\nDeleting a duplicate value...";
        cout<<"\nnode count before deleting: "<<node_to_delete->count<<endl;

        node_to_delete->count--;
        cout<<"node count after deleting: "<<node_to_delete->count<<endl;
        return; // might have to delete this statement;
    }
    else{
        deleteNode(key, root);
        cout<<"\nnode deleted\n";
    }
}
/**
 * @brief runs recursively and deletes the subtree and reassemples the tree
 * 
 * @param num value that needs to be deleted
 * @param nodeptr reference to the pointer of the node. initially it is root node
 */
void BST::deleteNode(int num, node *&nodeptr){
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
/**
 * @brief deletes a node. further comments are added within this function
 * 
 * @param nodeptr reference to the pointed of a node to be deleted
 */
void BST::makeDeletion(node *&nodeptr){
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

int main()
{
    BST tree;
    int choice;
    while(1){
        cout<<"\nEnter your choice: \n1. Add a number to the tree\n2. delete a number from the tree\n3. search a number in the tree\n4. display in order traversal\n5. display pre order traversal\n6. display post order traversal\n7. Exit\n---> ";
        cin>>choice;
        while(choice < 1 || choice > 7){
            cout<<"\nWRONG CHOICE ENTERED. ENTER YOUR CHOICE AGAIN:\n---> ";
            cin>>choice;
        }
        if(choice == 1){
            int val;
            cout<<"\nEnter the value that you want to add: ";
            cin>>val;
            tree.InsertNode(val);
        }
        else if(choice == 2){
            int val;
            cout<<"\nEnter the value that you want to delete: ";
            cin>>val;
            tree.remove(val);
        }
        else if(choice == 3){
            int val;
            cout<<"\nEnter the value that you want to search: ";
            cin>>val;
            if(tree.searchNode(val)){
                cout<<"\nValue found in the tree\n";
            }
            else{
                cout<<"\nValue not found in the tree\n";
            }
        }
        else if(choice == 4){
            cout<<"\nDisplaying in order tree: \n";
            tree.ShowInOrder();
        }

        else if(choice == 5){
            cout<<"\nDisplaying pre order tree: \n";
            tree.ShowPreOrder();
        }
        else if(choice == 6){
            cout<<"\nDisplaying post order tree: \n";
            tree.ShowPostOrder();
        }

        else if(choice == 7){
            cout<<"\n...Exiting...\n";
            break;
        }
    }
    
    return 0;
}