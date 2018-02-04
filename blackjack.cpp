#include <iostream>
#include <ctime> // for system time
#include <cstdlib> // for srand() and rand()
#include <string>
#include <vector>
#include "blackjack.h" // for HandResults
#include "deck.h" // for Deck class
#include "card.h" // for Card class
#include "player.h" // for Player class

/*
 * Asks if the user wants to play again.
 * Params: None
 * Returns: true or false
*/
bool userInputPlayAgain()
{
    char input;
    do
    {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> input;
    } while (input != 'y' && input != 'n');
    if (input == 'y')
        return true;
    return false;
}

/*
 * Plays blackjack.
 * Parms: deck reference - the deck to play with
 * Returns: HandResults - enum of win/lose/break/push/unknown
*/
HandResults playBlackjack(Deck &deck)
{
    Dealer dealer;
    std::vector<Player> players;
    players.push_back(Player());


    // Do cuts
    players.back().doCut(deck);
    deck.dealerCut();
    
    // Burn first card in the deck
    deck.dealCard();

    do
    {    

        // Deal
        for (auto &player: players)
            player.deal(deck);
        dealer.deal(deck);
        for (auto &player: players)
            player.deal(deck);
        dealer.deal(deck);
        
        // Play
        std::cout << "Dealers' up card is ";
        dealer.getUpCard().printCard();
        std::cout << "\n";
        
        // Dealer peaks
        if (dealer.getUpCard().getCardValue() == 11 && dealer.getTotal() == 21)
        {
            std::cout << "Dealer peaks.. it's blackjack!";
            std::cout << "Your Hand: ";
            players.back().printHand();
            if (players.back().getTotal() == 21)
                return HandResults::Push;
            return HandResults::Lose;
        } else
        if (dealer.getUpCard().getCardValue() == 11 && dealer.getTotal() != 21)
            std::cout << "Dealer peaks.. no blackjack!";
    
        bool all_busted = true;
        for (auto &player: players)
        {
            player.play(deck);
            if (player.getResult() != HandResults::Break)
                all_busted = false;
        }
    
        // Dealer does not play more cards if everyone busts.
        if (all_busted)
            return HandResults::Lose;
        HandResults dealer_result;
        dealer_result = dealer.play(deck);
    
        if (players.back().getResult() == HandResults::Break)
            return HandResults::Lose;
        if (dealer_result == HandResults::Break)
            return HandResults::Win;
    
        if (players.back().getTotal() == dealer.getTotal())
            return HandResults::Push;
        else if (players.back().getTotal() > dealer.getTotal())
            return HandResults::Win;

        // Clean up the hands.
        return HandResults::Lose;
        for (auto &player: players)
            player.clearHands();
        dealer.clearHands();

    } while (deck.moreDrawableCards());
}

/*
 * Main thread. initializes the deck.
 * Params: None
 * Returns: 0
*/
int main()
{
    srand(0);
    rand();
    const Card cardQueenHearts(Card::RANK_QUEEN, Card::SUIT_HEART);
    cardQueenHearts.printCard();
    std::cout << " has the value " << cardQueenHearts.getCardValue() << '\n';

    Deck deck;
    deck.printDeck();
    //Initial "shuffle" for deck wash
    deck.shuffleDeck();
    deck.printDeck();

    do
    {
        //Actual shuffle
        deck.shuffleDeck();
        deck.printDeck();
        
        HandResults result = playBlackjack(deck); 
        if (result==HandResults::Win)
            std::cout << "Congrats, You won!\n";
        else if (result == HandResults::Push)
            std::cout << "Push :\\n";
        else
            std::cout << "You lost.\n";
        
    } while (userInputPlayAgain());

    return 0;
}
