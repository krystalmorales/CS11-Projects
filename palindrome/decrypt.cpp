/*
hw1_decrypt.cpp
Purpose: This program decrypts words entered by user, given a shift amount entered by user.
Krystal Morales
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string decryptWord;
    int shiftAmount;

    cout<< "Enter the word that you would like to decrypt (in lowercase characters)" << endl;
    cout << "Word to decrypt: ";
    cin >> decryptWord;

    cout << "Enter the shift amount: ";
    cin >> shiftAmount;

    int lengthofWord = decryptWord.length();
    int nextLetterPosition = 0;

cout << "Decrypted word: ";

while ( nextLetterPosition < lengthofWord) 
{
    char newLetter = decryptWord[nextLetterPosition];

    if (newLetter >= 'a' && newLetter <= 'z') 
    {
        newLetter -= shiftAmount;

        if (newLetter < 'a') {
            newLetter += 26;
        }
    
    cout << newLetter;

    nextLetterPosition++;
    }

}
cout << endl;

return 0;


}
