#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Hand {
private:
	vector<Card*> playerCards;
public:
	Hand();
	Hand(const Hand& other);
	bool addCard(Card &card);
	bool removeCard(Card &card);
	vector<Card*> getPlayerCards();
	int getNumberOfCards(); // Get the number of cards in hand
	string toString(); // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
	virtual ~Hand();
};

#endif
