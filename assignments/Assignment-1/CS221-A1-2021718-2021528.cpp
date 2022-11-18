#include<iostream>
using namespace std;

/**
 * @brief The class has been declared for the 4-Way Linked List
 * 
 */
class list {
private:
    /**
     * @brief A structure of the node has been created that will take in all of the data and store.
     * 
     */
    struct node {
        long phNo;
        string name;
        string address;
        string email;
        node* left = NULL;
        node* right = NULL;
        node* up = NULL;
        node* down = NULL;
    };
    node* headptr, * temphead, * head_above;
    int rows, columns;
    static int num_nodes, current_row;


public:

    /**
     * @brief The constructor is passing R and C which act as the Rows and Columns
     * of the 4-Way Linked List
     * 
     * @param r 
     * @param c 
     */
    list(int r, int c) {
        headptr = NULL;
        head_above = NULL;
        rows = r;
        columns = c;
    }
    /**
     * @brief This is the function to fetch all user details, this function is interlinked with the insert function that is meant
     * to add a new node
     * 
     * @param newnode will be passed to which then all the details will be added
     */
    void get_details(node* newnode) {
        cout << "\nEnter the phone number: ";
        cin >> newnode->phNo;
        cout<<"\nEnter the name: ";
        cin>>newnode->name;
        cout<<"\nEnter the address: ";
        cin>>newnode->address;
        cout<<"\nEnter the email: ";
        cin>>newnode->email;
    }
    /**
     * @brief This function acts as a safety check to see if the 4-Way Linked List is full or not.
     * 
     * @return true 
     * @return false 
     */
    bool full() {
        return(num_nodes == rows * columns);
    }
    /**
     * @brief As the function is void, we are taking the input through the function in-itself. An error check
     * has been added as well, in the case that the function is full.
     * the Bool function will be called to check.
     * 
     */
    void insert() {
        if (list::full()) {
            cout << "\nlist is full already. Can't add more items to the list\n";
            return;
        }
        else if (headptr == NULL) {
            node* temp = new node;
            get_details(temp);
            headptr = temp;
            temphead = headptr;
            num_nodes++;
            return;
        }
        else {
            node* temp = new node;
            node* traverse = temphead;
            while (traverse->right != NULL) {
                traverse = traverse->right;
            }
            get_details(temp);
            num_nodes++;
            if (current_row == 1) {
                traverse->right = temp;
                temp->left = traverse;
            }
            if (current_row > 1) {
                if (num_nodes % columns != 1) {
                    traverse->right = temp;
                    temp->left = traverse;
                    node* vertical_connect = temp->left->up->right;
                    temp->up = vertical_connect;
                    vertical_connect->down = temp;
                }
                else {
                    temphead->down = temp;
                    temp->up = temphead;
                    temphead = temp;
                    current_row++;
                }
            }

            // if (num_nodes % columns == 0&& current_row != rows) {
            //     node* newtemphead = new node;
            //     cout << "a" << endl;
            //     head_above = temphead;
            //     newtemphead->up = temphead;
            //     temphead->down = newtemphead;
            //     temphead = newtemphead;
            //     current_row++;
            // }
        }
    }

    /**
     * @brief The Search_Num function is designed to traverse the 4-Way Linked List
     * and find whatever node may have the value. 
     * In the chance of there not being a value, an error will be given to the user.
     * 
     * @param n is being utilized to pass the name from the User's Input
     */
    void search_name(string n) {
        node* rowhead = headptr;
        node* temp = rowhead;
        while (temp != NULL) {
            if (temp->name == n) {
                cout << "\nNumber found: " << temp->phNo << endl;
                return;
            }
            temp = temp->right;
            if (temp == NULL) {
                temp = rowhead->down;
                rowhead = temp;
            }
        }
        if (temp == NULL) {
            cout << "\nNo such phone number found\n";
        }

    }

    /**
     * @brief The Search_Mail function is designed to traverse the 4-Way Linked List
     * and find whatever node may have the value.
     * In the chance of there not being a value, an error will be given to the user.
     * 
     * @param m is being utilzied to pass the name from the User's input
     */
    void search_mail(string m) {
        node* rowhead = headptr;
        node* temp = rowhead;
        while (temp != NULL) {
            if (temp->email == m) {
                cout << "\nNumber found: " << temp->phNo << endl;
                return;
            }
            temp = temp->right;
            if (temp == NULL) {
                temp = rowhead->down;
                rowhead = temp;
            }
        }
        if (temp == NULL) {
            cout << "\nNo such phone number found\n";
        }

    }

    /**
     * @brief The Search_address function is designed to traverse the 4-Way Linked List
     * and find whatever node may have the value.
     * In the chance of there not being a value, an error will be given to the user.
     * 
     * @param add is being utilized to pass the Address from the User's Input
     */
    void search_address(string add) {
        node* rowhead = headptr;
        node* temp = rowhead;
        while (temp != NULL) {
            if (temp->address == add) {
                cout << "\nNumber found: " << temp->phNo << endl;
                return;
            }
            temp = temp->right;
            if (temp == NULL) {
                temp = rowhead->down;
                rowhead = temp;
            }
        }
        if (temp == NULL) {
            cout << "\nNo such phone number found\n";
        }

    }

