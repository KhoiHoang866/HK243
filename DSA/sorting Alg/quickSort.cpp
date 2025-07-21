#include<iostream>
using namespace std;

int partition(int* arr, int begin, int end){
    int index = begin - 1;
    for(int i = begin; i < end; i++){
        if(arr[i] <= arr[end]){
            swap(arr[i],arr[++index]);
        }
    }
    swap(arr[end],arr[++index]);
    return index;
}

void quickSort(int* arr, int begin, int end){
    if(begin < end){
        int mark = partition(arr,begin,end);
        quickSort(arr,begin,mark-1);
        quickSort(arr,mark + 1,end);
    }
}

int main(){
    int size = 100;
    int arr[100] = {
        42, 17, 89, 3, 76, 25, 61, 42, 8, 90,
        33, 58, 77, 10, 65, 49, 22, 70, 91, 36,
        13, 28, 47, 95, 5, 61, 71, 84, 30, 56,
        39, 2, 19, 44, 73, 11, 29, 80, 24, 33,
        98, 7, 14, 62, 100, 68, 81, 21, 93, 60,
        4, 35, 43, 92, 26, 17, 12, 46, 85, 38,
        75, 31, 59, 53, 23, 37, 15, 50, 69, 96,
        63, 48, 32, 6, 40, 87, 16, 74, 1, 45,
        9, 83, 97, 99, 27, 66, 18, 20, 34, 41,
        55, 78, 94, 72, 64, 86, 67, 57, 79, 88
    };
    quickSort(arr,0,size-1);

    for(int i = 0; i < size; i++)
        cout<<arr[i]<<" ";
}