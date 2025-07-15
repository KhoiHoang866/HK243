#include<iostream>
using namespace std;


void heapify(int* arr, int size, int pos){
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    int maxPos = pos;
    if(left < size && arr[maxPos] < arr[left]){
        maxPos = left;
    }
    if(right < size && arr[maxPos] < arr[right]){
        maxPos = right;
    }
    if(maxPos != pos){
        swap(arr[pos],arr[maxPos]);
        heapify(arr,size,maxPos);
    }
}
void heapSort(int* arr, int size, bool descending = false){
    //built heap (move all greater element to upper level)
    for(int i = size/2 - 1; i >= 0; i--)
        heapify(arr,size,i);
    for(int i = size - 1; i > 0; i--){
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
    }
    if(descending)
        for(int i = 0; i < size/2; i++)
            swap(arr[i],arr[size-1-i]);
}

int main(){
    int size = 6;
    int arr[size] = {2,1,4,6,5,3};
    heapSort(arr,size,1);
    for(int i = 0; i < size; i++)
        cout<<arr[i]<<" ";
}