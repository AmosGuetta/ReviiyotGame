#include <iostream>
#include "../include/Card.h"
#include <sstream>
using namespace std;

Card::Card(Shape s):shape(s)
{
}

Shape Card::getShapeE()
{
	return shape;
}

string Card::getShape()
{
	switch(shape)
	{
	case Diamond:
		return "D";

	case Spade:
		return "S";

	case Heart:
		return "H";

	case Club:
		return "C";
	default:
		return "undefined";
	}
}


FigureCard::FigureCard(Figure f,Shape s):Card(s),figure(f)
{
}

string FigureCard::toString()
{
	return "" + getFigure() + getShape();
}

Figure FigureCard::getFigureE()
{
	return figure;
}

string FigureCard::getFigure()
{
	switch(figure)
	{
	case Jack:
		return "J";

	case Queen:
		return "Q";

	case King:
		return "K";

	case Ace:
		return "A";
	default:
		return "undefined";
	}
}

NumericCard::NumericCard(int n, Shape s):Card(s),number(n)
{
}

int NumericCard::getNumber()
{
    return number;
}
string NumericCard::toString()
{
	stringstream convert;
	convert << number;
	string num;
	convert >> num;
	return num + getShape();
}

Card::~Card()
{
}

