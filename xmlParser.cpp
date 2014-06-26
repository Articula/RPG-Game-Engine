/*
 * xmlParser.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */

#include "include/xmlParser.h"
#include <stdio.h>

Container* XmlParser::root = NULL;

XmlParser::XmlParser()
{
	root = new Container();
	this->parser = NULL;
}

XmlParser::~XmlParser()
{
}

void XmlParser::LoadFile(const std::string * xmlFileName)
{
	this->ParseFile(xmlFileName);
}

void XmlParser::ParseFile(const std::string * xmlFileName)
{
	FILE *xmlFile;
	char buffer[BUFSIZE];
	char xmlFilePath[BUFSIZE];
	int stringLength = 0;
	bool endOfStream = false;

	/* TODO: Would be a consideration to remove the bufsize for xml path. a) This is faster than snprintf  b) no size limitation on path
	 * something along the lines of:
	 *
	 * const std::string filePath = Configuration::xmlFilePath() + fileName; then later filePath.c_str();
	 */


	XmlParser::InitParser();

	/* This will be skipped for configuration's parse, but that will set up the directory for the level xml files! */
	if (Configuration::GetInstance()->GetXMLDirectoryPath() != "")
	{
		snprintf(xmlFilePath, BUFSIZE, "%s%s", Configuration::GetInstance()->GetXMLDirectoryPath().c_str(), xmlFileName->c_str());
		fprintf(stdout, "XML File: %s\n", xmlFilePath);
	}
	else
	{
		snprintf(xmlFilePath, BUFSIZE, "%s", xmlFileName->c_str());
	}

	xmlFile = fopen(xmlFilePath, "r");

	if (xmlFile == NULL)
	{
		fprintf(stderr, "Error opening xml layout file \"%s\"\n", xmlFileName->c_str());
		exit(0);
	}
	else
	{
		fprintf(stdout, "File opened successfully: %s", xmlFileName->c_str());
		/* Pass chunks of the XMl file to the parse function, return true if there aren't any issues */
		while ((stringLength = fread(buffer, sizeof(char), BUFSIZE, xmlFile)) != 0) {
			endOfStream = feof(xmlFile);
			this->Parse(buffer, stringLength, endOfStream);
		}
	}

	fclose(xmlFile);

	XmlParser::CloseParser();
}

bool XmlParser::Parse(char * xmlString, int stringLength, bool endOfStream)
{
	bool rc = true;

	if (!XML_Parse(this->parser, xmlString, stringLength, endOfStream)) {
		fprintf(stderr, "Parse error at line %d:\n%s\n",
				(int)XML_GetCurrentLineNumber(this->parser),
				XML_ErrorString(XML_GetErrorCode(this->parser)));

		rc = false;
	}

	return rc;
}

void XmlParser::InitParser ()
{
  this->parser = XML_ParserCreate(NULL);

  /* Sets the functions that will handle the start and end of every bit of XML parsing. Handled by expat. */
  XML_SetElementHandler(this->parser, StartCallBack, EndCallBack);
}


void XmlParser::CloseParser ()
{
  XML_ParserFree(this->parser);
}


inline void XmlParser::StartCallBack (void*             data,
                                      const XML_Char*   element,
                                      const XML_Char**  attribute)
{
	fprintf(stdout, "\n Hit StartCallBack! \n");

	std::string* elementId = new std::string(element);
	ILoadable* node = NULL;

	if(CodeTools::areStringsEqual(elementId, Configuration::GetInstance()->XML_ELEMENT_NAME_CONFIGURATION))
	{
		LoadConfigurationAttributes(attribute);
	}
	else
	{
		/* Else, creation of a new object. */
		node = WorldBuilder::GetInstance()->CreateElement(root, elementId, attribute);
	}


	if (node != NULL)
	{
		WorldBuilder::GetInstance()->LoadAttributes(node, attribute);
	}
} // StartCallBack


inline void XmlParser::EndCallBack (void*           data,
                                    const XML_Char* element)
{
	fprintf(stdout, "\n Hit EndCallBack! \n");
} // EndCallBack


void XmlParser::LoadConfigurationAttributes (const XML_Char** attribute)
{
  int rc = true;
  std::string* attr = NULL;
  std::string* value = NULL;

  for (int i = 0; attribute[i]; i += 2)
  {
    rc = true;
    attr = new std::string(attribute[i]);
    value = new std::string(attribute[i + 1]);

    rc = Configuration::GetInstance()->LoadAttribute(attr, value);

    if (!rc)
    {
    	fprintf(stdout, "\n Unknown configuration attribute: %s", attr->c_str());
    }
  }
} // LoadConfigurationAttributes
