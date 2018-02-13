#include <iostream>
#include <vector>
#include "hand.h"
#include "card.h"

/*
 * Constructor which is for when decks are split.
 * Params: const carda reference - a card from the previous hand
 *         const cardb reference - a card from the deck
*/
Hand::Hand(Card const &carda, Card const &cardb, bool split_aces): m_num_aces(0),
    m_total(0), m_has_split_aces(split_aces), m_payed_out(false)
{
    addCard(carda);
    addCard(cardb);
}

/*
 * Constructor for the fist hand of the player
*/
Hand::Hand(): m_num_aces(0), m_total(0), m_has_split_aces(false)
{
}

/*
 * gets the total value in the hand
 * Params: None
 * Returns: int - total value of the cards in the hand
*/
int Hand::getTotal()
{
    return m_total;
}

/*
 * Adds a card to the hand
 * Params: const card reference - a card from the deck
 * Returns: None
*/
void Hand::addCard(Card const &card)
{
    m_hand.push_back(card);
    if (m_hand.back().getCardValue() == 11)
        m_num_aces++;

    // Handle if you bust but have an unused ace.
    if (m_num_aces > 0 && (m_total + card.getCardValue()) > 21)
    {
        --m_num_aces;
        m_total -= 10;
    }
    m_total += card.getCardValue();
}

/*
 * operator overloading of << to print the hand.
*/
std::ostream& operator<< (std::ostream &out, const Hand &hand)
{
    for (auto &card : hand.m_hand)
    {
        std::cout << card.getCard() << " ";
    }
    return out;
}

/*
 * tells if the hand can be split
 * Params: None
 * Returns: bool - t/f if can be split
*/
bool Hand::canSplit()
{
    if (m_has_split_aces)
        return false;
    if (m_hand.size() == 2 && m_hand[0].getCardValue() == m_hand[1].getCardValue())
        return true;
    return false;
}

/*
 * Tells if the hand can be doubled
 * Params: None
 * Returns: bool - t/f if can be doubled
*/
bool Hand::canDouble()
{
    if (m_hand.size() == 2)
        return true;
    return false;
}

/*
 * Used for card splitting. Replace the split card with another from the deck
 * Params: const Card reference - new card from the deck
 * Returns: const Card reference - split card from the hand
*/
const Card& Hand::replaceCard(Card const &card)
{
    Card const &temp = m_hand.back();
    m_hand.pop_back();
    if (temp.getCardValue() == 11)
        --m_num_aces;
    m_total -= temp.getCardValue();
    addCard(card);

    //if split aces
    if (m_num_aces == 2)
        m_has_split_aces = true;
    return temp;
}

/*
 * Used by the Dealer class. Gets the last card added to the hand
 * Params: None
 * Returns: const Card reference - last card added to the hand
*/
const Card& Hand::getUpCard()
{
    return m_hand.back();
}

/*
 * Sets the flag that the hand has split aces.
 * Params: None
 * Returns: Void
*/

void Hand::setSplitAces()
{
    m_has_split_aces = true;
}

/*
 * Tells if you split aces with this hand
 * Params: None
 * Returns: bool - true or false if aces were split from this hand.
*/
bool Hand::hasSplitAces()
{
    return m_has_split_aces;
}

/*
 * Returns the number of aces.
 * Params: None
 * Returns: int - number of aces
*/
int Hand::getNumAces()
{
    return m_num_aces;
}

/*
 * Sets the bet amount for the hand.
 * Params: int bet - amount to bet on the hand.
 * Returns: Void
*/
void Hand::placeBet(int bet)
{
    m_bet = bet;
}

/*
 * gets the current bet amount for the hand
 * Parms: None
 * Returns: int - amount bet
*/
int Hand::getBet()
{
    return m_bet;
}

/*
 * Tells if the hand is a blackjack
 * Params: None
 * Returns: bool - whether the hand is blackjack or not.
*/
bool Hand::hasBlackjack()
{
    if (m_total == 21 && m_hand.size() == 2)
        return true;
    return false;
}

/*
 * Gets if the hand is better than the dealer.
 * Params: Hand dealer_hand - Dealers' hand
 * Returns: bool - win or not
*/
bool Hand::didHandWin(Hand dealer_hand)
{
    if (dealer_hand.getTotal() < getTotal())
        return true;
    return false;
}

/*
 * Tells if the hand is busted
 * Params: None
 * Returns: bool - true if total > 21
*/
bool Hand::isBusted()
{
    if (getTotal() > 21)
        return true;
    return false;
}

/*
 * Sets that the hand has been payed out.
 * Params: None
 * Returns: Void
*/
void Hand::payOut()
{
    m_payed_out = true;
}

/*
 * Gets if the hand has been payed out.
 * Params: None
 * Returns: bool - payed out or not
*/
bool Hand::payedOut()
{
    return m_payed_out;
}
