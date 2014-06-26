/*
 * level.h
 *
 *  Created on: Nov 24, 2013
 *      Author: faye
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include "container.h"
#include "iLoadable.h"
#include "codeTools.h"

class Level:
	public Container, public ILoadable
{
	public:

	static const std::string XML_ELEMENT_NAME_LEVEL;
	static const std::string XML_ATTRIBUTE_LEVEL_ID;
	static const std::string XML_ATTRIBUTE_LEVEL_HEIGHT;
	static const std::string XML_ATTRIBUTE_LEVEL_WIDTH;
	static const std::string XML_ATTRIBUTE_LEVEL_BACKGROUND;
	static const std::string XML_ATTRIBUTE_PLAYER_START_X;
	static const std::string XML_ATTRIBUTE_PLAYER_START_Y;

    //Initialises the variables
    Level();

    //Destroys the object
    virtual ~Level();

    bool LoadAttribute (const std::string* attribute,
                        const std::string* value);

    int GetId();
    int GetWidth();
    int GetHeight();
    std::string GetBackground();


    private:

    int levelID_;
    int levelHeight_;
    int levelWidth_;
    int playerStartX_;
    int playerStartY_;
    std::string backgroundImage_;

};

#endif /* LEVEL_H_ */
