//Author: Brady Hajec
//Name: project3_Hajec_bdh0059.cpp
//Auburn ID: bdh0059@auburn.edu
//To Compile: g++ project3_Hajec_bdh0059.cpp
//used https://cplusplus.com/reference/ios/ios/eof/ to learn about the methods used in sample code

#include <fstream>
#include <iostream>
using namespace std;

//Constant Declaration
const int MAX_SIZE = 100;


//Input: (1) Array storing data retrieved from the file (i.e., instream)
// (2) input file stream object
//Output: Size of array. Note: you need to use this parameter to control the array size.
int readfile(int inputArray[], ifstream& instream);
//final sorting of both arrays into outputArray
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]);
//method to write output array to file
void writefile(int outputArray[], int outputArray_size);
//the method will take one array and do a mergesort on it
void mergeSort(int inputArray[], int right, int left);
void merge(int array[], int left, int middle, int right);

int main( ) {

    cout << "*** Welcome to Brady's sorting program ***\n";

    string filename1; 
    string filename2;

    ifstream inStream1, inStream2;

    int iArray1[MAX_SIZE];
    int iArray1_size;
    int iArray2[MAX_SIZE];
    int iArray2_size;


    bool validFilename1 = false;
    while (!validFilename1) {
        cout << "Enter the first input file name:";
        cin >> filename1;
        inStream1.open(filename1);
        if (inStream1.fail()) {
            cout << "\nInput file opening failed. Please Enter an valid filename.\n" << endl;
            continue;
        }
        validFilename1 = true;
    }

    //sets array size 1 and also returns contents, then closes file after they are stored in the array
    iArray1_size = readfile(iArray1, inStream1);
    inStream1.close();


   bool validFilename2 = false;
    while (!validFilename2) {
        cout << "Enter the second input file name:";
        cin >> filename2;
        inStream2.open(filename2);
        if (inStream2.fail()) {
            cout << "\nInput file opening failed. Please Enter an valid filename.\n" << endl;
            continue;
        }
        validFilename2 = true;
    }

    iArray2_size = readfile(iArray2, inStream2);

    //create the output array, must have constant value 
    int outputArray[MAX_SIZE];

    sort(iArray1, iArray1_size, iArray2, iArray2_size, outputArray);

    inStream1.close();
    inStream2.close();
    return 0; 

}

//this method outputs the contents of the file by iteration through the array and returning the number of elements
//inStream paramater points to file that is being read from
//this returns the size of the input array
int readfile(int inputArray[], ifstream& inStream)  {

    int index = 0;
    inStream >> inputArray[index];  //store first value

    while (!inStream.eof()) {  //this stops when we reach the end of the file
        cout << inputArray[index] << endl; //input current value in array at this index
        index++;
        inStream >> inputArray[index];  //reads the line we are on and stores it the first index
    }


    return index;
}


//where breaking down and sorting is done 
void merge(int array[], int left, int middle, int right) {

    int lsize = middle - left + 1;
    int rsize = right - middle;

    int* tempLeft = new int[lsize];
    int* tempRight = new int[rsize];

    for (int i = 0; i < lsize; i++) {
        tempLeft[i] = array[left + i];
    }

    for (int j = 0; j < rsize; j++) {
        tempRight[j] = array[middle + 1 + j];
    }

    int indexOfLeftSubArray = 0;   //starting index for left subarray
    int indexOfRightSubArray = 0;     //starting index for right subarray
    int index = left;  //starting index for temporary array

    while (indexOfLeftSubArray < lsize && indexOfRightSubArray < rsize) {  //keep check of indexes fir left are less than the middle and middle are less than right

        if (tempLeft[indexOfLeftSubArray] <= tempRight[indexOfRightSubArray]) {
            array[index] = tempLeft[indexOfLeftSubArray]; //tempLeft is smaller than tempRight
            indexOfLeftSubArray++;
        }
        else {
            array[index] = tempRight[indexOfRightSubArray]; //tempRight is smaller than tempLeft
            indexOfRightSubArray++;
        }

        index++;

    }

    while (indexOfLeftSubArray < lsize) {   //copy the remaining values from the left subarray into the temporary array
     
        array[index] = tempLeft[indexOfLeftSubArray];
        index++;
        indexOfLeftSubArray++;

    }

    while (indexOfRightSubArray < rsize) {    //copy the remaining values from right subarray into the temporary array

        array[index] = tempRight[indexOfRightSubArray];
        index++;
        indexOfRightSubArray++;

    }
    

    //from GeeksforGeeks, C++ does not have automatic garbage collection
    delete[] tempLeft;
    delete[] tempRight;

}


void mergeSort(int array[], int left, int right) {

    //if there is not only 1 element left call again
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }

}


int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]) {

    int outputArray_size = inputArray1_size + inputArray2_size;

    //copy inputArray1 and inputArray2 into outputArray
    for (int i = 0; i < inputArray1_size; i++) {
        outputArray[i] = inputArray1[i];
    }
    for (int j = 0; j < inputArray2_size; j++) {
        outputArray[inputArray1_size + j] = inputArray2[j];
    }
    
    mergeSort(outputArray, 0, outputArray_size - 1);

    for (int k = 0; k < outputArray_size; k++) {

        cout << outputArray[k] << " ";

    }

    return outputArray_size;
}


void writefile(int outputArray[], int outputArray_size) {

}

