#include <iostream>
#include <vector> // for std::vector
#include <cassert> // for assert
#include "player.h" 
#include "hand.h" // for Hand class
#include "card.h" // for Card class
#include "deck.h" // for Deck class
#include "blackjack.h" // for HandResults

/*
 * Constructor. Adds a blank hand to the player.
*/
Player::Player(int num_hands): m_num_hands(num_hands)
{
    assert(num_hands > 0 && num_hands < 2 && "Player can only play 1 or two hands");
    for (int i = 0; i < num_hands; ++i)
        m_hands.push_back(Hand());
}

/*
 * Gets the user input depending on what they can do with their hand.
 * Parameters: None
 * Returns: Char of s/p/d/h
*/
char Player::getUserInput(Hand &hand)
{
    char temp;
    if (hand.canDouble() && hand.canSplit())
    {
        do
        {
            std::cout << "Hit, stand, double or split? (h/s/d/s)?";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd' && temp != 'p');
        return temp;
    } else if (hand.canDouble())
    {
        do
        {
            std::cout << "Hit, stand, or double? (h/s/d)?";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd');
        return temp;
    } else if (hand.canSplit())
    {
        do
        {
            std::cout << "Hit, stand, or split? (h/s/p)?";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'p');
        return temp;
    }
    do
    {
        std::cout << "Hit or stand (h/s)? ";
        std::cin >> temp;
    } while (temp != 's' && temp != 'h');
    return temp;
}

/*
 * Splits the hand into two hands (if they can) auto-draws 1 card for each hand.
 * Can't do this in Hand because would allocate on the heap and have to delete them.
 * Might change to dynamically allocated hands to m_hands and have a destructor delete them.
 * Params: hands_index - index of the m_hands hand to split
 *         deck - the current blackjack deck
 * Returns: None
*/
void Player::doSplit(Hand &hand, Deck &deck)
{
    if (hand.getNumAces() == 2)
        m_hands.push_back(Hand(hand.replaceCard(deck.dealCard()),
            deck.dealCard(),
            true));
    m_hands.push_back(Hand(hand.replaceCard(deck.dealCard()),
        deck.dealCard()));
}

/*
 * Adds a card to the hand.
 * Params: deck - the current blackjack deck
 * Returns: None
*/
void Player::deal(Deck &deck)
{
    for (int i = 0, n = m_hands.size(); i < n; ++i)
        m_hands[i].addCard(deck.dealCard());
}

/*
 * Gets the total for a specific hand
 * Params: index - index of m_hands
 * Returns: int of hand numerical total.
*/
int Player::getTotal(int index)
{
    assert(index >= 0 && index < m_hands.size());
    return m_hands[index].getTotal();
}

/*
 * Main routine for user-interactive playing of blackjack
 * Params: deck - the current blackjack deck
 * Returns: HandResults - break or unknown
*/
HandResults Player::play(Deck &deck)
{
    char user_action;
    printHand();
    std::cout << "Your total: " << m_hands.back().getTotal() << " ";
    for (int i = 0; i < m_hands.size(); ++i)
    {
        while(1)
        {
            user_action = getUserInput(m_hands[i]);
            if (user_action == 's')
                break;
            else if (user_action == 'p')
                doSplit(m_hands[i], deck);
                if (m_hands[i].hasSplitAces())
                    break;
            else if (user_action == 'd' or user_action == 'h')
                m_hands.back().addCard(deck.dealCard());

            int total = m_hands[i].getTotal();
            std::cout << "Your total: " << total << " ";
            if (total > 21)
            {
                std::cout << "\n";
                break;
            }
        }
    }
    return HandResults::Unknown;
}

/*
 * Gets if the hands is busted or not
 * Params: index - hand index for the player
 * Returns: HandResults - Break or Unknown
*/
HandResults Player::getResult(int index)
{
    assert(index >= 0 && index < m_hands.size());
    if (m_hands[index].getTotal() > 21)
        return HandResults::Break;
    return HandResults::Unknown;
}

/*
 * Cuts the deck as a player
 * Params: deck reference - the current blackjack deck
 * Returns: None
*/
void Player::doCut(Deck &deck)
{
    int total_cards = deck.getNumCards();
    deck.playerCut(getPlayerCut(total_cards));
}

/*
 * Gets the user input for where they want to cut the deck
 * Params: num_cards - the number of cards in the deck
 * Returns: int - the index of where to cut
*/
int Player::getPlayerCut(int num_cards)
{
    int player_cut = 0;
    do
    {
        std::cout << "Where would you like to cut the cards (0 - " <<
            num_cards - 1 << ")?";
        std::cin >> player_cut;
    } while (player_cut <= 0 && player_cut >= num_cards);
    return player_cut;
}

/*
 * prints the players' hand(s)
 * Params: None
 * Returns: None
*/
void Player::printHand()
{
    if (m_hands.size() == 1)
        std::cout << m_hands.back();
    else
    {
        for (int i = 0, n = m_hands.size(); i < n; ++i)
        {
            std::cout << "Hand " << i << ": " << m_hands[i] << "\n";
        }
    }
}

/*
 * Prints a specific hand in m_hands
 * Params: index - the index of the hand in m_hands
 * Returns: None
*/
void Player::printHand(int index)
{
    assert(index > 0 && index < m_hands.size());
    std::cout << m_hands[index];
}

/*
 * Clears the hand(s) of the player.
 * Params: None
 * Returns: Void
*/
void Player::clearHands()
{
    m_hands.clear();
    for(int i = 0; i < m_num_hands; ++i)
        m_hands.push_back(Hand());
}

int Player::getNumHands()
{
    return m_hands.size();
}

/*
 * Constructor, depends on the Player() constructor in initialize the hand.
*/
Dealer::Dealer() : Player()
{
}

/*
 * Gets the current card facing up. only 1 hand.
 * Params: None
 * Returns: const Card reference
*/
const Card& Dealer::getUpCard()
{
    return m_hands.back().getUpCard();
}

/*
 * Plays the game as a dealer
 * Params: deck reference - the current blackjack deck
 * Returns: HandResult - Break or Unknown
*/
HandResults Dealer::play(Deck &deck)
{
    std::cout << "Dealer total: " << m_hands.back().getTotal() << "\n";
    while(m_hands.back().getTotal() < 17)
    {
        m_hands.back().addCard(deck.dealCard());
        int total = m_hands.back().getTotal();
        std::cout << "Dealer total: " << total << "\n";
        if (total > 21)
            return HandResults::Break;
    }

    return HandResults::Unknown;
}
