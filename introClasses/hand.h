#ifndef _HAND_H
#define _HAND_H

#include "card.h"


class Hand {
public:
  const static int HAND_SIZE = 5;

  Hand(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5);
  ~Hand();

  bool  isWinningHand();
  Card* replaceCard(Card* newCard);

  void  print();

private:
  Card* cards[HAND_SIZE];
};

#endif // _HAND_H
