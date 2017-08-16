#include "../include/Game.h"
#include <fstream>
#include <sstream>
#include <iterator>

Game::Game(char* configurationFile):players(),playersNumberOfCards(new vector<int>()),deck(),numberOfTurns(1),currentPlayerPosition(1),n(1),isVerbalGame(true)
{
	int count = 0;
	ifstream file (configurationFile);

	if (file.is_open())
	{
		char temp[1000000];
		string value;
		string shape;
		vector<Card*> deckCards;
		string name;
		int strategy;
		int i = 1;

		while(!file.eof())
		{
			file.getline(temp,1000000);
			if(temp[0] != 0 && temp[0] != '#')
			{
				if(count == 0)
				{
					string verbalLine(temp);
					if(verbalLine. compare("0") == 0)
						isVerbalGame = false;
					count++;
				}
				else if(count == 1)
				{
					string numberLine(temp);
					istringstream convert(numberLine);
					convert >> n;
					count++;
				}
				else if(count == 2)
				{
					string cardsLine(temp);
					istringstream iss(cardsLine);

					vector<string> tokens;

					copy(istream_iterator<string>(iss),
						 istream_iterator<string>(),
						 back_inserter(tokens));

					for(unsigned j = 0; j < tokens.size(); j++)
					{
						value = tokens[j];
						shape = value.substr(value.length() - 1);
						value = value.substr(0,value.length() - 1);

						deckCards.insert(deckCards.begin() + j, convertToCard(value,convertToShape(shape)));
					}

					deck.setCards(deckCards);
					count++;
				}
				else
				{
					string nameLine(temp);
					name = nameLine.substr(0,nameLine.find(' '));
					nameLine = nameLine.substr(nameLine.find(' ') + 1);

					istringstream convert1(nameLine);
					convert1 >> strategy;

					switch(strategy)
					{
						case 1:
							players.insert(players.begin() + i - 1,new PlayerType1(name,i));
							break;
						case 2:
							players.insert(players.begin() + i - 1,new PlayerType2(name,i));
							break;
						case 3:
							players.insert(players.begin() + i - 1,new PlayerType3(name,i));
							break;
						case 4:
							players.insert(players.begin() + i - 1,new PlayerType4(name,i));
							break;
					}
					i++;
				}
			}
		}

		for(unsigned int i = 0; i < players.size(); i++)
			players[i]->setPlayersCount(players.size());

		file.close();
	}
	else cout << "Unable to open file" << endl;
}

Game& Game::operator=(const Game& g)
{
	return *this;
}

Game::Game(const Game& g):players(),playersNumberOfCards(new vector<int>()),deck(g.deck),numberOfTurns(g.numberOfTurns),currentPlayerPosition(g.currentPlayerPosition),n(g.n),isVerbalGame(g.isVerbalGame)
{
	int length = g.players.size();

	for(int i = 0; i < length; i++)
		playersNumberOfCards->insert(playersNumberOfCards->begin() + i,7);

	for(int i = 0; i < length; i++)
	{
		Player * p = g.players[i];
		switch(p->strategy)
		{
			case 1:
				players.insert(players.begin() + i,new PlayerType1(*((PlayerType1 *)p)));
				break;
			case 2:
				players.insert(players.begin() + i,new PlayerType2(*((PlayerType2 *)p)));
				break;
			case 3:
				players.insert(players.begin() + i,new PlayerType3(*((PlayerType3 *)p)));
				break;
			case 4:
				players.insert(players.begin() + i,new PlayerType4(*((PlayerType4 *)p)));
				break;
		}
	}
}

Shape Game::convertToShape(string s)
{
	if(s.compare("D") == 0)
		return Diamond;
	else if(s.compare("S") == 0)
		return Spade;
	else if(s.compare("H") == 0)
		return Heart;
	else if(s.compare("C") == 0)
		return Club;

	return Diamond;
}

Card* Game::convertToCard(string v, Shape s)
{
	if(v.compare("J") == 0)
		return new FigureCard(Jack,s);
	else if(v.compare("Q") == 0)
			return new FigureCard(Queen,s);
	else if(v.compare("K") == 0)
			return new FigureCard(King,s);
	else if(v.compare("A") == 0)
			return new FigureCard(Ace,s);

	int number;
	istringstream convert(v);
	convert >> number;
	return new NumericCard(number,s);
}

void Game::init()
{
    numberOfTurns = 0;
    currentPlayerPosition = 1;

    for (unsigned int i = 0; i < players.size(); i++)
    {
        for(unsigned int j = 0; j < 7; j++)
        	players[i]->addCard(*deck.fetchCard());
        (*playersNumberOfCards).insert(playersNumberOfCards->begin() + i, 7);
    }
}

void Game::printState()
{
    cout << "Deck: " << deck.toString() << endl;
    for (unsigned int i = 0; i < players.size(); i++)
        cout << players[i]->getName() << ": " << players[i]->toString() << endl;
}

