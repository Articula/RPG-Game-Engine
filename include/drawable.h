/*
 * drawable.h
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <string>

class Drawable
{
	public:
	Drawable();
	virtual ~Drawable();

	protected:
	    std::string imageName_;
	    int  positionLeft_;
	    int  positionTop_;
	    int  width_;
	    int  height_;
};


#endif /* DRAWABLE_H_ */
