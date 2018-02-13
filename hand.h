#ifndef HAND_H
#define HAND_H
#include "card.h"
#include <vector>
#include <iostream>

class Hand
{
public:
    enum Moves
    {
        HIT,
        STAND,
        DOUBLE,
        SPLIT,
        MAX_MOVES
    };
private:
    std::vector<Card> m_hand;
    int m_num_aces;
    int m_total;
    bool m_has_split_aces = false;
    int m_bet = 0;
    bool m_payed_out = false;
public:
    Hand(Card const &carda, Card const &cardb, bool split_aces = false);
    Hand();
    int getTotal();
    const Card& getUpCard();
    
    friend std::ostream& operator<< (std::ostream &out, const Hand &hand);
    void addCard(Card const &card);

    bool canSplit();
    bool canDouble();
    const Card& replaceCard(Card const &card);
    
    void setSplitAces();
    bool hasSplitAces();
    bool hasBlackjack();
    int getNumAces();
    void placeBet(int bet);
    int getBet();
    bool didHandWin(Hand dealer_hand);
    bool isBusted();
    void payOut();
    bool payedOut();
};

 #endif
