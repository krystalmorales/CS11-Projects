#include "discard_pile.h"
#include <iostream>

using namespace std;


DiscardPile::DiscardPile(Card* seedCard) {
  topDiscard = seedCard;
}


DiscardPile::~DiscardPile() {
  if (topDiscard != NULL) {
    delete topDiscard;
  }
}


void DiscardPile::discard(Card* discard) {
  if (topDiscard != NULL) {
    delete topDiscard;
  }
  topDiscard = discard;
}


Card* DiscardPile::takeDiscard() {
  Card* drawCard = topDiscard;
  topDiscard = NULL;
  return drawCard;
}


void DiscardPile::print() {
  if (topDiscard == NULL) {
    cout << "(NULL)" << endl;
  } else {
    cout << topDiscard->toString();
  }
}
