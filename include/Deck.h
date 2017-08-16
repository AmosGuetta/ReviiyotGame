#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
private:
	vector<Card*> deckCards;
public:
	Deck();
    Deck(vector<Card*> cards);
	Card* fetchCard();   //Returns the top card of the deck and remove it from the deck
	int getNumberOfCards(); // Get the number of cards in the deck
	string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"1
	virtual ~Deck();
	Deck(const Deck &deck);
	void setCards(vector <Card*> cards);
};

#endif
