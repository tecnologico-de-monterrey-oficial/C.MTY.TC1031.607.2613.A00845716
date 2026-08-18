#ifndef List_h
#define List_h
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class List {
    private:
        vector<T>data;
        int size;
    public:
        List();
        void insert(T value);
        void removeLast();
        T getData(int pos);
        int getSize();
        T getMax();
        void print();
        void insertAt(int pos, T value);
        void removeAt(int pos);
};

template<typename T>
List<T>::List() {
    size = 0;
}

template<typename T>
void List<T>::insert(T value){
    data.push_back(value);
    size++;
}
template<typename T>
void List<T>::removeLast(){
    if(size == 0){
        cout << "NO HAY ELEMENTOS" << endl;
    } else {
        cout << data[size-1] << endl;
        data.pop_back();
        size--;
    }
}
template<typename T>
T List<T>::getData(int pos){
    return data[pos];
}
template<typename T>
int List<T>::getSize(){
    return size;
}
template<typename T>
T List<T>::getMax(){
    T max = data[0];
    for(int i = 1; i < size; i++){
        if(data[i] > max){
            max = data[i];
        }
    }
    return max;
}
template<typename T>
void List<T>::print(){
    for(int i = 0; i < size; i++){
        cout << "[" << i << "] - " << data[i] << endl;
    }
}
template<typename T>
void List<T>::insertAt(int pos, T value){
    if(pos < 0 || pos > size){
        cout << "POSICIÓN INVÁLIDA" << endl;
    } else {
        data.push_back(value);
        for(int i = size; i > pos; i--){
            data[i] = data[i-1];
        }
        data[pos] = value;
        size++;
    }
}

template<typename T>
void List<T>::removeAt(int pos){
    if(size == 0){
        cout << "NO HAY ELEMENTOS" << endl;
    } else if(pos < 0 || pos >= size){
        cout << "POSICIÓN INVÁLIDA" << endl;
    } else {
        cout << data[pos] << endl;
        for(int i = pos; i < size-1; i++){
            data[i] = data[i+1];
        }
        data.pop_back();
        size--;
    }
}
#endif /* List_h */