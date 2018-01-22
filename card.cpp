#include <iostream>
#include <string>
#include "card.h"

Card::CardRank Card::getRank() const
{
    return m_rank;
}

std::string Card::getCard() const
{
    std::string holder = "";
    switch (m_rank)
    {
        case RANK_2:        holder += '2'; break;
        case RANK_3:        holder += '3'; break;
        case RANK_4:        holder += '4'; break;
        case RANK_5:        holder += '5'; break;
        case RANK_6:        holder += '6'; break;
        case RANK_7:        holder += '7'; break;
        case RANK_8:        holder += '8'; break;
        case RANK_9:        holder += '9'; break;
        case RANK_10:       holder += 'T'; break;
        case RANK_JACK:     holder += 'J'; break;
        case RANK_QUEEN:    holder += 'Q'; break;
        case RANK_KING:     holder += 'K'; break;
        case RANK_ACE:      holder += 'A'; break;
    }
 
    switch (m_suit)
    {
        case SUIT_CLUB:     holder += 'C'; break;
        case SUIT_DIAMOND:  holder += 'D'; break;
        case SUIT_HEART:    holder += 'H'; break;
        case SUIT_SPADE:    holder += 'S'; break;
    }
    return holder;
}

void Card::printCard() const
{
    switch (m_rank)
    {
        case RANK_2:        std::cout << '2'; break;
        case RANK_3:        std::cout << '3'; break;
        case RANK_4:        std::cout << '4'; break;
        case RANK_5:        std::cout << '5'; break;
        case RANK_6:        std::cout << '6'; break;
        case RANK_7:        std::cout << '7'; break;
        case RANK_8:        std::cout << '8'; break;
        case RANK_9:        std::cout << '9'; break;
        case RANK_10:        std::cout << 'T'; break;
        case RANK_JACK:        std::cout << 'J'; break;
        case RANK_QUEEN:    std::cout << 'Q'; break;
        case RANK_KING:        std::cout << 'K'; break;
        case RANK_ACE:        std::cout << 'A'; break;
    }
 
    switch (m_suit)
    {
        case SUIT_CLUB:        std::cout << 'C'; break;
        case SUIT_DIAMOND:    std::cout << 'D'; break;
        case SUIT_HEART:    std::cout << 'H'; break;
        case SUIT_SPADE:    std::cout << 'S'; break;
    }
}

int Card::getCardValue() const
{
    switch (m_rank)
    {
    case RANK_2:        return 2;
    case RANK_3:        return 3;
    case RANK_4:        return 4;
    case RANK_5:        return 5;
    case RANK_6:        return 6;
    case RANK_7:        return 7;
    case RANK_8:        return 8;
    case RANK_9:        return 9;
    case RANK_10:        return 10;
    case RANK_JACK:        return 10;
    case RANK_QUEEN:    return 10;
    case RANK_KING:        return 10;
    case RANK_ACE:        return 11;
    }
    
    return 0;
}
