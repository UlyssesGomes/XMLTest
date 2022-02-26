#ifndef _FLOOR_COLLECTION_H_
#define _FLOOR_COLLECTION_H_

#include <iostream>
#include <string>

#include "AutoFillObject.h"
#include "Floor.h"
#include "XMLNode.h"

using namespace std;

class FloorCollection : public AutoFillObject
{
private:
	string imagePath;

	list<Floor*> floorList;

public:

	~FloorCollection()
	{
		for (Floor* floor : floorList)
		{
			delete floor;
		}
	}

	void autoFillElement(XMLNode* node)
	{
		if (node->type == XML_CONTAINER)
		{
			imagePath = node->getAttribute("imagePath");

			Floor* floor;
			for (int u = 0; u < node->childrenSize(); u++)
			{
				floor = new Floor();
				XMLNode* n = (*node)[u];
				floor->autoFillElement(n);
				floorList.push_back(floor);
			}
		}
	}

	void print()
	{
		cout << "Collection imagePath: " << imagePath << endl;
		cout << "----------------------------------------------\n";
		for (Floor* floor : floorList)
			floor->print();
	}
};

#endif