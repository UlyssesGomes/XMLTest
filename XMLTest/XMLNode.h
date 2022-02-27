/**********************************************************************************
// Catalog (Header File)
//
// Created:		19 Feb 2022
//	Author:		Ulysses Gomes
// Updated:		19 Feb 2022
//	Author:		Ulysses Gomes
// Compiler:	Visual C++ 19
//
// Description: Class thats represent a xml element. The instance can assume
//				two types, containers and elements. Containers has others xml
//				elements inside. Elements only has attributes. Both types can
//				fill a object that implements AutoFillObject.
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
	vector<XMLNode*> * children;						// if containers type, all children will be store here
	int currentChildrenSize;							// amount of children stored

public:
	unordered_map<string, string> attributes;			// all attributes of this node
	char name[50];										// element name
	int type;											// element type, can be XML_ELEMENT and XML_CONTAINER

public:
	XMLNode();
	XMLNode(int type);
	~XMLNode();

	void addAttribute(string key, string value);		// add element attribute
	void addChild(XMLNode* node);						// add a new child, only if type is XML_CONTAINER

	string getAttribute(string key);					// get attribute by his key

	void fillObject(AutoFillObject * object);			// fill an object instance

	XMLNode * operator[](int i);						// override "[]" operator to access child by index
	long long childrenSize();							// children container size
};

//----------------------------------------------------------------------------------------

inline string XMLNode::getAttribute(string key)
{
	return attributes[key];
}

//----------------------------------------------------------------------------------------

inline void XMLNode::addChild(XMLNode* node)
{
	currentChildrenSize++;
	children->push_back(node);
}

//----------------------------------------------------------------------------------------

inline void XMLNode::addAttribute(string key, string value)
{
	attributes[key] = value;
}

//----------------------------------------------------------------------------------------

inline void XMLNode::fillObject(AutoFillObject * object)
{
	object->autoFillElement(this);
}

#endif