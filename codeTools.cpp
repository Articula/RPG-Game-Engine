/*
 * codeTools.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: faye
 */

#include "include/codeTools.h"
#include <string.h>

CodeTools::CodeTools()
{
}


CodeTools::~CodeTools()
{
}


bool CodeTools::areStringsEqual (const char*  string_a,
                              const char*  string_b)
{
  bool equality = false;

  if ((string_a != NULL) && (string_b != NULL))
  {
    if (strlen(string_a) == 0)
    {
      if (strlen(string_b) == 0)
      {
        equality = true;
      }
      else
      {
        equality = false;
      }
    }
    else
    {
      equality = (strcmp(string_a, string_b) == 0)? true:false;
    }
  }

  return equality;
}


bool CodeTools::areStringsEqual (const char* a,
                              char*       b)
{
  const char* stringA  = a;
  const char* stringB  = b;
  bool        equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (char*       a,
                              const char* b)
{
  const char* stringA  = a;
  const char* stringB  = b;
  bool        equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (char* a,
                              char* b)
{
  const char* stringA  = a;
  const char* stringB  = b;
  bool        equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (const std::string* a,
                              const std::string* b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = (a != NULL) ? a->c_str() : NULL;
  stringB  = (b != NULL) ? b->c_str() : NULL;
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (const std::string* a,
                              std::string*       b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = (a != NULL) ? a->c_str() : NULL;
  stringB  = (b != NULL) ? b->c_str() : NULL;
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (std::string*       a,
                              const std::string* b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = (a != NULL) ? a->c_str() : NULL;
  stringB  = (b != NULL) ? b->c_str() : NULL;
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (std::string*       a,
                              std::string*       b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = (a != NULL) ? a->c_str() : NULL;
  stringB  = (b != NULL) ? b->c_str() : NULL;
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (const std::string a,
                              const std::string b)
{
  const char* stringA  = a.c_str();
  const char* stringB  = b.c_str();
  bool        equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (const std::string* a,
                              const std::string  b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = (a != NULL) ? a->c_str() : NULL;
  stringB  = b.c_str();
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}


bool CodeTools::areStringsEqual (const std::string  a,
                              const std::string* b)
{
  const char* stringA;
  const char* stringB;
  bool        equality = false;

  stringA  = a.c_str();
  stringB  = (b != NULL) ? b->c_str() : NULL;
  equality = CodeTools::areStringsEqual(stringA, stringB);

  return equality;
}
