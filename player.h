#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "deck.h"
#include "blackjack.h" // for HandResults

class Player
{
private:
    std::array<Card, 12> m_hand; // min hand is 4 Aces, 4 2's, 4 3's;
    int m_total = 0;
    bool m_is_dealer = false;
    int m_num_dealers{0};

    char getUserInput();

public:
    Player(bool is_dealer = false);

    void deal(Deck &deck);

    int getTotal();

    HandResults play(Deck &deck);
};

#endif
