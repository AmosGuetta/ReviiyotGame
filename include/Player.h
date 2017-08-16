#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "Hand.h"

using namespace std;

class Player : public Hand
{
private:
	const string name;
	int playersCount;
public:
    int myPosition;
	int strategy;
    Player(string name, int position, int strag);
    Player(const Player& other);
    virtual string getAskingValue() = 0;
    virtual int getAskedPlayer(vector<int> playersCountCards) = 0;
    int whoIsNext(int nextPlayerPosition);
	string getName();
	void setPlayersCount(int numberOfPlayers);
	virtual ~Player();
};

class PlayerType1 : public Player
{
public:
	PlayerType1(string name, int position);
	PlayerType1(const PlayerType1& other);
    string getAskingValue() override;
    int getAskedPlayer(vector<int> playersCountCards) override;
};

class PlayerType2 : public Player
{
public:
	PlayerType2(string name, int position);
	PlayerType2(const PlayerType2& other);
    string getAskingValue() override;
    int getAskedPlayer(vector<int> playersCountCards) override;
};

class PlayerType3 : public Player
{
private:
    int nextPlayerPosition;
public:
    PlayerType3(string name, int position);
    PlayerType3(const PlayerType3& other);
    string getAskingValue() override;
    int getAskedPlayer(vector<int> playersCountCards) override;
};

class PlayerType4 : public Player
{
private:
    int nextPlayerPosition;
public:
    PlayerType4(string name, int position);
    PlayerType4(const PlayerType4& other);
    string getAskingValue() override;
    int getAskedPlayer(vector<int> playersCountCards) override;
};

#endif
