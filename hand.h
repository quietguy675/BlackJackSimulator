#ifndef HAND_H
#define HAND_H
#include "card.h"
#include <vector>
#include <iostream>

class Hand
{
public:
    enum Moves
    {
        HIT,
        STAND,
        DOUBLE,
        SPLIT,
        MAX_MOVES
    };
private:
    std::vector<Card> m_hand;
    int m_num_aces;
    int m_total;
public:
    Hand(Card const &carda, Card const &cardb);
    Hand();
    int getTotal();
    const Card& getUpCard();
    
    friend std::ostream& operator<< (std::ostream &out, const Hand &hand);
    void addCard(Card const &card);

    bool canSplit();
    bool canDouble();
    const Card& replaceCard(Card const &card);

};

/*std::ostream& operator<< (std::ostream &out, const Hand &hand)
{
    out << "Hit or Stand (h or s)?";
    return out;
}
void addCard(Card const &card);
*/
#endif
