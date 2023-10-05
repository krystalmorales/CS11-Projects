#ifndef _DISCARD_PILE_H
#define _DISCARD_PILE_H

#include "card.h"


class DiscardPile {
public:
  DiscardPile(Card* seedCard);
  ~DiscardPile();

  void  discard(Card* discard);
  Card* takeDiscard();

  void print();

private:
  Card* topDiscard;
};

#endif // _DISCARD_PILE_H
