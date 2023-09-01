#include <iostream>
#include <fstream>
using namespace std;

int BribedQueue(int array[], int lenght){
    int count = 0;
    for (int i = 0; i < lenght - 1; i++ ){
        for (int j = 0; j < lenght - 1; j++){
            if (array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                count = count + 1;
            }
    }
    
        
    }
    return count;
}


int main(){
    int val;
    int len;
    // opening file
    ifstream in("E:/chrome downloads/q1/TestCase_04.txt");
    //lenght of array
    in >> len;
    int arr[len];

    for (int i = 0; i < len; i++){
        in >> arr[i];
        in.get();
    }
    val = BribedQueue(arr, len);
    cout << "Number of bribes: " << val;
}