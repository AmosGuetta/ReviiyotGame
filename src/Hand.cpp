#include "../include/Hand.h"
#include <sstream>
#include <vector>

Hand::Hand():playerCards()
{
}

Hand::Hand(const Hand& other):playerCards()
{
	int length = other.playerCards.size();
	for(int i = 0; i < length; i++)
	{
		Card * c = other.playerCards[i];
		string value = c->toString().substr(0,c->toString().length() - 1);
		if(value.at(0) >= '1' && value.at(0) <= '9')
		{
			NumericCard * nc = new NumericCard(((NumericCard*)c)->getNumber(),c->getShapeE());
			addCard(*nc);
		}
		else
		{
			FigureCard * fc = new FigureCard(((FigureCard*)c)->getFigureE(),c->getShapeE());
			addCard(*fc);
		}
	}
}
bool Hand::addCard(Card &card)
{
    string value = card.toString().substr(0,card.toString().length() - 1);
    string shape = card.getShape();

    if(value.at(0) >= '1' && value.at(0) <= '9')
    {
        NumericCard * addCard = ((NumericCard*)&card);

        for (unsigned int i = 0; i < playerCards.size(); i++)
        {
            string valueCurrentCard = playerCards[i]->toString().substr(0,playerCards[i]->toString().length() - 1);
            if(valueCurrentCard.at(0) >= '1' && valueCurrentCard.at(0) <= '9')
            {
                int valueHandCard = ((NumericCard*)playerCards[i])->getNumber();

                if(valueHandCard > addCard->getNumber() || (valueHandCard == addCard->getNumber() && playerCards[i]->getShapeE() >= card.getShapeE()))
                {
                    playerCards.insert(playerCards.begin() + i, &card);
                    return true;
                }
            }
            else
            {
            	playerCards.insert(playerCards.begin() + i, &card);
            	return true;
            }
        }
        playerCards.insert(playerCards.end(), &card);
    }
    else
	{
    	FigureCard * addCard = ((FigureCard*)&card);

		for (unsigned int i = 0; i < playerCards.size(); i++)
		{
			string valueCurrentCard = playerCards[i]->toString().substr(0,playerCards[i]->toString().length() - 1);
			if(!(valueCurrentCard.at(0) >= '1' && valueCurrentCard.at(0) <= '9'))
			{
				Figure valueHandCard = ((FigureCard*)playerCards[i])->getFigureE();
				Shape shapeHandCard = playerCards[i]->getShapeE();

				if(valueHandCard > addCard->getFigureE() || (valueHandCard == addCard->getFigureE() && shapeHandCard >= addCard->getShapeE()))
				{
					playerCards.insert(playerCards.begin() + i, &card);
					return true;
				}
			}
		}
		playerCards.insert(playerCards.end(), &card);
		return true;
	}
    return false;
}

bool Hand::removeCard(Card &card)
{
    string value = card.toString().substr(0,card.toString().length() - 1);
    string shape = card.getShape();

    if(value.at(0) >= '1' && value.at(0) <= '9')
	{
		NumericCard * addCard = ((NumericCard*)&card);

		for (unsigned int i = 0; i < playerCards.size(); i++)
		{
			string valueCurrentCard = playerCards[i]->toString().substr(0,playerCards[i]->toString().length() - 1);
			if(valueCurrentCard.at(0) >= '1' && valueCurrentCard.at(0) <= '9')
			{
				int valueHandCard = ((NumericCard*)playerCards[i])->getNumber();

				if(valueHandCard == addCard->getNumber() && playerCards[i]->getShapeE() == card.getShapeE())
				{
					playerCards.erase(playerCards.begin() + i);
					return true;
				}
			}
		}
	}
	else
	{
		FigureCard * addCard = ((FigureCard*)&card);

		for (unsigned int i = 0; i < playerCards.size(); i++)
		{
			string valueCurrentCard = playerCards[i]->toString().substr(0,playerCards[i]->toString().length() - 1);
			if(!(valueCurrentCard.at(0) >= '1' && valueCurrentCard.at(0) <= '9'))
			{
				Figure valueHandCard = ((FigureCard*)playerCards[i])->getFigureE();
				Shape shapeHandCard = playerCards[i]->getShapeE();

				if(valueHandCard == addCard->getFigureE() && shapeHandCard == addCard->getShapeE())
				{
					playerCards.erase(playerCards.begin() + i);
					return true;
				}
			}
		}
	}
	return false;
}

int Hand::getNumberOfCards()
{
    return playerCards.size();
}

vector<Card*> Hand::getPlayerCards()
{
    return playerCards;
}

string Hand::toString()
{
	if(getNumberOfCards() == 0)
		return "";
    string result = playerCards[0]->toString();
    for (unsigned int i = 1; i < playerCards.size(); i++)
        result = result + " " + playerCards[i]->toString();
    return result;
}

Hand::~Hand()
{

}
