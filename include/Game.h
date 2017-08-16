#ifndef GAME_H_
#define GAME_H_

#include <iostream>

#include "Player.h"
#include "Deck.h"

using namespace std;

class Game {
private:
	vector<Player *> players;
	vector<int> * playersNumberOfCards;
	Deck deck;
	int numberOfTurns;
	int currentPlayerPosition;
	int n;
	bool isVerbalGame;
	Shape convertToShape(string s);
	Card* convertToCard(string v,Shape s);
public:
	Game(char* configurationFile);
	Game(const Game& g);
	void init();
	void play();
	void printState();        //Print the state of the game as described in the assignment.
	void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
    void CheckReviiya(Player * player);
    Game& operator=(const Game& g);
    ~Game();

};

#endif
