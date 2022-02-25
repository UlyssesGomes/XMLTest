/**********************************************************************************
// Catalog (Header File)
//
// Created:		31 Jan 2022
//	Author:		Ulysses Gomes
// Updated:		31 Jan 2022
//	Author:		Ulysses Gomes
// Compiler:	Visual C++ 19
//
// Description:	
//				
//
**********************************************************************************/

#ifndef _AUTO_FILL_OBJECT_H_
#define _AUTO_FILL_OBJECT_H_

#include "XMLNode.h"

class XMLNode;

class AutoFillObject
{
public:
	virtual void autoFillElement(XMLNode * node) = 0;
};

#endif 