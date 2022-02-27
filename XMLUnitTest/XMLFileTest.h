#ifndef _XML_FILE_TEST_H_
#define _XML_FILE_TEST_H_

#include "pch.h"
#include "../XMLTest/XMLReader.h"
#include "../XMLTest/FloorCollection.h"
#include "../XMLTest/IODataFile.cpp"
#include "../XMLTest/XMLReader.cpp"
#include "../XMLTest/XMLNode.cpp"

class XMLFileTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).

        // close all srteam
        reader.closeAndClean();
    }

    const char XML_SINGLE_CONTAINER[40] = "../XMLTest/xml/landscapeTiles_sheet.xml";
    const char XML_ELEMENTS_LIST[40] = "../XMLTest/xml/singleElementList.xml";
    const char XML_CONTAINER_LIST[40] = "../XMLTest/xml/multiContainerList.xml";

    XMLReader reader;
    FloorCollection floorCollection;
};

#endif