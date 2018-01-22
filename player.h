#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "blackjack.h" // for HandResults


class Player
{
private:
    char getUserInput();
protected:
    std::vector<Hand> m_hands;
    int getPlayerCut(int num_cards);
public:
    Player();

    void deal(Deck &deck);

    int getTotal();

    HandResults play(Deck &deck);
    void doSplit(int hands_index, Deck &deck);
    HandResults getResult();
    void doCut(Deck &deck);
    void printHand();
    void printHand(int index);
};

class Dealer : public Player
{
public:
    Dealer();

    const Card& getUpCard();
    HandResults play(Deck &deck);
};

#endif
