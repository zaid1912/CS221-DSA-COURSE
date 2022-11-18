#include<iostream>
using namespace std;

int main(){
    string name = "zaid";
    for(int i = 0; i<name.length(); i++){
        int index = name[i] - 'a';
        cout<<index<<endl;
    }
}