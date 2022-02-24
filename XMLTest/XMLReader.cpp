#include <string>
#include "XMLReader.h"

XMLReader::XMLReader(string fileName)
{
	root = new XMLNode();
	current = root;
	reader = new IODataFile();
	reader->open2Read(fileName);
	tagStack = new stack();
}

XMLReader::~XMLReader()
{
	delete root;
	reader->closeReadStream();
	delete reader;
	delete tagStack;
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
			newNode = new XMLNode();
			strcpy_s(newNode->name, tagName.c_str());
			extractAttributes(newNode->attributes, params);
			current->addChild(newNode);
			//cout << "N: " << tagName << " P: " << params << endl;
		}
		else if (regex_search(line, match, regex(TAG_CONTAINER_BEGIN)))
		{
			splitText(line, tagName, params);
			//cout << "openN: " << tagName << " P: " << params << endl;
			if (tagStack->size() != 0)
			{
				newNode = new XMLNode();
				
				strcpy_s(newNode->name, tagName.c_str());
				extractAttributes(newNode->attributes, params);
				current->addChild(newNode);
				tagStack->push_front(current);
				current = newNode;
			}
			else 
			{
				strcpy_s(current->name, tagName.c_str());
				extractAttributes(root->attributes, params);
				tagStack->push_front(root);
			}	
		}
		else if (regex_search(line, match, regex(TAG_CONTAINER_END)))
		{
			params = match.str();
			tagName = extractTagName(params);
			//cout << "closeN: " << tagName << endl;
			if (!strcmp(tagStack->front()->name, tagName.c_str()))
			{
				tagStack->pop_front();
				if (tagStack->size())
					current = tagStack->front();
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

void XMLReader::extractAttributes(unordered_map<string, string>& attributes, string text)
{
	regex paramsRegex(ONLY_PARAMS);
	regex_iterator<string::iterator> regexItBegin(text.begin(), text.end(), paramsRegex);
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
