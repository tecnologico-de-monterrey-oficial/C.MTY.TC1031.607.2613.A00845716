// Diego Contreras
// A00845716

#include <iostream>  
#include <vector>      // vector
#include <algorithm>   // sort, binary_search, lower_bound, find
#include <string>      // string
#include <cmath>       



mid = right + left / 2; 
right = n -1;
left = 0;

while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    }
    else if (arr[mid] < target) {
        left = mid + 1;     }
    else {
        right = mid - 1; 
    }
}



cout << "Insertion point for target: " << left << endl; 
cout << "Insertion point for target: " << right << endl; 
cout << "Insertion point for target: " << mid << endl; 
