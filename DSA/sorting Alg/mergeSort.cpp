#include<iostream>
using namespace std;

void merge(int* arr, int size, int* left, int* right){
    int l_idx = 0, r_idx = 0;
    int leftSize = size/2;
    int rightSize = size - leftSize;
    while(l_idx < leftSize && r_idx < rightSize){
        if(left[l_idx] <= right[r_idx]){
            int i = l_idx + r_idx;
            arr[i] = left[l_idx++];
        }
        else{
            int i = l_idx + r_idx;
            arr[i] = right[r_idx++];
        }
    }
    while(l_idx < leftSize){
        int i = l_idx + r_idx;
        arr[i] = left[l_idx++];
    }
    while(r_idx < rightSize){
        int i = l_idx + r_idx;
        arr[i] = right[r_idx++];
    }
}

void mergeSort(int* arr, int size, bool descending = false){
    if(size == 1) return;
    int leftSize = size/2;
    int rightSize = size - leftSize;
    int* left = new int[leftSize];
    int* right = new int[rightSize];
    for(int i = 0; i < leftSize; i++){
        left[i] = arr[i];
    }
    for(int i = 0; i < rightSize; i++){
        right[i] = arr[i + leftSize];
    }
    mergeSort(left, leftSize, descending);
    mergeSort(right, rightSize, descending);
    merge(arr, size, left, right);
    delete[] left;
    delete[] right;

}

void merge2(int* arr, int begin, int end){
    int temp[end - begin + 1];
    int mid = (begin + end)/2;
    int l_idx = begin, r_idx = mid + 1;
    int i = 0;
    while(l_idx <= mid && r_idx <= end){
        if(arr[l_idx] <= arr[r_idx]){
            temp[i++] = arr[l_idx++];
        }
        else{
            temp[i++] = arr[r_idx++];
        }
    }
    while(l_idx <= mid){
        temp[i++] = arr[l_idx++];
    }
    while(r_idx <= end){
        temp[i++] = arr[r_idx++];
    }
    for(int i = begin; i <= end; i++){
        arr[i] = temp[i - begin];
    }
}

void mergeSort2(int* arr, int begin, int end){
    if(begin >= end) return;
    int mid = (begin + end) / 2;
    mergeSort2(arr, begin, mid);
    mergeSort2(arr, mid + 1, end);
    merge2(arr,begin,end);
}

int main(){
    int size = 100;
    int arr[size] = {
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
    mergeSort2(arr,0,size-1);
    for(int i = 0; i < size; i++)
        cout<<arr[i]<<" ";
}