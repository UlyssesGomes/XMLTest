/**********************************************************************************
// Catalog (Header File)
//
// Created:		19 Feb 2022
//	Author:		Ulysses Gomes
// Updated:		19 Feb 2022
//	Author:		Ulysses Gomes
// Compiler:	Visual C++ 19
//
// Description:	
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
	IODataFile* reader;
	XMLNode* current;
	stack* tagStack;

	cmatch match;
	smatch stringMatch;

	vector<XMLNode*> nodes;
	int nodesCurrentSize;

public:
	XMLReader(string fileName);
	~XMLReader();

	bool readFile() throw(IOFileException);

	XMLNode * operator[](int i);
	long long size();

	void extractAttributes(unordered_map<string, string>& attributes, string * text);
private:
	void splitText(char *line, string& tagName, string& params);
	string extractTagName(string& line);

	void fillNodeAndStack(XMLNode* node, string* name, string* param);

	void addNode(XMLNode * node);
};

inline XMLNode* XMLReader::operator[](int i)
{
	return nodes[i];
}

inline string XMLReader::extractTagName(string& line)
{
	regex_search(line, stringMatch, regex(TAG_NAME));
	string outputName = stringMatch.str();
	line = stringMatch.suffix();
	return outputName;
}

inline void XMLReader::fillNodeAndStack(XMLNode* node, string* name, string* params)
{
	strcpy_s(node->name, name->c_str());
	extractAttributes(node->attributes, params);
	tagStack->push_front(node);
	addNode(node);
}

inline long long XMLReader::size()
{
	return nodes.size();
}

inline void XMLReader::addNode(XMLNode* node)
{
	nodesCurrentSize++;
	nodes.push_back(node);
}

#endif