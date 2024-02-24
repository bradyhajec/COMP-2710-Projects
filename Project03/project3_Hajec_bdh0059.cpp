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

int main( ) {

    cout << "*** Welcome to Brady's sorting program ***\n";

    string filename;

    cout << "Enter the first input file name:";
    cin >> filename;

    //for reading files 1 and 2
    ifstream inStream1, inStream2;
    int data;

    // Pass the file name as an array of chars to open()
    // inStream.open(filename);
    inStream1.open((char*)filename.c_str());  //opens the string using the char pointer and the string name of file.... c_str converts to C-Style string (array of characters)

    if (inStream1.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
    }

    inStream1 >> data; //this moves the data in inSteam when file was opened into data
    
    while (!inStream1.eof()) {  //eof used to indicate when the end of the file is reached 
        cout << data << endl;
        inStream1 >> data;
    }
    inStream1.close();

    return 0;

}

//this method outputs the contents of the file by iteration through the array and returning the number of elements
//inStream paramater points to file that is being read from
int readfile(int inputArray[], ifstream& inStream)  {

    int index;
    inStream >> inputArray[index];

    while (! inStream.eof()) {
        cout << inputArray[index] << endl;
        index++;
        inStream >> inputArray[index];
    }

    return index;
}
