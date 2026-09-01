// Diego Contreras

#include <iostream>
using namespace std;



template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}




int main() {
    vector<int> nums = {5, 2, 4, 6, 1, 3};
    insertionSort(nums);
    for (int x : nums) cout << x << " ";
}



