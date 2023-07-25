#include <iostream>
using namespace std;

int main(){

    int arr []={86,22,39,57,28,32,56,80,88} ;
    int toSearch = 56;

    for (int i = 0; i < 9 ; i++ ){
        if (toSearch == arr[i]){
            cout << "value found at index " << i;
            break;

        }
    }
}