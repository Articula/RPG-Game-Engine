/*
 * configuration.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */
#include "include/configuration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const std::string Configuration::XML_ELEMENT_NAME_CONFIGURATION = "configuration";
const std::string Configuration::XML_ATTRIBUTE_LEVEL_FILE_NAMES = "level-file-names";
const std::string Configuration::XML_ATTRIBUTE_XML_DIRECTORY_PATH = "xml-directory-path";
const std::string Configuration::XML_ATTRIBUTE_IMAGE_DIRECTORY_PATH = "image-directory-path";
const std::string Configuration::XML_ATTRIBUTE_SCREEN_WIDTH = "screen-width";
const std::string Configuration::XML_ATTRIBUTE_SCREEN_HEIGHT = "screen-height";
const std::string Configuration::XML_ATTRIBUTE_SCREEN_BPP = "screen-bpp";
const std::string Configuration::XML_ATTRIBUTE_FPS = "game-fps";
const std::string Configuration::XML_ATTRIBUTE_FIRST_LEVEL_ID = "first-level-id";
const std::string Configuration::XML_ATTRIBUTE_MULTI_MOVEMENT = "multi-direction-movement";

//The screen attributes
const int  Configuration::DEFAULT_SCREEN_WIDTH = 420;
const int  Configuration::DEFAULT_SCREEN_HEIGHT = 420;
const int  Configuration::DEFAULT_SCREEN_BPP = 32;

//The frame rate
const int  Configuration::DEFAULT_FRAMES_PER_SECOND = 20;

Configuration* Configuration::pConfigurationInstance_ = NULL;

Configuration* Configuration::GetInstance()
{
  if (Configuration::pConfigurationInstance_ == NULL)
  {
	  Configuration::SetInstance(new Configuration());
  }
  return Configuration::pConfigurationInstance_;
}

void Configuration::SetInstance(Configuration* pConfiguration)
{
  if (Configuration::pConfigurationInstance_ != NULL)
  {
    // Destroy old instance
    delete Configuration::pConfigurationInstance_;
  }
  // Can be set to NULL
  Configuration::pConfigurationInstance_ = pConfiguration;
}

Configuration::Configuration()
{
	this->xmlDirectory_ = "";
	this->imageDirectory_ = "";
	this->firstLevelID_ = 0;
	this->currentLevel_ = 0;
	this->screenWidth_ = DEFAULT_SCREEN_WIDTH;
	this->screenHeight_ = DEFAULT_SCREEN_HEIGHT;
	this->screenBPP_ = DEFAULT_SCREEN_BPP;
	this->fps_ = DEFAULT_FRAMES_PER_SECOND;
	this->levelWidth_ = 0;
	this->levelHeight_ = 0;
	this->levelBackground_ = "";
	this->multiMove_ = false;

	for (int i = 0; i < MAX_XML_LEVELS; i++)
	{
	  this->levelFileNames_[i] = NULL;
	}
}

Configuration::~Configuration()
{
}

bool Configuration::LoadAttribute (const std::string* attribute,
                                   const std::string* value)
{
  bool rc = true;

  fprintf(stdout, "\n Configuration Attribute received: %s - %s", attribute->c_str(), value->c_str());

  if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_LEVEL_FILE_NAMES))
  {
	  this->SetLevelFileNames(value);
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_XML_DIRECTORY_PATH))
  {
      this->SetXMLDirectoryPath(value->c_str());
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_IMAGE_DIRECTORY_PATH))
  {
	  this->SetImageDirectoryPath(value->c_str());
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_SCREEN_WIDTH))
  {
	  this->SetScreenWidth(atoi(value->c_str()));
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_SCREEN_HEIGHT))
  {
	  this->SetScreenHeight(atoi(value->c_str()));
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_SCREEN_BPP))
  {
	  this->SetScreenBPP(atoi(value->c_str()));
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_FPS))
  {
	  this->SetFPS(atoi(value->c_str()));
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_FIRST_LEVEL_ID))
  {
	  this->SetFirstLevel(atoi(value->c_str()));
  }
  else if (CodeTools::areStringsEqual(attribute, Configuration::XML_ATTRIBUTE_MULTI_MOVEMENT))
  {
	  this->SetMultiMove(atoi(value->c_str()));
  }
  else
  {
    rc = false;
  }

  return rc;
} // LoadAttribute

void Configuration::SetCurrentLevel(int levelId)
{
	this->currentLevel_ = levelId;
}

int Configuration::GetCurrentLevel()
{
	return this->currentLevel_;
}

int Configuration::GetLevelWidth()
{
	return this->levelWidth_;
}

int Configuration::GetLevelHeight()
{
	return this->levelHeight_;
}

void Configuration::SetXMLDirectoryPath(std::string directory)
{
	this->xmlDirectory_ = directory;
}

std::string Configuration::GetXMLDirectoryPath()
{
	return this->xmlDirectory_;
}

void Configuration::SetImageDirectoryPath(std::string directory)
{
	this->imageDirectory_ = directory;
}

void Configuration::SetFirstLevel(int levelID)
{
	this->firstLevelID_ = levelID;
	this->currentLevel_ = levelID;
}

int Configuration::GetFirstLevel()
{
	return this->firstLevelID_;
}

void Configuration::SetMultiMove(int multimove)
{
	this->multiMove_ = multimove;
}

bool Configuration::GetMultiMove()
{
	return this->multiMove_;
}

void Configuration::SetScreenWidth(int width)
{
	this->screenWidth_ = width;
}

int Configuration::GetScreenWidth()
{
	return this->screenWidth_;
}

void Configuration::SetScreenHeight(int height)
{
	this->screenHeight_ = height;
}

int Configuration::GetScreenHeight()
{
	return this->screenHeight_;
}

void Configuration::SetScreenBPP(int bpp)
{
	this->screenBPP_ = bpp;
}

int Configuration::GetScreenBPP()
{
	return this->screenBPP_;
}

void Configuration::SetFPS(int fps)
{
	this->fps_ = fps;
}

int Configuration::GetFPS()
{
	return this->fps_;
}

void Configuration::SetLevelFileNames (const std::string* value)
{
  char* token;
  char xmlFileName[BUFSIZE];
  std::string* xmlFile = NULL;
  int i = 0;

  strcpy(xmlFileName, value->c_str());

  token = strtok(xmlFileName, ",");

  while (this->levelFileNames_[i] != NULL)
  {
    i++;
  }

  while (token != NULL)
  {
    xmlFile = new std::string(token);
    this->levelFileNames_[i] = xmlFile;

    token = strtok(NULL, ",");
    i++;
  }
} // SetLayoutFileNames

const std::string** Configuration::GetLevelFileNames()
{
  return this->levelFileNames_;
}
