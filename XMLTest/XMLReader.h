/**********************************************************************************
// Catalog (Header File)
//
// Created:		19 Feb 2022
//	Author:		Ulysses Gomes
// Updated:		19 Feb 2022
//	Author:		Ulysses Gomes
// Compiler:	Visual C++ 19
//
// Description:	XML reader implementation that load data from xml file into
//				XMLNode. If some error is found in file a IOFileExcetion is
//				thrown.
//
**********************************************************************************/

#ifndef _XMLREADER_H_
#define _XMLREADER_H_

#include <string>
#include <regex>
#include <vector>

#include "IODataFile.h"
#include "XMLNode.h"

#define TAG_LINE "<[a-zA-Z]+( [a-zA-Z]+\\=\\\"[\\w\\.]*\\\"| )*\\/>"
#define TAG_NAME "[a-zA-Z]*(?=( [a-zA-Z]+\\=\\\"[\\w\\.]*\\\"| )*((?=>)|(?=\\/>)))"
#define TAG_CONTAINER_BEGIN "<[a-zA-Z]+( [a-zA-Z]+\\=\\\"[\\w\\_\\.]*\\\"| )*>"
#define TAG_CONTAINER_END "<\\/[a-zA-Z]+>"
#define ONLY_PARAMS "([a-zA-Z]+\\=\\\"[\\w\\.]*\\\")"

using std::string;
using std::regex;

typedef list<XMLNode *> stack;

class XMLReader
{
private:
	IODataFile* reader;									// input file reader to read xml file in text mode
	XMLNode* current;									// last xml element container readed
	stack* tagStack;									// stack to validate open and close tag

	cmatch match;										// regex char array match variable
	smatch stringMatch;									// regex string match variable

	vector<XMLNode*> nodes;								// XMLNode container
	int nodesCurrentSize;								// size of XMLNode container

public:
	XMLReader();
	XMLReader(string fileName);
	~XMLReader();

	void openFile(string fileName);						// open xml file
	void closeAndClean();								// close last file and clear all data readed before

	bool readFile() throw(IOFileException);				// read all xml file and store nodes

	XMLNode * operator[](int i);						// get node by index
	long long size();									// elements container size

	void extractAttributes(unordered_map<string, string>& attributes, string * text);	// extract attributes from line readed from xml file
private:
	void splitText(char *line, string& tagName, string& params);						// split params elements attributes
	string extractTagName(string& line);												// element name

	void fillNodeAndStack(XMLNode* node, string* name, string* param);					// fill XMLNode instance and add to nodes

	void addNode(XMLNode * node);														// add node to nodes
};

//----------------------------------------------------------------------------------------

inline XMLNode* XMLReader::operator[](int i)
{
	return nodes[i];
}

//----------------------------------------------------------------------------------------

inline string XMLReader::extractTagName(string& line)
{
	regex_search(line, stringMatch, regex(TAG_NAME));
	string outputName = stringMatch.str();
	line = stringMatch.suffix();
	return outputName;
}

//----------------------------------------------------------------------------------------

inline void XMLReader::fillNodeAndStack(XMLNode* node, string* name, string* params)
{
	strcpy_s(node->name, name->c_str());
	extractAttributes(node->attributes, params);
	tagStack->push_front(node);
	addNode(node);
}

//----------------------------------------------------------------------------------------

inline long long XMLReader::size()
{
	return nodes.size();
}

//----------------------------------------------------------------------------------------

inline void XMLReader::addNode(XMLNode* node)
{
	nodesCurrentSize++;
	nodes.push_back(node);
}

#endif