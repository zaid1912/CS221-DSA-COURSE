#include <iostream>
using namespace std;
// constant integer variable to store the maximum number of characters in English Language
const int total_char = 26;

class tries
{
private:
    struct node
    {
        bool EndOfWord;
        node *children[total_char];
        char data;
    };
    node *root;
    node *getNode()
    {
        node *newnode = new node;
        newnode->EndOfWord = false;
        for (int i = 0; i < total_char; i++)
        {
            newnode->children[i] = NULL;
        }
        return newnode;
    }
    /**
     * @brief this traverses through the trie and inserts new character node at appropriate position
     *
     * @param root pointer to the root node where the traversing starts tolook where new node needs to be added
     * @param key the word that needs to be added to the trie
     */
    void insert(node *root, string key)
    {
        node *traverse = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a'; // stores the index of each characted in key. a = 0, b = 1 and so on
            if (!traverse->children[index])
            {
                traverse->children[index] = getNode();
            }
            traverse = traverse->children[index];
        }
        traverse->EndOfWord = true;
    }

    /**
     * @brief travreses through the trie and checks if a particular word is included in the trie data structure
     *
     * @param root initially, traversing starts from the root node
     * @param key the word that needs to be searched for in the trie
     * @return true if the word is found
     * @return false if the word is not found
     */
    bool search(node *root, string key)
    {
        node *traverse = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!traverse->children[index])
            {
                return false;
            }
            traverse = traverse->children[index];
        }
        return traverse->EndOfWord;
    }

public:
    /**
     * @brief Construct a new tries object
     * Constructor
     */
    tries()
    {
        root = getNode();
    }
    /**
     * @brief calls the private member function of insert with root and the word that needs to be inserted as the two parameters
     *
     * @param s the string/word that needs to be added to tries data struture
     */
    void insertword(string s)
    {
        insert(root, s);
    }
    /**
     * @brief calls the private member function of search with root and the word that needs to be searched for as the two parameters
     *
     * @param s the string/word that needs to be added to tries data struture
     * @return true if the word is found
     * @return false if the word is not found
     */
    bool searchword(string s)
    {
        return (search(root, s));
    }
};