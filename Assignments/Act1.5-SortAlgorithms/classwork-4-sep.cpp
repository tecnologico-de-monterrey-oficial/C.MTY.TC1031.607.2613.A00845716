#include <iostream>
using namespace std;

template <typename>
void mergeSort(vector<T>)


template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    vector<T> leftList;
    for (int i=left; i<=mid; i++ ) {
        rightList.push_back(list[j]);
    }
    //combinamos las dos listas
    //creamos variables index con indice actualizado
    int index = left;
    //inicializamos el indice de lado izquierdo
    int i = 0;
    // inicializamos el indice de lado derech
    int j = 0;
    //iteramos mientras no se acaben las listas
    while (i<leftList.size() && j<rightList.size()){
        if (listLeft[i] < listRight [j]){
            i++;
        }
        else {
            listt[index] = listRight[j];
            j++;
        }
    }
    
}