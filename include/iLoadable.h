/*
 * iLoadable.h
 *
 *  Created on: Jan 26, 2014
 *      Author: faye
 */

#ifndef ILOADABLE_H_
#define ILOADABLE_H_

class ILoadable
{
	public:

	virtual ~ILoadable() {};

	virtual bool LoadAttribute(const std::string* attribute,
            				   const std::string* value) = 0;

};

#endif /* ILOADABLE_H_ */
