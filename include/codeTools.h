/*
 * codeTools.h
 *
 *  Created on: Jan 2, 2014
 *      Author: faye
 */

#ifndef CODETOOLS_H_
#define CODETOOLS_H_

#include <string>

class CodeTools {
public:

	static bool areStringsEqual (const char* string_a,
	                                 const char* string_b);
	    static bool areStringsEqual (const char* a,
	                                 char*       b);
	    static bool areStringsEqual (char*       a,
	                                 const char* b);
	    static bool areStringsEqual (char*       a,
	                                 char*       b);

	    static bool areStringsEqual (const std::string* a,
	                                 const std::string* b);
	    static bool areStringsEqual (const std::string* a,
	                                 std::string*       b);
	    static bool areStringsEqual (std::string*       a,
	                                 const std::string* b);
	    static bool areStringsEqual (std::string*       a,
	                                 std::string*       b);

	    static bool areStringsEqual (const std::string  a,
	                                 const std::string  b);

	    static bool areStringsEqual (const std::string* a,
	                                 const std::string  b);

	    static bool areStringsEqual (const std::string  a,
	                                 const std::string* b);

private:
	    CodeTools();
	    virtual ~CodeTools();
};


#endif /* CODETOOLS_H_ */
