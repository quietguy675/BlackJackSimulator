#include <iostream>
#include <array> // for std::array
#include "player.h" 
#include "card.h" // for Card class
#include "deck.h" // for Deck class
#include "blackjack.h" // for HandResults

char Player::getUserInput()
{
    char temp;
    do
    {
        std::cout << "Hit or stand (h/s)? ";
        std::cin >> temp;
    } while (temp != 's' && temp != 'h');
    return temp;
}

Player::Player(bool is_dealer) : m_hand(), m_total(0), m_is_dealer(is_dealer)
{
    if (is_dealer)
        m_num_dealers++;
}

void Player::deal(Deck &deck)
{
    if (m_is_dealer)
    {
        m_hand[0] = deck.dealCard();
        m_total = m_hand[0].getCardValue();
    }
    else
    {
        m_hand[0] = deck.dealCard();
        m_total = m_hand[0].getCardValue();
        m_hand[1] = deck.dealCard();
        m_total = m_hand[1].getCardValue();
    }
}

int Player::getTotal()
{
    return m_total;
}

HandResults Player::play(Deck &deck)
{
    // this is the player
    if (!m_is_dealer)
    {
        char user_action;
        std::cout << "Your total: " << m_total;
        while(1)
        {
            user_action = getUserInput();
            if (user_action == 's')
                break;
            m_total += deck.dealCard().getCardValue();
            std::cout << "Your total: " << m_total;
            if (m_total > 21)
            {
                std::cout << "\n";
                return HandResults::Break;
            }
        }
    }
    //this is the dealer
    else
    {
        while(m_total < 17)
        {
            m_total += deck.dealCard().getCardValue();
            std::cout << "Dealer total: " << m_total << "\n";
            if (m_total > 21)
                return HandResults::Break;
        }
    }
    return HandResults::Unknown;
}
