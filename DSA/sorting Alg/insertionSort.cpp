#include<iostream>
using namespace std;

void insert(int* arr, int pos, bool descending){
    int i = pos - 1;
    int val = arr[pos];
    while(0<=i && (!descending && val < arr[i] || descending && val > arr[i])){
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = val;
}

void insertionSort(int* arr, int size, bool descending = false){
    for(int i = 1; i < size; i++){
        insert(arr, i, descending);
    }
}



// int main(){
//     int size = 6;
//     int arr[size] = {2,4,1,6,5,3};
//     insertionSort(arr,size,0);
//     for(int i = 0; i < size; i++)
//         cout<<arr[i]<<" ";
// }