#ifndef BLACKJACK_H
#define BLACKJACK_H

enum class HandResults
{
    Unknown,
    Break,
    Push,
    Win,
    Lose
};

const int NUM_DECKS = 1;
const int CARDS_PER_DECK = 52;
#endif
