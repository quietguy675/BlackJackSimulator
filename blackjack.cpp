#include <iostream>
#include <ctime> // for system time
#include <cstdlib> // for srand() and rand()
#include <string>
#include "blackjack.h" // for HandResults, DECK_SIZE, and CARDS_PER_DECK
#include "deck.h" // for Deck class
#include "card.h" // for Card class
#include "player.h" // for Player class

HandResults playBlackjack(Deck deck)
{
    Player dealer(true);
    Player player;    

    // Dealer draws first
    dealer.deal(deck);
    std::cout << "Dealers' up card is " << dealer.getTotal() << "\n";
    player.deal(deck);

    HandResults result;
    result = player.play(deck);
    if (result == HandResults::Break)
        return HandResults::Lose;

    result = dealer.play(deck);
    if (result == HandResults::Break)
        return HandResults::Win;

    if (player.getTotal() == dealer.getTotal())
        return HandResults::Push;
    else if (player.getTotal() > dealer.getTotal())
        return HandResults::Win;
    return HandResults::Lose;
}

int main()
{
    srand(0);
    rand();
    const Card cardQueenHearts(Card::RANK_QUEEN, Card::SUIT_HEART);
    cardQueenHearts.printCard();
    std::cout << " has the value " << cardQueenHearts.getCardValue() << '\n';

    Deck deck;
    deck.printDeck();
    deck.shuffleDeck();
    deck.printDeck();

    std::cout << "The first card has value: " << deck.dealCard().getCardValue() << "\n";
    std::cout << "The second card has value: " << deck.dealCard().getCardValue() << "\n";
    HandResults result = playBlackjack(deck); 
    if (result==HandResults::Win)
        std::cout << "Congrats, You won!\n";
    else if (result == HandResults::Push)
        std::cout << "Push :\\\n";
    else
        std::cout << "You lost.\n";
    return 0;
}
