#include<iostream>
usiing namespace std;
#include<list>

template<class T>
struct node{
    T val;
    int priority;
    node *next;
};

class priority_queue{
    private:
    int len;
    node *front;

    public:

    priority_queue(){
        front = NULL;
        len = 0;
    }
    

};