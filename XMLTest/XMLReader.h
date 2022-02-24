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
	XMLNode* root;
	XMLNode* current;
	stack* tagStack;

	cmatch match;
	smatch stringMatch;

public:
	XMLReader(string fileName);
	~XMLReader();

	bool readFile() throw(IOFileException);

	XMLNode * getRoot();

	void extractAttributes(unordered_map<string, string>& attributes, string text);
private:
	void splitText(char *line, string& tagName, string& params);
	string extractTagName(string& line);
};

inline XMLNode* XMLReader::getRoot()
{
	return root;
}

inline string XMLReader::extractTagName(string& line)
{
	regex_search(line, stringMatch, regex(TAG_NAME));
	string outputName = stringMatch.str();
	line = stringMatch.suffix();
	return outputName;
}

#endif