#include "card.h"
#include <iostream>
#include <sstream>

using namespace std;


Card::Card(int cardNumber) {
  cardNum = cardNumber;
}


int Card::getNum() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }
  return cardNum;
}


string Card::toString() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }

  return getTopEdge() + '\n'
    + getBlankLine()  + '\n'
    + getNumberLine() + '\n'
    + getBlankLine()  + '\n'
    + getBottomEdge() + '\n';
}


string Card::getTopEdge() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }
  return "/----\\";
}


string Card::getBlankLine() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }
  return "|    |";
}


string Card::getNumberLine() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }

  ostringstream numberLine;
  numberLine << "| ";
  if (cardNum < 10) {
    numberLine << ' ';
  }
  numberLine << cardNum;
  numberLine << " |";
  return numberLine.str();
}


string Card::getBottomEdge() {
  if (cardNum < 0) {
    cerr << "ERROR: tried to read an uninitialized card" << endl;
    exit(EXIT_FAILURE);
  }
  return "\\----/";
}
