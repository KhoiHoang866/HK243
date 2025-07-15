#include<iostream>
using namespace std;

void bubbleSort(int* arr, int size, bool descending = false){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(!descending && arr[j] > arr[j+1] || descending && arr[j] < arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}