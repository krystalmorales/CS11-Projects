/*
* top3.cpp
* Purpose: This file will output the top three numbers from the input file
* Submitted by: {Krystal Morales, kmoral02}
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "ERROR: Invalid number of arguments\n";
        exit(EXIT_FAILURE);
    }

    // Declare a variable to read in from the input file
    ifstream infile;
    string filename = argv[1];

    infile.open(filename.c_str());

    //Check for Error
    if(!infile.is_open()) {
        cerr << "ERROR: Could not open file" << filename << endl;
        cerr << "Please check that you specified the correct filename" << endl;
        exit(EXIT_FAILURE);
    }  //open the file

    int next_number;
    int size = 0;
    const int max_size = 3;
    int* arr_number = new int[max_size];

    while(infile >> next_number) {

        if(infile.eof()) {
            cerr << "ERROR: Reached end of file" << endl;
            exit(EXIT_FAILURE);
        }

        arr_number[size] = next_number;
        size++;

        if(size > max_size) {
        for(int i = 0; i < size - 1 ; i++) {
            for(int j = 0; j < size - 1; j++) {
                if (arr_number[j] < arr_number[j + 1]) {
                    int temp = arr_number[j];
                    arr_number[j] = arr_number[j+1];
                    arr_number[j+1] = temp;
                    }
                }
            }
            size = max_size;
        }
    }

    for(int i = 0; i < 3; i++) {      
        cout << arr_number[i] << endl;
    }

    infile.close();

    delete[] arr_number;

    return 0;
    
}    