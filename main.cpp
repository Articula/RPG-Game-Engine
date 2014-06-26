/*
 * main.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: faye
 */

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "include/main.h"

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        return false;
    }

    //Set up the screen
    //If there was an error in setting up the screen
    if(!DrawManager::getInstance()->createSurface())
    {
    	return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "RPG Game!", NULL );

    //If everything initialized fine
    return true;
}

void LoadConfiguration()
{
	//Create the XMLParser which will load in the configuration
	XmlParser * parser = new XmlParser();

	//Grab the main xml file to be read in
	std::string * configurationFile = new std::string("main");
	configurationFile->append(".xml");

	//Send to XMLParser
	parser->LoadFile(configurationFile);
}

void LoadLevels()
{
	XmlParser* parser = new XmlParser();
	const std::string* xmlFileName = NULL;
	int i = 0;

	while ((xmlFileName = Configuration::GetInstance()->GetLevelFileNames()[i]) != NULL)
	{
	  parser->LoadFile(xmlFileName);
	  i++;
	}
}


void cleanUp()
{
    DrawManager::getInstance()->clearSurfaces();

    //Quit SDL
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The event structure
    SDL_Event event;

    //Load in the XML files!
    LoadConfiguration();

    //Load in the Levels!
    LoadLevels();

    //Load player sprite
    Player player;

    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if(DrawManager::getInstance()->loadFiles() == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
        	if( event.type == SDL_KEYDOWN )
        	{
        		if(event.key.keysym.sym == SDLK_ESCAPE)
        		{
        			//Quit the program
					quit = true;
        		}
        		else
        		{
					//Handle events for the player
					player.handleInput(0, event.key.keysym.sym);
        		}
        	}
        	//If a key was released
			else if( event.type == SDL_KEYUP )
			{
				//Handle events for the player
				player.handleInput(1, event.key.keysym.sym);
			}
            //If the user has X'ed out the window
			else if(event.type == SDL_QUIT)
            {
                //Quit the program
                quit = true;
            }
        }

        //Move the player
        player.move();

        //Set the camera
        player.set_camera();

        //Redraw the background
        DrawManager::getInstance()->drawBackground(player.get_camera());

        //Show the player on the screen
        player.show();

        //Update the screen
        if(DrawManager::getInstance()->flip() == -1)
        {
            return 1;
        }

        //Cap the frame rate
        if(fps.get_ticks() < 1000 / Configuration::GetInstance()->GetFPS())
        {
            SDL_Delay( ( 1000 / Configuration::GetInstance()->GetFPS()) - fps.get_ticks() );
        }
    }

    //Clean up
    cleanUp();

    return 0;
}
