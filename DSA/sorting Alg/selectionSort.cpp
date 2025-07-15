#include<iostream>
using namespace std;

void selectionSort(int* arr, int size,bool descending = false){
    for(int i = 0; i < size; i++){
        int minimal = arr[i];
        int minPos = i;
        for(int j = i + 1; j < size; j++){
            if(!descending && arr[j] < minimal || descending && arr[j] > minimal) {
                minimal = arr[j];
                minPos = j;
            }
        }
        swap(arr[i],arr[minPos]);
    }
}


int main(){
    int size = 6;
    int arr[size] = {2,1,4,6,5,3};
    selectionSort(arr,size,0);
    for(int i = 0; i < size; i++)
        cout<<arr[i]<<" ";
}