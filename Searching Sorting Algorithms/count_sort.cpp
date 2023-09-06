#include <iostream>
using namespace std;

void countSort(int arr[], int n){

    //max element
    int k = arr[0];
    // how many elemnts in count array
    for (int i = 0; i < n; i++)
    {
        k = max(k, arr[i]);
    }

    //count array
    int count[10] = {0};
    //storing count of every element form our original array 
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }
    
    //traversing count array and add previous count value to next one
    for (int i = 1; i <= k; i++)
    {
        count[i] += count[i - 1];
    }
    
    int output[n];
    //sorted array values
    // traversing from the last element
    for (int i = n - 1; i >= 0; i--)
    {
        output[--count[arr[i]]] = arr[i];
    }
    
    //Updating unsorted array with sorted values
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

}

int main(){

    int arr[] = {1,3,2,3,4,1,6,4,3};
    countSort(arr, 9);

    for (int i = 0; i < 9; i++)
    {
        cout << arr[i] << " ";
    }
     
}