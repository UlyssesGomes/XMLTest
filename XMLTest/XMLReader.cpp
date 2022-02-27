#include <string>
#include "XMLReader.h"

XMLReader::XMLReader()
{
	current = nullptr;
	reader = new IODataFile();
	tagStack = new stack();
}

XMLReader::XMLReader(string fileName)
{
	current = nullptr;
	reader = new IODataFile();
	tagStack = new stack();
	openFile(fileName);
}

XMLReader::~XMLReader()
{
	closeAndClean();
	delete reader;
	delete tagStack;
}

void XMLReader::openFile(string fileName)
{
	reader->open2Read(fileName);
	nodesCurrentSize = 0;
}

void XMLReader::closeAndClean()
{
	for (XMLNode* node : nodes)
		delete node;
	nodesCurrentSize = 0;
	nodes.resize(0);
	reader->closeReadStream();
}

bool XMLReader::readFile() throw(IOFileException)
{
	char line[2048];
	memset(line, '\0', 2048);
	string tagName;
	string params;
	XMLNode* newNode;
	while (reader->readLine(line))
	{
		if (regex_search(line, match, regex(TAG_LINE)))
		{
			splitText(line, tagName, params);
			newNode = new XMLNode(XML_ELEMENT);
			strcpy_s(newNode->name, tagName.c_str());
			extractAttributes(newNode->attributes, &params);
			if (current)
				current->addChild(newNode);
			else
				addNode(newNode);
		}
		else if (regex_search(line, match, regex(TAG_CONTAINER_BEGIN)))
		{
			splitText(line, tagName, params);

			if (nodesCurrentSize > 0)
			{
				newNode = new XMLNode();
				if (current)
					current->addChild(newNode);

				fillNodeAndStack(newNode, &tagName, &params);
				current = newNode;
			}
			else if (nodesCurrentSize == 0)
			{
				current = new XMLNode();
				fillNodeAndStack(current, &tagName, &params);
			}
		}
		else if (regex_search(line, match, regex(TAG_CONTAINER_END)))
		{
			params = match.str();
			tagName = extractTagName(params);
			if (!strcmp(tagStack->front()->name, tagName.c_str()))
			{
				tagStack->pop_front();
				if (tagStack->size())
					current = tagStack->front();
				else
					current = nullptr;
			}
			else
				throw IOFileException("Closed tag is different.");
		}
		else
		{
			throw IOFileException("Error line format unknow.");
		}
	}
	return true;
}

void XMLReader::splitText(char * line, string& tagName, string& params)
{
	params = match.str();
	tagName = extractTagName(params);
	params = regex_replace(params, regex("<|>|/"), "");
}

void XMLReader::extractAttributes(unordered_map<string, string>& attributes, string * text)
{
	regex paramsRegex(ONLY_PARAMS);
	regex_iterator<string::iterator> regexItBegin(text->begin(), text->end(), paramsRegex);
	regex_iterator<string::iterator> regexItEnd;
	
	string stringParam;
	char param[200];

	char* name;
	char* value;
	char* context;

	while (regexItBegin != regexItEnd)
	{
		stringParam = regexItBegin->str();
		strcpy_s(param, stringParam.c_str());
		context = nullptr;

		name = strtok_s(param, "=", &context);
		value = strtok_s(strtok_s(nullptr, "=", &context), "\"", &context);
		attributes[name] = value;
		regexItBegin++;
	}
}
