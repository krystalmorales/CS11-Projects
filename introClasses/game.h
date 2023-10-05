#ifndef _GAME_H
#define _GAME_H

#include "deck.h"
#include "discard_pile.h"
#include "hand.h"
#include <string>

using namespace std;


class Game {
public:
  const static int NUM_PLAYERS = 2;

  Game(string deckFileName);
  ~Game();

  void play();

private:
  void takeTurn(int playerNum);
  void takeDiscard(int playerNum);
  void drawFromDeck(int playerNum);
  bool didPlayerWin(int playerNum);

  Deck* deck;
  DiscardPile* discard;
  Hand* hands[NUM_PLAYERS];
};

#endif // _GAME_H
