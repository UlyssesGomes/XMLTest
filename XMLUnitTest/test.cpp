#include <regex>
#include <cstdlib>

#include "pch.h"
#include "XMLFileTest.h"


TEST_F(XMLFileTest, TestSingleElementListRead) 
{
	reader.openFile(XML_ELEMENTS_LIST);
	reader.readFile();

	EXPECT_EQ(reader.size(), 4);

	string  templateName = "landscapeTiles_00#.png";
	string name;
	char charNumber[5];
	for (int u = 0; u < reader.size(); u++)
	{
		itoa(u, charNumber, 10);
		name = regex_replace(templateName, regex("#"), charNumber);

		EXPECT_EQ(strcmp(reader[u]->getAttribute("name").c_str(), name.c_str()), 0);
	}
}

TEST_F(XMLFileTest, TestMultiContainerListRead)
{
	reader.openFile(XML_CONTAINER_LIST);
	reader.readFile();

	EXPECT_EQ(reader.size(), 3);

	string templateContainerName = "sheet#.png";
	string singleFileName = "landscapeTiles_#0@.png";
	string name;
	char charNumber[5];
	int elementCount = 0;
	for (int u = 0; u < reader.size(); u++)
	{
		itoa(u+1, charNumber, 10);
		name = regex_replace(templateContainerName, regex("#"), charNumber);

		EXPECT_EQ(strcmp(reader[u]->getAttribute("imagePath").c_str(), name.c_str()), 0);

		itoa(elementCount, charNumber, 10);
		string elementTemplate = regex_replace(singleFileName, regex("#"), charNumber);
		for (int g = 0; g < reader[u]->childrenSize(); g++)
		{
			itoa(g, charNumber, 10);
			name = regex_replace(elementTemplate, regex("@"), charNumber);
			XMLNode* n = reader[u];
			n = (*n)[g];
			EXPECT_EQ(strcmp(n->getAttribute("name").c_str(), name.c_str()), 0);
		}

		elementCount++;
	}
}

TEST_F(XMLFileTest, TestSingleContainerListRead)
{
	reader.openFile(XML_SINGLE_CONTAINER);
	reader.readFile();
	

	EXPECT_EQ(reader.size(), 1);

	reader[0]->fillObject(&floorCollection);

	EXPECT_EQ(strcmp(floorCollection.imagePath.c_str(), "sheet.png"), 0);

	EXPECT_EQ(floorCollection.floorList.size(), 128);

	string  templateName1 = "landscapeTiles_00#.png";
	string  templateName2 = "landscapeTiles_0#.png";
	string  templateName3 = "landscapeTiles_#.png";
	string name;
	char charNumber[5];
	int floorListSize = floorCollection.floorList.size();
	for (int u = 0; u < floorListSize; u++)
	{
		itoa(u, charNumber, 10);
		if (u > 99)
			name = regex_replace(templateName3, regex("#"), charNumber);
		else if(u > 9)
			name = regex_replace(templateName2, regex("#"), charNumber);
		else 
			name = regex_replace(templateName1, regex("#"), charNumber);

		Floor * f = floorCollection.floorList.front();
		EXPECT_EQ(strcmp(name.c_str(), f->getFileName().c_str()), 0);

		EXPECT_GT(f->getWidth(), 130);
		EXPECT_GT(f->getHeight(), 80);

		EXPECT_LT(f->getWidth(), 140);
		EXPECT_LT(f->getHeight(), 132);

		floorCollection.floorList.pop_front();
	}
}