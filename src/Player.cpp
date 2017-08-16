#include "../include/Player.h"
#include <string.h>
#include <limits>
#include <sstream>

Player::Player(string n, int p,int strag):name(n),playersCount(0),myPosition(p),strategy(strag)
{
}

string Player::getName()
{
    return name;
}


Player::Player(const Player& other):Hand(other),name(other.name),playersCount(other.playersCount),myPosition(other.myPosition),strategy(other.strategy)
{
}

void Player::setPlayersCount(int numberOfPlayers)
{
	playersCount = numberOfPlayers;
}

int Player::whoIsNext(int nextPlayerPosition)
{
    if(((nextPlayerPosition + 1) % (playersCount + 1)) == myPosition)
        nextPlayerPosition = ((nextPlayerPosition + 2) % (playersCount + 1));
    else
        nextPlayerPosition = ((nextPlayerPosition + 1) % (playersCount + 1));

    if(nextPlayerPosition == 0)
        nextPlayerPosition++;
    return nextPlayerPosition;
}

PlayerType1::PlayerType1(string name, int position):Player(name,position,1)
{

}

PlayerType1::PlayerType1(const PlayerType1& other):Player(other)
{
}

string PlayerType1::getAskingValue()
{
    Card * mostCard = getPlayerCards().at(getPlayerCards().size() - 1);
    Card * currentCard = mostCard;

    int counterMostCard = 1;
    int counterCurrentCard = 1;

    for (int i = getPlayerCards().size() - 2; i >= 0; i--)
    {
        Card * nextCard = getPlayerCards()[i];
        string a = currentCard->toString().substr(0,currentCard->toString().length() - 1);
        string b = nextCard->toString().substr(0,nextCard->toString().length() - 1);
        if(a.compare(b) == 0)
        {
           counterCurrentCard++;
           if(counterMostCard < counterCurrentCard)
           {
               counterMostCard = counterCurrentCard;
               mostCard = currentCard;
           }
        }
        else
        {
            if(counterMostCard < counterCurrentCard)
            {
                counterMostCard = counterCurrentCard;
                mostCard = currentCard;
            }
            counterCurrentCard = 1;
            currentCard = getPlayerCards()[i];
        }
    }
    return mostCard->toString().substr(0,mostCard->toString().length() - 1);
}

int PlayerType1::getAskedPlayer(vector<int> playersCountCards)
{
    int mostCards = 1;
    int index = 0;
    for(int i = playersCountCards.size() - 1; i >= 0; i--)
    {
        if(mostCards < playersCountCards[i] && i != myPosition - 1)
        {
            mostCards = playersCountCards[i];
            index = i + 1;
        }
    }
    return index;
}

PlayerType2::PlayerType2(string name, int position):Player(name,position,2)
{
}

PlayerType2::PlayerType2(const PlayerType2& other):Player(other)
{
}

string PlayerType2::getAskingValue()
{
    Card * leastCard = getPlayerCards()[0];
    Card * currentCard = leastCard;

    int counterleastCard = getPlayerCards().size();
    int counterCurrentCard = 1;
    for (unsigned int i = 1; i <= getPlayerCards().size() - 1; i++)
    {
        Card * nextCard = getPlayerCards()[i];
        string a = currentCard->toString().substr(0,currentCard->toString().length() - 1);
        string b = nextCard->toString().substr(0,nextCard->toString().length() - 1);
        if(a.compare(b) == 0)
            counterCurrentCard++;
        else
        {
            if(counterleastCard > counterCurrentCard)
            {
                counterleastCard = counterCurrentCard;
                leastCard = currentCard;
            }
            counterCurrentCard = 1;
            currentCard = getPlayerCards()[i];
        }
    }

    if(counterleastCard > counterCurrentCard)
	{
		counterleastCard = counterCurrentCard;
		leastCard = currentCard;
	}
    return leastCard->toString().substr(0,leastCard->toString().length() - 1);
}

int PlayerType2::getAskedPlayer(vector<int> playersCountCards)
{
    int mostCards = 1;
    int index = 0;
    for( int i = playersCountCards.size() - 1; i >= 0; i--)
    {
        if(mostCards < playersCountCards[i] && i != myPosition - 1)
        {
            mostCards = playersCountCards[i];
            index = i + 1;
        }
    }
    return index;
}

PlayerType3::PlayerType3(string name, int position):Player(name,position,3),nextPlayerPosition(1)
{

}
PlayerType3::PlayerType3(const PlayerType3& other):Player(other),nextPlayerPosition(1)
{
}

string PlayerType3::getAskingValue()
{
    string value = getPlayerCards()[getPlayerCards().size() - 1]->toString();
    return value.substr(0,value.length() - 1);
}

int PlayerType3::getAskedPlayer(vector<int> playersCountCards)
{
	if(myPosition == nextPlayerPosition)
		nextPlayerPosition++;
	int temp = nextPlayerPosition;
    nextPlayerPosition = whoIsNext(nextPlayerPosition);
    return temp;

}

PlayerType4::PlayerType4(string name, int position):Player(name,position,4),nextPlayerPosition(1)
{
}
PlayerType4::PlayerType4(const PlayerType4& other):Player(other),nextPlayerPosition(1)
{
}
string PlayerType4::getAskingValue()
{
    string value = getPlayerCards()[0]->toString();
    return value.substr(0,value.length() - 1);
}

int PlayerType4::getAskedPlayer(vector<int> playersCountCards)
{
	if(myPosition == nextPlayerPosition)
		nextPlayerPosition++;
	int temp = nextPlayerPosition;
	nextPlayerPosition = whoIsNext(nextPlayerPosition);
	return temp;
}

Player::~Player()
{
	vector<Card *> hand = getPlayerCards();
	for(unsigned int i = 0; i < hand.size(); i++)
		delete hand[i];
}
