/*
 * configuration.h
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
#include <string>
#include "codeTools.h"
#include "level.h"

#define MAX_XML_LEVELS 12
#define BUFSIZE 512

class Configuration
{
	public:

	static const std::string XML_ELEMENT_NAME_CONFIGURATION;
	static const std::string XML_ATTRIBUTE_LEVEL_FILE_NAMES;
	static const std::string XML_ATTRIBUTE_XML_DIRECTORY_PATH;
	static const std::string XML_ATTRIBUTE_IMAGE_DIRECTORY_PATH;
	static const std::string XML_ATTRIBUTE_SCREEN_WIDTH;
	static const std::string XML_ATTRIBUTE_SCREEN_HEIGHT;
	static const std::string XML_ATTRIBUTE_SCREEN_BPP;
	static const std::string XML_ATTRIBUTE_FPS;
	static const std::string XML_ATTRIBUTE_FIRST_LEVEL_ID;
	static const std::string XML_ATTRIBUTE_MULTI_MOVEMENT;

	static const int LEVEL_WIDTH;
	static const int LEVEL_HEIGHT;

	static const int DEFAULT_SCREEN_WIDTH;
	static const int DEFAULT_SCREEN_HEIGHT;
	static const int DEFAULT_SCREEN_BPP;
	static const int DEFAULT_FRAMES_PER_SECOND;

	static Configuration* GetInstance();
    static void SetInstance(Configuration* pConfiguration);

	static Configuration* configuration;

	Configuration();
	~Configuration();

	bool LoadAttribute(const std::string* attribute,
	                          const std::string* value);

	void SetCurrentLevel(int levelId);

	int GetCurrentLevel();
	int GetLevelWidth();
	int GetLevelHeight();
	int GetFirstLevel();
	bool GetMultiMove();
	int GetScreenWidth();
	int GetScreenHeight();
	int GetScreenBPP();
	int GetFPS();
	const std::string** GetLevelFileNames();
	std::string GetXMLDirectoryPath();


	private:

	static Configuration*      pConfigurationInstance_;

	void SetLevelFileNames (const std::string* value);
	void SetXMLDirectoryPath(std::string directory);
	void SetImageDirectoryPath(std::string directory);
	void SetFirstLevel(int levelID);
	void SetMultiMove(int multiMove);
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
	void SetScreenBPP(int bpp);
	void SetFPS(int fps);

	const std::string* levelFileNames_[MAX_XML_LEVELS];

	int screenWidth_;
	int screenHeight_;
	int screenBPP_;
	int fps_;
	std::string xmlDirectory_;
	std::string imageDirectory_;
	int firstLevelID_;
	int currentLevel_;
	bool multiMove_;
	std::string levelBackground_;
	int levelWidth_;
	int levelHeight_;
};



#endif /* CONFIGURATION_H_ */
