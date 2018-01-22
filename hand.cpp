#include <iostream>
#include <vector>
#include "hand.h"
#include "card.h"

Hand::Hand(Card const &carda, Card const &cardb): m_num_aces(0), m_total(0)
{
    m_hand.push_back(carda);
    m_hand.push_back(cardb);
}

Hand::Hand(): m_num_aces(0), m_total(0)
{
}

int Hand::getTotal()
{
    return m_total;
}

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

std::ostream& operator<< (std::ostream &out, const Hand &hand)
{
    for (auto &card : hand.m_hand)
    {
        std::cout << card.getCard() << " ";
    }
    return out;
}

bool Hand::canSplit()
{
    if (m_hand.size() == 2 && m_hand[0].getCardValue() == m_hand[1].getCardValue())
        return true;
    return false;
}

bool Hand::canDouble()
{
    if (m_hand.size() == 2)
        return true;
    return false;
}

const Card& Hand::replaceCard(Card const &card)
{
    Card const &temp = m_hand.back();
    m_hand.pop_back(); 
    m_hand.push_back(card);
    return temp;
}

const Card& Hand::getUpCard()
{
    return m_hand.back();
}
