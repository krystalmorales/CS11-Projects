/*
* tradecraft.cpp
* Purpose: This file will crack a ccaesar-encrypted text by determining the shift amount that was used during encryption
* Submitted by: {Krystal Morales, kmoral02}
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

// Function declarations
string read_encrypted_text(string filename);
int find_shift_amount(string filename);

/*
Name: main
Arguments: int argc, char *argv[]
    - int argc: represents the number of command-line arguments passed through the program
    - argv: is an array of strings where each element represents a command-line argument
Expectation about arguments: This function expects two arguments, if less are provided and error message is displayed
Description:  main checks for the number of command-line arguments and will read from the filename provided. it will also call the other two functions
Return value: 0
Exceptions about return value: it will return 0 if the program is successful
*/ 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "ERROR: Invalid number of arguments\n";
        exit(EXIT_FAILURE);
    }

    string encrypted_text = read_encrypted_text(argv[1]);
    find_shift_amount(encrypted_text);

    return 0;
}

/*
Name: read_encrypted_text
Arguments: string filename
     - string filename reads from the input filename
Expectation: this function will read the encrypted text and write into string_text
Description:  this function will retrieve the encrypted text
Return value: this will return the encrypted text
Exceptions about return value: by returning the encrypted text, 
    we can then find the frequency of letters in the text in a different function
*/
string read_encrypted_text(string filename) {

    // Declare a variable to read in from the file
    ifstream infile;

    //Open the file
    infile.open(filename.c_str());

    //Error check
    if(!infile.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    cerr << "Please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
    }

    if(infile.eof()) {
        cerr << "ERROR: Reached end of file before finishing \n";
        exit(EXIT_FAILURE);
        }

    string string_text; 
    string line;
    while(getline(infile, line)) {
        string_text += line;
    }
     
    //close file
    infile.close();

    return string_text;

}

/*
Name: find_shift_amount
Arguments: string filename
     - a string will pass through find_shift_amount in order to find the shift amount that was used to encrypt the text
Expectation: this function will read the encrypted text and calculate the shift amount 
Description:  this function will calculate the shift amount based on frequency of the letters in the filename
Return value: this will return an int that represents the shift amount
Exceptions about return value: by returning the shift amount we will be able to 
    figure out what the shift amount was at encryption time
*/
int find_shift_amount(string filename) {
    //array to hold all 26 letters
    int letter_count[26] = {0};
    //tally up the total letter count
    int total_letters = 0;
    int highest_frequency = 0;
    char most_frequent_letter;

//find most frequent letter
    //for every c in filename, enhanced for loop
    for (char c : filename) { 
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { 
            // Check if the character is a letter
            if (c >= 'A' && c <= 'Z') {
                // Convert uppercase letter to lowercase
                c += 'a' - 'A'; 
            }
            letter_count[c - 'a']++;  
            total_letters++;  

            if (letter_count[c - 'a'] > highest_frequency) {
                highest_frequency = letter_count[c - 'a'];
                most_frequent_letter = c;
            }
        }
    }

// Determine the shift amount based on the most frequent letter
    int shift_amount = 0;
    if(most_frequent_letter == 'c') {
        shift_amount = most_frequent_letter - 't';
         if (shift_amount < 0) {
            // Wrap around for negative values
            shift_amount += 26; 
        }
    }
    else {
        shift_amount = most_frequent_letter - 'e';
         if (shift_amount < 0) {
            // Wrap around for negative values
            shift_amount += 26; 
        } 
    }

    
    cout << "The shift amount is: " << shift_amount << endl;
    
    return shift_amount;
}