    /**
     * @brief The Search_delete function traverses through the 4-Way Linked List and finds the 
     * specific node that is to be deleted.
     * 
     * @param key is essentially the number to be deleted, being taken from the User.
     * @return node* (is being returned to the delete_node function)
     */
    node* search_delete(long key) {
        node* rowhead = headptr;
        node* temp = rowhead;
        while (temp != NULL) {
            if (temp->phNo == key) {
                return temp;
            }
            temp = temp->right;
            if (temp == NULL) {
                temp = rowhead->down;
                rowhead = rowhead->down;
            }
        }
        return NULL;
    }

    /**
     * @brief The Delete_Node function goes to the Last Node and swaps the date with the Node that is to be deleted
     * The pointer values however are not being changed therefore, the order of the Linked List may not remain the same.
     * 
     * @param key 
     */
    void delete_node(long key) {
        node* temp = temphead;
        node* delete_node = search_delete(key);
        if(delete_node == NULL){
            cout << "\nNODE NOT FOUND!\n";
            return;
        }
        // if (num_nodes % columns == 1)
        // {
        //     temphead = temphead->up;
        //     temp = temphead;
        // }

        while(temp->right != NULL)
            temp = temp->right;
        
        swap(temp->name, delete_node->name);
        swap(temp->email, delete_node->email);
        swap(temp->address, delete_node->address);
        swap(temp->phNo, delete_node->phNo);
        delete_node = temp;
        temp->left->right = NULL;
        delete delete_node;
        num_nodes--;
    }


    /**
     * @brief The 4-Way Linked List will traverse the entire system and display the entire directory for the user to see.
     * 
     */
    void display() {
        cout << "\nDisplaying...\n";
        node* rowhead = headptr;
        node* temp = rowhead;
        while (temp != NULL) {
            cout << "Phone Number: " << temp->phNo << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Address: " << temp->address << endl;
            cout << "Email: " << temp->email << endl;
            // cout << "temp->right = " << temp->right << endl;
            temp = temp->right;
            if (temp == NULL) {
                temp = rowhead->down;
                rowhead = rowhead->down;
            }
        }
    }
};
int list::num_nodes = 0;
int list::current_row = 1;


int main() 
{
    /**
     * @brief The initial end of the code is being utilized to create a 
     * UI for the user to interact with
     * 
     */
    int r, c;
    int option;

    cout << "         Welcome to the Telephone Directory." << endl;

    cout << "To start, please specify the Row Size of the Directory: ";
    cin >> r;
    cout << endl;
    cout << "Please specify the Column Size of the Directory: ";
    cin >> c; 
    cout << endl;

    list l(r, c);

    system("CLS");

    /**
     * @brief The While Loop has been created to allow for the user to have the option to add multiple inputs
     * into the system.
     * 
     */
    while(1)
    {
        
        while(1)
        {
            cout << "Menu: " << endl;
            cout << "1. Add a Phone Number" << endl;
            cout << "2. Delete a Phone Number" << endl;
            cout << "3. Search Directory" << endl;
            cout << "4. Display Directory" << endl;

            cout << "Please select: ";
            cin >> option;
            cout << endl;

            if (option < 1 || option > 4)
            {
                cout << "Error: The number you have entered is beyond limits." << endl;
                continue;
            }
            else
            {
                break;
            }
        }

        switch (option)
        {
            case 1:
            {
                l.insert();
                break;
            }

            case 2:
            {
                long number_to_delete;
                cout << "Please enter the number to delete: ";
                cin >> number_to_delete;
                cout << endl;
                l.delete_node(number_to_delete);
                break;
            }

            case 3:
            {
                int choice;

                while (1)
                {
                    cout << "What would you like to search for?" << endl;
                    cout << "1. Name" << endl;
                    cout << "2. Mail" << endl;
                    cout << "3. Address" << endl;

                    cout << "Please select: ";
                    cin >> choice;

                    if (choice < 1 || choice > 3)
                    {
                        continue;
                    }
                    else
                    {
                        if (choice == 1)
                        {
                            string temp_name;
                            cout << "Please enter the name to search: ";
                            cin >> temp_name;
                            cout << endl;
                            l.search_name(temp_name);
                            break;

                        }
                        else if (choice == 2)
                        {
                            string temp_mail;
                            cout << "Please enter the Email to search: ";
                            cin >> temp_mail;
                            cout << endl;
                            l.search_mail(temp_mail); 
                            break;
                        }
                        else if (choice == 3)
                        {
                            string x_address;
                            cout << "Please enter the Address to search: ";
                            cin >> x_address;
                            cout << endl;
                            l.search_address(x_address);
                            break;
                        }

                    }
                }
            }

            case 4:
            {
                l.display();
                break;
            }

            std::cout << "\n\n\n";

        }
    }
}
