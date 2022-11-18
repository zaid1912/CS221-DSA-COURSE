#include<iostream>
using namespace std;

template <class T>

class dynamic_array{
    private:

    T *arr;  //array pointer of template type
    int capacity = 0; // actual length of array

    public:
    dynamic_array(int cap){  //constructor
        arr = new T[cap];  //array is created by allocating the size equals argument(cap)
        capacity = cap;
    }
    int size(){ //returns the current size of the array (capacity)
        cout<<"\nSize of the array: ";
        return capacity;
    }

    bool is_empty(){  //check if the array contains any data or not
        if(capacity == 0){
            return true;
        }
        else{
            return false;
        }
        
    }

    T get(int index){  //returns the value of the array at the index passed as argument
        cout<<"\nshowing the stored element at index "<<index<<":\n";
        return arr[index];
        cout<<endl;
    }

    void set(int index, T elem){  //set/replace the value at specified index
        arr[index] = elem;
    }

    void add(T elem){ //adds the data at the end of array
        // int sizeAdd1 = capacity + 1;
        T *temp = new T[capacity + 1];  //temporary dynamil array of size = capacity + 1 is cleated (concept studied in CS112 (OOP))
        for(int i = 0; i < capacity; i++){
            temp[i] = arr[i];  //copy the initial values up to capacity from arr to temp array
        }
        delete []arr;  //delete the original array 
        temp[capacity] = elem;  //at the index equals capacity, new value is added to temp array
        arr = temp;  //we still have to call the array with its original name ie arr. so assignment is done
        capacity++;  //increment in capacity when a new value is added to the array
    }

    void show(){  //displays all the values stored in the array
        cout<<"\nshowing all elements in the array: \n";
        for(int i = 0; i<capacity; i++){
            cout<<arr[i]<<endl;
        }
    }
    void clear(){ //clears whole array
        for(int i = 0; i<capacity; i++){
            arr[i] = NULL;
        }
        capacity = 0;  //capacity is set to 0 whn the whole array is deleted
    }

    void remove_at(int index){  //removes an element at specified index
        for(int i = index; i < capacity - 1; i++){
            arr[i] = arr[i+1];

        }
        capacity--;  //decrement in capacity when an element is removed
        arr[capacity] = NULL;
    }


};
// int dynamic_array::capacity = 0;

int main(){
    dynamic_array<int> list(0);  //dynamic array of type int having a name 'list' is initialised.....object of class. having initial capacity/ size = 0
    list.add(2);
    list.add(3);
    list.add(5);
    list.add(8);
    list.add(3);
    list.add(0);
    list.show();

    // cout<<list.is_empty();
    // cout<<list.get(2)<<endl;
    // list.set(0, 5);
    cout<<list.size()<<endl;//6
    list.remove_at(2);
    cout<<list.size()<<endl;//5
    list.show();
    // list.clear();
    return 0;
}