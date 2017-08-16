#include "../include/Deck.h"
Deck::Deck():deckCards()
{
}
Deck::Deck(vector<Card*> cards):deckCards(cards)
{
}

Deck::Deck(const Deck & other):deckCards()
{
	int length_deck = other.deckCards.size();
	for(int i = 0; i < length_deck; i++)
	{
		Card * c = other.deckCards[i];
		string value = c->toString().substr(0,c->toString().length() - 1);
		if(value.at(0) >= '1' && value.at(0) <= '9')
		{
			NumericCard * nc = new NumericCard(((NumericCard*)c)->getNumber(),c->getShapeE());
			deckCards.insert(deckCards.begin() + i,nc);
		}
		else
		{
			FigureCard * fc = new FigureCard(((FigureCard*)c)->getFigureE(),c->getShapeE());
			deckCards.insert(deckCards.begin() + i,fc);
		}
	}
}
void Deck::setCards(vector<Card*> cards)
{
	deckCards = cards;
}

Card* Deck::fetchCard()
{
    if(deckCards.size() != 0)
    {
        Card* card = deckCards.at(0);
        deckCards.erase(deckCards.begin() + 0);
        return card;
    }
    return NULL;
}

int Deck::getNumberOfCards()
{
    return deckCards.size();
}

string Deck::toString()
{
	if(getNumberOfCards() == 0)
		return "";
    string result = deckCards.at(0)->toString();
    for (unsigned int i = 1; i < deckCards.size(); i++)
        result = result + " " + deckCards.at(i)->toString();
    return result;
}

Deck::~Deck()
{
	for(unsigned int i = 0; i < deckCards.size(); i++)
			delete deckCards.at(i);
}
