#include<iostream>
using namespace std;

struct table{
    int key;
    string data;
    table(){}
    table(int k, string d){
        key = k;
        data = d;
    }
};

void insert(table t[], table x){
    t[x.key] = x;
}

table search(table t[], int key){
    return(t[key]);
}

void del(table t[], table x){
    t[x.key] = table(0, "");
}

int main(){
    table t[50];
    table x;
    
    for(int i = 0; i<50; i++){
        t[i] = table(0, "");
    }

}
