/*
 * level.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: faye
 */
#include "include/level.h"
#include "SDL/SDL.h"
#include <string>

const std::string Level::XML_ELEMENT_NAME_LEVEL = "level";
const std::string Level::XML_ATTRIBUTE_LEVEL_ID = "level-id";
const std::string Level::XML_ATTRIBUTE_LEVEL_HEIGHT = "level-height";
const std::string Level::XML_ATTRIBUTE_LEVEL_WIDTH = "level-width";
const std::string Level::XML_ATTRIBUTE_LEVEL_BACKGROUND = "level-background";
const std::string Level::XML_ATTRIBUTE_PLAYER_START_X = "player-start-x";
const std::string Level::XML_ATTRIBUTE_PLAYER_START_Y = "player-start-y";

Level::Level():
Container(), ILoadable()
{
	this->levelID_ = 0;
	this->levelWidth_ = 0;
	this->levelHeight_ = 0;
	this->playerStartX_ = 0;
	this->playerStartY_ = 0;
	this->backgroundImage_ = "";
}

Level::~Level()
{
}

bool Level::LoadAttribute(const std::string*  attribute,
        				  const std::string*  value)
{
	bool rc = true;

	if (CodeTools::areStringsEqual(attribute, Level::XML_ATTRIBUTE_LEVEL_ID))
	{
		this->levelID_ = atoi(value->c_str());
	}
	else if(CodeTools::areStringsEqual(attribute, Level::XML_ATTRIBUTE_LEVEL_HEIGHT))
	{
		this->levelHeight_ = atoi(value->c_str());
	}
	else if(CodeTools::areStringsEqual(attribute, Level::XML_ATTRIBUTE_LEVEL_WIDTH))
	{
		this->levelWidth_ = atoi(value->c_str());
	}
	else if(CodeTools::areStringsEqual(attribute, Level::XML_ATTRIBUTE_LEVEL_BACKGROUND))
	{
		this->backgroundImage_ = value->c_str();
	}
	else
	{
	  rc = false;
	}

	return rc;

}// LoadAttribute

int Level::GetId()
{
	return this->levelID_;
}

int Level::GetWidth()
{
	return this->levelWidth_;
}

int Level::GetHeight()
{
	return this->levelHeight_;
}

std::string Level::GetBackground()
{
	return this->backgroundImage_;
}

