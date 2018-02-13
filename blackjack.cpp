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
HandResults playBlackjack(Deck &deck, std::vector<Player> &players)
{
    Dealer dealer;


    // Do cuts, first player always cuts.
    players.back().doCut(deck);
    dealer.doCut(deck);
    
    // Burn first card in the deck
    deck.dealCard();

    do
    {    
        // Place bets
        bool no_one_playing = true;
        for (auto &player: players)
        {
            player.placeBets(MIN_BET);
            if (player.isPlaying())
                no_one_playing = false;
        }
        if (no_one_playing)
        {
            std::cout << "No one playing. Quitting shoe.";
            break;
        }

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
        if (dealer.getUpCard().getCardValue() == 11 && 
            dealer.getTotal() == 21)
        {
            std::cout << "Dealer peaks.. it's blackjack!\n";
            for (auto &player: players)
            {
                for (auto &hand: player.getHands())
                {
                std::cout << "Your Hand: " << hand;
                    if (hand.hasBlackjack())
                    {
                        std::cout << "Push from a blackjack!";
                        player.addMoney(hand.getBet());
                    }
                std::cout << "\n";
                }
            }
            for (auto &player: players)
                player.clearHands();
            dealer.clearHands();
            players.back().printHand();
            continue;
        } else
        if (dealer.getUpCard().getCardValue() == 11 && dealer.getTotal() != 21)
            std::cout << "Dealer peaks.. no blackjack!\n";
    
        bool all_busted = true;
        for (auto &player: players)
        {
            for (auto &player: players)
            {
                for (auto &hand: player.getHands())
                {
                    if (hand.hasBlackjack())
                    {
                        std::cout << "Oh hot damn, blackjack off the bat!\n";
                        hand.payOut();
                        player.addMoney(hand.getBet()*2.5);
                    }
                }
                
            }
            player.play(deck);
            if (player.getResult() != HandResults::Break)
                all_busted = false;
        }
    
        // Dealer does not play more cards if everyone busts.
        if (all_busted)
        {
            std::cout << "\nEveryone busted. Dealer had: ";
            dealer.printHand();
            std::cout << "\n";
            for (auto &player: players)
                player.clearHands();
            dealer.clearHands();
            continue;
        }

        dealer.play(deck);
        Hand dealer_hand = dealer.getHands()[0];
        
        int player_counter = 1;
        for (auto &player: players)
        {
            int hand_counter = 1;
            for(auto &hand: player.getHands()) 
            {
                std::cout << "Player " << player_counter <<
                    " Hand " << hand_counter;
                ++hand_counter;
                // Player getting blackjack off the bat already handled.
                if (hand.payedOut())
                {
                    std::cout << " won from previous blackjack!\n";
                    continue;
                }
                if (dealer_hand.isBusted())
                {
                    if (!hand.isBusted())
                    {
                        std::cout << " won from dealer bust!\n";
                        player.addMoney(hand.getBet() * 2);
                    } else
                    {
                        std::cout << " dealer busted, but hand was already busted\n";
                    }
                    continue;
                }
                if (hand.isBusted())
                {
                    std::cout << " busted :(\n";
                    continue;
                }

                if (hand.didHandWin(dealer_hand))
                {
                    std::cout << " won!\n";
                    player.addMoney(hand.getBet() * 2);
                }
                else if (hand.getTotal() == dealer_hand.getTotal())
                {
                    std::cout << " push!\n";
                    player.addMoney(hand.getBet());
                }
                else
                    std::cout << " lost :<\n";
            }
            ++player_counter;
        }
        std::cout << "****New Round!****\n";
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

    std::vector<Player> players;
    players.push_back(Player());
    do
    {
        //Actual shuffle
        deck.shuffleDeck();
        deck.printDeck();
        
        playBlackjack(deck, players); 
    } while (userInputPlayAgain());

    return 0;
}
