#include <iostream> // for cout
#include <cassert> // for assert
#include "deck.h" // for deck class
#include "card.h" // for card class

int Deck::getRandomNumber(int min, int max)
{
    // static used for efficiency, so we only calculate this value once
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

 
void Deck::swapCard(Card &a, Card &b)
{
    if (&a == &b)
    {
        //Same card, so ignore.
        return;
    }
    Card temp = a;
    a = b;
    b = temp;
}

Deck::Deck(int num_decks) : m_card_index(0), m_cards_drawn(0), m_num_decks(num_decks)
{
    for (int deck = 0; deck < m_num_decks; ++deck)
    {
        for (int suit = 0; suit < Card::MAX_SUITS; ++suit)
        {
            for (int rank = 0; rank < Card::MAX_RANKS; ++rank)
            {
                m_deck.push_back(Card(static_cast<Card::CardRank>(rank),
                   static_cast<Card::CardSuit>(suit)));
            }
        }
    }
}

void Deck::printDeck() const
{
    for (int i = 0; i < m_deck.size(); ++i)
    {
        m_deck[i].printCard();
        std::cout << " ";
        if ((i+1)%CARDS_PER_SUIT == 0)
            std::cout << "\n";
    }
    std::cout << "\n";
}

void Deck::shuffleDeck()
{
    for (int i = 0; i < m_deck.size(); ++i)
    {
        swapCard(m_deck[i],
            m_deck[getRandomNumber(0, m_deck.size() - 1)]);
    }
    m_card_index = 0;
}

const Card& Deck::dealCard()
{
    assert(m_cards_drawn < m_num_decks*CARDS_PER_DECK);
    ++m_cards_drawn;
    int temp = m_card_index;
    m_card_index = ++m_card_index % (m_num_decks * CARDS_PER_DECK);
    return m_deck[temp];
}

void Deck::playerCut(int cut)
{
    assert(cut < m_num_decks*CARDS_PER_DECK);
    m_card_index = cut;
    std::cout << "Player cut, card index now at: " << m_card_index << "\n";
}

void Deck::dealerCut()
{
    m_card_index += static_cast<int>(0.2 * m_num_decks * CARDS_PER_DECK);
    m_card_index = (m_card_index % (m_num_decks * CARDS_PER_DECK));
    std::cout << "Dealer cut, card index now at: " << m_card_index << "\n";
}

int Deck::getNumCards()
{
    return m_num_decks * CARDS_PER_DECK;
}
