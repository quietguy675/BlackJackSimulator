#include <iostream>
#include <ctime> // for system time
#include <cstdlib> // for srand() and rand()
#include <string>
#include "deck.h" // for Deck class
#include "card.h" // for Card class


char getUserInput()
{
    char temp;
    do
    {
        std::cout << " Hit or stand (h/s): ";
        std::cin >> temp;
    } while (temp != 's' && temp != 'h');
    return temp;
}

bool playBlackjack(Deck deck)
{
    int player_total = 0;
    int dealer_total = 0;

    // Dealer draws first
    dealer_total += deck.dealCard().getCardValue();
    std::cout << "Dealers' up card is " << dealer_total << "\n";
    player_total += deck.dealCard().getCardValue();
    player_total += deck.dealCard().getCardValue();

    char user_action;
    while (1)
    {
        std::cout << "Your total: " << player_total;
        user_action = getUserInput();
        if (user_action == 's')
            break;
        player_total += deck.dealCard().getCardValue();
        if (player_total > 21)
        {
            std::cout << player_total << "Busted!\n";
            return false;
        }
    }

    while (dealer_total < 17)
    {
        dealer_total += deck.dealCard().getCardValue();
        std::cout << "Dealer total: " << dealer_total << "\n";
        if (dealer_total > 21)
        {
            std::cout << "Dealer busted.\n";
            return true;
        }
    }

    if (player_total > dealer_total)
        return true;
    return false;
}

int main()
{
    srand(0);
    const Card cardQueenHearts(Card::RANK_QUEEN, Card::SUIT_HEART);
    cardQueenHearts.printCard();
    std::cout << " has the value " << cardQueenHearts.getCardValue() << '\n';

    Deck deck;
    deck.printDeck();
    deck.shuffleDeck();
    deck.printDeck();

    std::cout << "The first card has value: " << deck.dealCard().getCardValue() << "\n";
    std::cout << "The second card has value: " << deck.dealCard().getCardValue() << "\n"; 
    if (playBlackjack(deck))
        std::cout << "Congrats, You won!\n";
    else
        std::cout << "You lost.\n";
    return 0;
}
