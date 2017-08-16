#ifndef CARD_H_
#define CARD_H_

#include <iostream>
using namespace std;

enum Figure
{
	Jack,
	Queen,
	King,
	Ace
		};

enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

class Card
{
private:
    Shape shape;
public:
    Card(Shape s);
	virtual string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
	virtual ~Card();
	string getShape();
	Shape getShapeE();
};

class FigureCard : public Card
{
	private:
		Figure figure;
	public:
		FigureCard(Figure f, Shape s);
		string getFigure();
		Figure getFigureE();
		virtual string toString() override;
};

class NumericCard : public Card {
	private:
		int number;
	public:
		NumericCard(int n,Shape s);
		int getNumber();
		virtual string toString() override;
};
#endif
