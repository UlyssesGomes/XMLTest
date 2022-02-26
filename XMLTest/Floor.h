#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <iostream>
#include <string>

#include "AutoFillObject.h"

using namespace std;

class Floor : public AutoFillObject
{
private:
	string fileName;
	int width;
	int height;
	int x;
	int y;

public:

	void autoFillElement(XMLNode * node);

	void print();
};

void Floor::autoFillElement(XMLNode * node)
{
	if (node->type == XML_ELEMENT)
	{
		fileName = node->attributes["name"];
		width = stoi(node->attributes["width"]);
		height = stoi(node->attributes["height"]);
		x = stoi(node->attributes["x"]);
		y = stoi(node->attributes["y"]);
	}
}

void Floor::print()
{
	cout << "File name:\t" << fileName << endl;
	cout << "Width:\t\t" << width << endl;
	cout << "Height:\t\t" << height << endl;
	cout << "(x, y) = " << x << ", " << y << endl;
	cout << "===========================================\n";
}

#endif