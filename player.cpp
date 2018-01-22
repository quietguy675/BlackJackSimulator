#include <iostream>
#include <vector> // for std::vector
#include <cassert> // for assert
#include "player.h" 
#include "hand.h" // for Hand class
#include "card.h" // for Card class
#include "deck.h" // for Deck class
#include "blackjack.h" // for HandResults

char Player::getUserInput()
{
    char temp;
    
    if (m_hands.back().canDouble() && m_hands.back().canSplit())
    {
        do
        {
            std::cout << "Hit, stand, double or split? (h/s/d/s)?";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd' && temp != 'p');
        return temp;
    } else if (m_hands.back().canDouble())
    {
        do
        {
            std::cout << "Hit, stand, or double? (h/s/d)?";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd');
        return temp;
    } else if (m_hands.back().canSplit())
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

void Player::doSplit(int hands_index, Deck &deck)
{
    m_hands.push_back(Hand(m_hands[hands_index].replaceCard(deck.dealCard()),
        deck.dealCard()));
}

Player::Player()
{
    Hand somehand;
    m_hands.push_back(somehand);
}

void Player::deal(Deck &deck)
{
    m_hands.back().addCard(deck.dealCard());
}

int Player::getTotal()
{
    return m_hands.back().getTotal();
}

HandResults Player::play(Deck &deck)
{
    char user_action;
    printHand();
    std::cout << "Your total: " << m_hands.back().getTotal() << " ";
    while(1)
    {
        user_action = getUserInput();
        if (user_action == 's')
            break;
        else if (user_action == 'p')
            continue;
        else if (user_action == 'd' or user_action == 'h')
            m_hands.back().addCard(deck.dealCard());
        int total = m_hands.back().getTotal();
        std::cout << "Your total: " << total << " ";
        if (total > 21)
        {
            std::cout << "\n";
            return HandResults::Break;
        }
    }
    return HandResults::Unknown;
}

HandResults Player::getResult()
{
    if (m_hands.back().getTotal() > 21)
        return HandResults::Break;
    return HandResults::Unknown;
}

Dealer::Dealer() : Player()
{
}

const Card& Dealer::getUpCard()
{
    return m_hands.back().getUpCard();
}

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

void Player::doCut(Deck &deck)
{
    int total_cards = deck.getNumCards();
    deck.playerCut(getPlayerCut(total_cards));
}

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

void Player::printHand()
{
    if (m_hands.size() == 1)
        std::cout << m_hands.back();
    else
    {
        for (int i = 0; i < m_hands.size(); ++i)
        {
            std::cout << "Hand " << i << ": " << m_hands[i] << "\n";
        }
    }
}

void Player::printHand(int index)
{
    assert(index > 0 && index < m_hands.size());
    std::cout << m_hands[index];
}
