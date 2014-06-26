/*
 * xmlParser.h
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <expat.h>
#include <string.h>
#include "configuration.h"
#include "codeTools.h"

#include "container.h"
#include "worldBuilder.h"
#include "iLoadable.h"

#define BUFSIZE 512

class XmlParser
{
  public:
	static Container * root;

	XmlParser();
	virtual ~XmlParser();

	virtual void LoadFile (const std::string* xmlFileName);
	virtual bool Parse    (char* xmlString,
	                       int   stringLength,
	                       bool  endOfStream);

  private:
      static bool setStyle_;
      XML_Parser  parser;

      void CloseParser();
      void InitParser();

      static void StartCallBack(void *, const XML_Char * element, const XML_Char ** attribute);
      static void EndCallBack(void * data, const XML_Char * element);
      void ParseFile            (const std::string* xmlFileName);
      static void       LoadConfigurationAttributes (const XML_Char**   attribute);

};


#endif /* XMLPARSER_H_ */
