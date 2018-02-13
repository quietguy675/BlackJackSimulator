#include <iostream> // for cout
#include <cassert> // for assert
#include "deck.h" // for deck class
#include "card.h" // for card class

/*
 * Random number generator used for shuffling the deck.
 * Params: int min - minimum value to be returned
 *         int max - maximum value to be returned
 * Returns: int - random number
*/
int Deck::getRandomNumber(int min, int max)
{
    // static used for efficiency, so we only calculate this value once
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

/*
 * Swaps two cards in the deck
 * Params: Card a reference - carda to swap
 *         Card b reference - cardb to swap
 * Returns: None
*/
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

/*
 * Constructor for the deck. Generates the deck.
 * Params: num_decks - number of decks to add to the shoe.
*/
Deck::Deck(int num_decks) : m_card_index(0), m_cards_drawn(0),
    m_num_decks(num_decks), m_deck_end_counter(0)
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

/*
 * Prints the deck as a grid.
 * Params: None
 * Returns: None
*/

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

/*
 * Shuffles the deck (pseudo)randomly
 * Params: None
 * Returns: Void
*/
void Deck::shuffleDeck()
{
    for (int i = 0; i < m_deck.size(); ++i)
    {
        swapCard(m_deck[i],
            m_deck[getRandomNumber(0, m_deck.size() - 1)]);
    }
    m_card_index = 0;
}

/*
 * deals a card from the deck.
 * Params: None
 * Returns: const Card reference - the card
*/
const Card& Deck::dealCard()
{
    assert(m_cards_drawn < m_num_decks*CARDS_PER_DECK);
    ++m_cards_drawn;
    --m_deck_end_counter;
    if (m_deck_end_counter == 0)
        std::cout << "Deck yellow card out, so last hand in this shoe.\n";
    int temp = m_card_index;
    m_card_index = ++m_card_index % (m_num_decks * CARDS_PER_DECK);
    return m_deck[temp];
}

/*
 * Performs a player-defined cut of the deck.
 * Params: int cut - card# of where to cut.
 * Returns: Void
*/
void Deck::playerCut(int cut)
{
    assert(cut < m_num_decks*CARDS_PER_DECK);
    m_card_index = cut;
    m_cards_drawn = 0;
    std::cout << "Player cut, card index now at: " << m_card_index << "\n";
}

/*
 * Performs a dealer cut. Set to use 80% of the deck.
 * Params: None
 * Returns: Void
*/
void Deck::dealerCut()
{
    m_deck_end_counter = static_cast<int>(0.8 * m_num_decks * CARDS_PER_DECK);
}

/*
 * Gets the number of cards in the deck.
 * Params: None
 * Returns: int - number of cards in the deck.
*/
int Deck::getNumCards()
{
    return m_num_decks * CARDS_PER_DECK;
}

/*
 * Gets the number of drawable cards left
 * Params: None
 * Returns: int - number of drawable cards before re-shuffle
*/
int Deck::getNumCardsLeft()
{
    return m_deck_end_counter;
}

/*
 * Gets if the number of drawable cards <= 0
 * Params: None
 * Returns: bool - more drawable cards or not
*/
bool Deck::moreDrawableCards()
{
    if (m_deck_end_counter >= 0)
        return true;
    return false;
}
