#include "Card.h"

Card::Card(Card_Number card_number, Card_Suit card_suit) {
    m_number = card_number;
    m_suit = card_suit;
}

Card::~Card() {
    // do nothing;
}

Card_Number Card::get_number() {
    return m_number;
}

Card_Suit Card::get_suit() {
    return m_suit;
}
