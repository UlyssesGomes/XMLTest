#include "XMLNode.h"

XMLNode::XMLNode()
{
	children = new list<XMLNode *>();
}

XMLNode::~XMLNode()
{
	for (auto u = children->begin(); u != children->end(); u++)
		delete (*u);
	delete children;
}