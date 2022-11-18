#include <iostream>
using namespace std;
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
    tries()
    {
        root = getNode();
    }

    void insertword(string s)
    {
        insert(root, s);
    }
    bool searchword(string s)
    {
        return (search(root, s));
    }
};

int main()
{
    string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their", "zaid"};
    tries t;
    for (int i = 0; i < 9; i++)
    {
        t.insertword(keys[i]);
    }
    std::cout << t.searchword("zaid");
}