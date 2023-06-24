/*
hw1_palindrome.cpp
Purpose: This program is to check if a given string is a palindrome or not.
Name: Krystal Morales
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;

    cout << "Greetings! I am the palindrome decider!" << endl;

    while (true) 
    {
         cout << "Please enter a word: ";
         cin >> input;

        int length = input.length();
        int compareLength = min(length, 3);

        bool isPalindrome = true;
        bool isCloseEnough = true;

        for (int i = 0; i < length; i++) 
        {
            if (input[i] != input[length - i - 1]) 
            {
                isPalindrome = false;
                break;
            }
        }     


        for (int i = 0; i < compareLength; i++) 
        {
            if (input[i] != input[length -  i - 1]) 
            {
                isCloseEnough = false;
                break;
            }
        }

        if (isPalindrome) 
        {
            cout << "Your word is a palindrome! Fantastic!" << endl;
        }
        else if (isCloseEnough)
        {
            cout << "Not quite a palindrome, but close enough." << endl;
        }
        else 
        {
            cout << "Your word is NOT a palindrome. Thanks anyway!" << endl;
            break;
        }
    }

    return 0;
}
