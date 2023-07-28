#include <iostream>
#include <cmath>
using namespace std;

int main(){

    int arr [] = {22,28,32,39,56,57,80,82,86,88};
    int low = 0;
    int high = 9;
    int mid = 0;
    int toSearch = 0;
    cout << "Enter the value you want to search: ";
    cin >> toSearch ; 
    while (low <= high){
        mid = (low + high) / 2;

        if (toSearch == arr[mid] )
        {
            cout << "value found at position  " << mid+1;
            break;
        }
        else if (toSearch > arr[mid])
        {
           low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
       
    }
     if (low > high)
        {
            cout << "Value not found.....";
        }
}