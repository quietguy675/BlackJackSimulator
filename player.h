#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "blackjack.h"

class Player
{
private:
    char getUserInput(Hand &hand);
    int getBetAmount(int min_bet, int max_bet);
protected:
    std::vector<Hand> m_hands;
    int getPlayerCut(int num_cards);
    int m_num_hands = 1;
    bool m_is_playing = true;
    int m_money = 500;
public:
    Player(int num_hands = 1, int money = 500);

    void deal(Deck &deck);

    int getTotal(int index = 0);

    HandResults play(Deck &deck);
    void doSplit(Hand &hand, Deck &deck);
    HandResults getResult(int index = 0);
    void doCut(Deck &deck);
    void printHand();
    void printHand(int index);
    void clearHands();
    int getNumHands();
    std::vector<Hand>& getHands();
    bool isPlaying();
    void placeBets(int min_bet = 5);
    void addMoney(int money = MIN_BET);
};

class Dealer : public Player
{
public:
    Dealer();

    const Card& getUpCard();
    HandResults play(Deck &deck);
    void doCut(Deck &deck);
};

#endif
