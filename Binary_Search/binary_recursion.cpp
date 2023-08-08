#include <iostream>
using namespace std;

int RBinSearch( int array[],int low,int high,int num){
     
     if (low <= high) 
     {
        int midp = (low + high) / 2;
        if (num == array[midp] )
        {
            return midp;
        }
        if (num > array[midp])
        {
            return RBinSearch(array,midp + 1, high, num);
        }
        if (num < array[midp])
        {
            return RBinSearch(array ,low, midp - 1 ,  num);
        }
     }
     
     return -1;
     

}

int main(){
    int arr [] = {22,28,32,39,56,57,80,82,86,88};
    int low = 0;
    int high = 9;
    int toSearch = 0;
    cout << "Enter the value you want to search: ";
    cin >> toSearch;
    int val = RBinSearch(arr,low, high, toSearch);
    if (val == -1)
    {
        cout << "value not found!";
    }
    else{
        cout << "value found at position " << val + 1 ;
    }
    
}
   
       