void Game::printWinner()
{
	bool is1Winner = false;
    bool is2Winners = false;
    Player * winner;
    Player * winner1;
    Player * winner2;

    for (unsigned int i = 0; i < players.size(); i++)
    {
        winner = players[i];
        if(winner->getNumberOfCards() == 0 && is1Winner == false)
        {
            winner1 = winner;
            is1Winner = true;
        }
        else if(winner->getNumberOfCards() == 0 && is1Winner == true)
        {
            winner2 = winner;
            is2Winners = true;
            break;
        }
    }

    if(is2Winners)
        cout << "***** The winners are: " << winner1->getName() << " and " << winner2->getName() << " *****" << endl;
    else
        cout << "***** The Winner is: " << winner1->getName() << " *****" << endl;
}

void Game::printNumberOfTurns()
{
    cout << "Number of turns: " << numberOfTurns << endl;
}

void Game::play()
{
	Card * c;
    bool isWinner = false;
    int askedPlayerPosition;
    vector<Card*> askedPlayerCards;
    Player * winner;

     while(!isWinner)
    {
        numberOfTurns++;
    	int counterWinCards = 0;
        //Player * p = players[currentPlayerPosition - 1];
        string askingValue = players[currentPlayerPosition - 1]->getAskingValue();

         askedPlayerPosition = players[currentPlayerPosition - 1]->getAskedPlayer(*playersNumberOfCards);

     	if(isVerbalGame)
    	{
    		cout << "Turn " << numberOfTurns << endl;
    		cout << "Deck: " << deck.toString() << endl;
    		for(unsigned int i = 0; i < players.size(); i++)
    			cout << players[i]->getName() << ": " << players[i]->toString() << endl;
    		cout << players[currentPlayerPosition - 1]->getName() << " asked " <<  players[askedPlayerPosition - 1]->getName() << " for the value " << askingValue << endl;
    	}

        askedPlayerCards = players[askedPlayerPosition - 1]->getPlayerCards();
        string askedPlayerCardsValue;

		for(unsigned int i = 0; i < askedPlayerCards.size(); i++)
		{
			askedPlayerCardsValue = askedPlayerCards[i]->toString().substr(0,askedPlayerCards[i]->toString().length() - 1);
			if(askingValue.compare(askedPlayerCardsValue) == 0)
			{
				players[currentPlayerPosition - 1]->addCard(*askedPlayerCards[i]);
				players[askedPlayerPosition - 1]->removeCard(*askedPlayerCards[i]);
				counterWinCards++;
			}
		}
		for(int i = 0; i < counterWinCards; i++)
		{
			c = deck.fetchCard();
			if(c != NULL)
				players[askedPlayerPosition - 1]->addCard(*c);
		}

        if(counterWinCards == 0)
        {
     	   c = deck.fetchCard();
     	   if(c != NULL)
     		   players[currentPlayerPosition - 1]->addCard(*c);
        }

        counterWinCards = 0;
        CheckReviiya(players[currentPlayerPosition - 1]);
        CheckReviiya(players[askedPlayerPosition - 1]);

        currentPlayerPosition = ((currentPlayerPosition + 1) % (players.size() + 1));
        if(currentPlayerPosition == 0)
            currentPlayerPosition++;

        for(unsigned int i = 0; i < players.size(); i++)
        {
            winner = players[i];
            if(winner->getNumberOfCards() == 0)
                isWinner = true;
        }

        for(unsigned int i = 0; i < players.size(); i++)
        	playersNumberOfCards->at(i) = players[i]->getNumberOfCards();

        if(!isWinner && isVerbalGame)
            cout << endl;

    }
}

void Game::CheckReviiya(Player * player)
{
	if(player->getNumberOfCards() == 0)
		return;

    int counter = 1;
    string value = player->getPlayerCards()[0]->toString();
    value = value.substr(0,value.length() - 1);

    unsigned int cardsCounter = player->getNumberOfCards();

    for(unsigned int i = 1; i < cardsCounter; i++)
    {
       string nextValue = player->getPlayerCards()[i]->toString();
       nextValue = nextValue.substr(0,player->getPlayerCards()[i]->toString().length() - 1);
       if(value.compare(nextValue) == 0)
            counter++;
        else
        {
            counter = 1;
            value = player->getPlayerCards()[i]->toString();
            value = value.substr(0,value.length() - 1);
        }

       if(counter == 4)
       {
    	   Card * c = player->getPlayerCards()[i - 3];
           player->removeCard(*player->getPlayerCards()[i - 3]);
           delete c;
           c = player->getPlayerCards()[i - 3];
           player->removeCard(*player->getPlayerCards()[i - 3]);
           delete c;
           c = player->getPlayerCards()[i - 3];
           player->removeCard(*player->getPlayerCards()[i - 3]);
           delete c;
           c = player->getPlayerCards()[i - 3];
           player->removeCard(*player->getPlayerCards()[i - 3]);
           delete c;
           counter = 0;

           cardsCounter = player->getNumberOfCards();
           if(i - 3 != cardsCounter)
           {
               value = player->getPlayerCards()[i - 3]->toString();
               value = value.substr(0,value.length() - 1);
               i++;
           }
       }
    }
}

Game::~Game()
{
	for(unsigned int i = 0; i < players.size(); i++)
		delete players[i];
	delete playersNumberOfCards;
}
