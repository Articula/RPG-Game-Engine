/*
 * container.h
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <list>
#include <string>

#include "drawable.h"

class Container:
  public Drawable
  {
    public:

	Container();
	virtual ~Container();

	virtual std::list<Container*> GetChildren();

	static bool LoadAttribute (const std::string* attribute,
	                           const std::string* value);

	protected:
    private:

	const std::string*          pId_;
	Container*                  pParent_;
	std::list<Container*> children_;

  };

#endif /* CONTAINER_H_ */
