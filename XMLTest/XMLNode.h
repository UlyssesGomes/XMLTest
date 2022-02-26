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
#include <vector>
#include <string>

#include "AutoFillObject.h"

using std::unordered_map;
using std::vector;
using std::string;

enum XMLNodeType {
	XML_ELEMENT = 1,
	XML_CONTAINER
};

class AutoFillObject;

class XMLNode
{
private:
	vector<XMLNode*> * children;
	int currentChildrenSize;

public:
	unordered_map<string, string> attributes;
	char name[50];
	int type;

public:
	XMLNode();
	XMLNode(int type);
	~XMLNode();

	void addAttribute(string key, string value);
	void addChild(XMLNode* node);

	string getAttribute(string key);

	void fillObject(AutoFillObject * object);

	XMLNode * operator[](int i);
	long long childrenSize();
};

inline string XMLNode::getAttribute(string key)
{
	return attributes[key];
}

inline void XMLNode::addChild(XMLNode* node)
{
	currentChildrenSize++;
	children->push_back(node);
}

inline void XMLNode::addAttribute(string key, string value)
{
	attributes[key] = value;
}

inline void XMLNode::fillObject(AutoFillObject * object)
{
	object->autoFillElement(this);
}

#endif