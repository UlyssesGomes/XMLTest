#include "XMLNode.h"

XMLNode::XMLNode()
{
	children = new vector<XMLNode*>();
	type = XML_CONTAINER;
	currentChildrenSize = 0;
}

XMLNode::XMLNode(int type)
{
	children = new vector<XMLNode*>();
	this->type = type;
	currentChildrenSize = 0;
}

XMLNode::~XMLNode()
{
	for (auto u = children->begin(); u != children->end(); u++)
		delete (*u);
	delete children;
}

XMLNode * XMLNode::operator[](int i)
{
	return (*children)[i];
}

long long XMLNode::childrenSize()
{
	return currentChildrenSize;
}