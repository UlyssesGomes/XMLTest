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

#ifndef _XMLNODE_H_
#define _XMLNODE_H_

#include <unordered_map>
#include <list>
#include <string>

using std::unordered_map;
using std::list;
using std::string;

class XMLNode
{
private:
	list<XMLNode*> * children;
	
public:
	char name[50];
	unordered_map<string, string> attributes;

public:
	XMLNode();
	~XMLNode();

	void addAttribute(string key, string value);
	void addChild(XMLNode* node);

	string getAttribute(string key);
};

inline string XMLNode::getAttribute(string key)
{
	return attributes[key];
}

inline void XMLNode::addChild(XMLNode* node)
{
	children->push_back(node);
}

inline void XMLNode::addAttribute(string key, string value)
{
	attributes[key] = value;
}

#endif