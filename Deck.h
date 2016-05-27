#ifndef DECK_H_
#define DECK_H_

#include <list>
#include "Card.h"

using namespace std;



/**
 * This class represents a deck of playing cards.  The user can draw cards from the top of the deck,
 * return taken cards back to the deck, and shuffle the deck.
 */
class Deck {

public:

    Deck();
    ~Deck();

    // resets the deck to have all 52 cards, and shuffles them
    void reset();

    // shuffles the cards currently in the deck
    void shuffle();

    // draws a specified number of cards from the deck
    list<Card> draw_cards(int number_of_cards);

    // places a specified set of cards back into the deck
    void return_cards(list<Card> cards_to_replace);

private:

    // the cards currently in the deck
    list<Card> m_cards;

};



#endif
