#ifndef CARD_H_
#define CARD_H_



// a card is uniquely identified by its number and suit
enum Card_Number { Two = 0, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, LAST_CARD_NUMBER };
enum Card_Suit { Spade = 0, Club, Diamond, Heart, LAST_CARD_SUIT };



/**
 * This class represents a card, with a designated number and suit.
 * This is a simple container class.
 */
class Card {

public:

    Card(Card_Number card_number, Card_Suit card_suit);
    ~Card();

    // getters
    Card_Number get_number();
    Card_Suit get_suit();

private:

    // the card's number and suit
    Card_Number m_number;
    Card_Suit m_suit;

};



#endif
