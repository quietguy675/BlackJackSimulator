#include <iostream>
#include <vector> // for std::vector
#include <cassert> // for assert
#include "player.h" 
#include "hand.h" // for Hand class
#include "card.h" // for Card class
#include "deck.h" // for Deck class

/*
 * Constructor. Adds a blank hand to the player.
*/
Player::Player(int num_hands, int money): m_num_hands(num_hands), m_money(money)
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
            std::cout << "Hit, stand, double or split? (h/s/d/p)? ";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd' && temp != 'p');
        return temp;
    } else if (hand.canDouble())
    {
        do
        {
            std::cout << "Hit, stand, or double? (h/s/d)? ";
            std::cin >> temp;
        } while (temp != 's' && temp != 'h' && temp != 'd');
        return temp;
    } else if (hand.canSplit())
    {
        do
        {
            std::cout << "Hit, stand, or split? (h/s/p)? ";
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
 * Gets the amount the player is to bet with min, max, and 0 to pull out.
 * Params: min_bet - minimum bet
 *         max_bet - maximum bet
 * Returns: int - amount bet or 0 for pulling out
*/
int Player::getBetAmount(int min_bet, int max_bet)
{
    int bet_amount = 0;
    do
    {
        std::cout << "How much would you like to bet? (0," << 
            min_bet << "-" << max_bet << "): ";
        std::cin >> bet_amount;
    } while (bet_amount !=0 && bet_amount < min_bet && bet_amount > max_bet);
    return bet_amount;
}

/*
 * Splits the hand into two hands (if they can) auto-draws 1 card for each hand.
 * Can't do this in Hand because would allocate on the heap and have to delete them.
 * Might change to dynamically allocated hands to m_hands and have a destructor delete them.
 * Params: Hand &hand - hand to split
 *         Deck &deck - the current blackjack deck
 * Returns: None
*/
void Player::doSplit(Hand &hand, Deck &deck)
{
    const Card &replaced_card = hand.replaceCard(deck.dealCard());
    if (hand.getNumAces() == 2)
    {    
        m_hands.push_back(Hand(replaced_card,
            deck.dealCard(),
            true));
        hand.setSplitAces();
    }
    m_hands.push_back(Hand(replaced_card,
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
    for (int i = 0; i < m_hands.size(); ++i)
    {
        std::cout << m_hands[i] << " total: " << m_hands[i].getTotal() << " ";
        while(1)
        {
            if (m_hands[i].getTotal() == 21)
            {
                std::cout << "\n";
                break;
            }
            user_action = getUserInput(m_hands[i]);
            if (user_action == 's')
                break;
            else if (user_action == 'p')
            {
                doSplit(m_hands[i], deck);
                if (m_hands[i].hasSplitAces())
                    break;
            } else if (user_action == 'd')
            {
                m_hands[i].addCard(deck.dealCard());
                m_money -= m_hands[i].getBet();
                m_hands[i].placeBet(m_hands[i].getBet() * 2);
                break;
            } else if (user_action == 'h')
                m_hands[i].addCard(deck.dealCard());

            std::cout << m_hands[i] << " total: " << m_hands[i].getTotal() << " ";
            if (m_hands[i].getTotal() > 21)
                break;
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

/*
 * Gets the number of hands the player has.
 * Params: None
 * Returns: int - number of hands the player is playing.
*/
int Player::getNumHands()
{
    return m_hands.size();
}

/*
 * Gets the hands of the player.
 * Params: None
 * Returns: const std::vector<Hand>& - vector of the users' hands.
*/
std::vector<Hand>& Player::getHands()
{
    return m_hands;
}

/*
 * Tells if the player is playing.
 * Params: None
 * Returns: bool - playing or not
*/
bool Player::isPlaying()
{
    return m_is_playing;
}

/*
 * Does the betting
 * Parms: None
 * Returns: Void
*/
void Player::placeBets(int min_bet)
{
    // If player has not enough money, sit them out
    if (min_bet > m_money)
    {
        std::cout << "You lost all your money. no play for you!!\n";
        m_is_playing = false;
        return;
    }
    if (m_num_hands >= 2 && m_money < (min_bet * 4))
    {
        std::cout << "Not enough money for two hands. reducing to one...\n";
        m_num_hands = 1;
        if (m_hands.size() == 2)
            m_hands.pop_back();
    }
    for (int i = 0, n = m_hands.size(); i < n; i++)
    {
        std::cout << "Money: " << m_money << " Hand " << i+1 << ": ";
        int something;
        //2x min bet if playing 2 hands
        if (m_num_hands >= 2)
            something = getBetAmount(2*min_bet, (m_money - 2*min_bet));
        else
            something = getBetAmount(min_bet, m_money);
        if (something == 0 && m_num_hands >= 2)
        {
            --m_num_hands;
            m_hands.erase(m_hands.begin() + i);
            --n;
            continue;
        } else if (something == 0)
        {
            m_is_playing = false;
            m_hands.pop_back();
            return;
        }    
        m_hands[i].placeBet(something);
        m_money -= something;
    }
}

/*
 * Adds money from the table.
 * Params: int money - amount of money to add.
 * Returns: Void
*/
void Player::addMoney(int money)
{
    m_money += money;
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
    std::cout << "Dealer hand: " << m_hands.back() <<
        " total: " << m_hands.back().getTotal() << "\n";
    while(m_hands.back().getTotal() < 17)
    {
        m_hands.back().addCard(deck.dealCard());
        int total = m_hands.back().getTotal();
        std::cout << "Dealer hand: " << m_hands.back() <<
            " total: " << m_hands.back().getTotal() << "\n";
        if (total > 21)
            return HandResults::Break;
    }

    return HandResults::Unknown;
}

/*
 * Does a dealer cut. just passes the call through to the hand.
 * Params: Deck &deck - the deck playing with.
 * Returns: void
*/
void Dealer::doCut(Deck &deck)
{
    deck.dealerCut();
}
