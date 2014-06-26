/*
 * drawmanager.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */
#include "include/drawmanager.h"
#include "SDL/SDL.h"
#include <string>

DrawManager* DrawManager::pDrawManager_;

DrawManager* DrawManager::getInstance()
{
  if (DrawManager::pDrawManager_ == NULL)
  {
    DrawManager::setInstance(new DrawManager());
  }

  return DrawManager::pDrawManager_;
}

void DrawManager::setInstance(DrawManager* pDrawManager)
{
  if (DrawManager::pDrawManager_ != NULL)
  {
    delete DrawManager::pDrawManager_;
  }

  DrawManager::pDrawManager_ = pDrawManager;
}

DrawManager::DrawManager()
{
	this->pScreenSurface_ = NULL;
	this->pBackgroundSurface_ = NULL;
	this->pPlayerSurface_ = NULL;
}

DrawManager::~DrawManager()
{
}

bool DrawManager::createSurface()
{

	this->pScreenSurface_ = SDL_SetVideoMode(Configuration::GetInstance()->GetScreenWidth(),
	                                     	 Configuration::GetInstance()->GetScreenHeight(),
	                                     	 Configuration::GetInstance()->GetScreenBPP(),
	                                     	 SDL_SWSURFACE);

	if(!this->pScreenSurface_)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool DrawManager::loadFiles()
{
	//Load the background image
	Level* currentLevel = WorldBuilder::GetInstance()->GetLevelById(Configuration::GetInstance()->GetCurrentLevel());
	this->pBackgroundSurface_ = this->loadImage(currentLevel->GetBackground());

    //Load the player image
	this->pPlayerSurface_ = this->loadImage("spritesheet.png");
	this->spriteClipping();

    //If there was a problem in loading the player
    if(this->pBackgroundSurface_ == NULL || pDrawManager_->pPlayerSurface_ == NULL)
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

SDL_Surface* DrawManager::loadImage( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimised surface that will be used
    SDL_Surface* optimisedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimised surface
        optimisedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimised
        if( optimisedImage != NULL )
        {
        	//Map the color key
			Uint32 colorkey = SDL_MapRGB( optimisedImage->format, 0, 0, 0);

			//Set all pixels of color R 0, G 0, B 0 to be transparent
			SDL_SetColorKey( optimisedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }

    //Return the optimized surface
    return optimisedImage;
}

void DrawManager::spriteClipping()
{
	//Clip range for up
	spriteMap[ 0 ].x = 80;
	spriteMap[ 0 ].y = 0;
	spriteMap[ 0 ].w = 18;
	spriteMap[ 0 ].h = 28;

	//Clip range for right
	spriteMap[ 1 ].x = 44;
	spriteMap[ 1 ].y = 0;
	spriteMap[ 1 ].w = 18;
	spriteMap[ 1 ].h = 28;

	//Clip range for down
	spriteMap[ 2 ].x = 4;
	spriteMap[ 2 ].y = 0;
	spriteMap[ 2 ].w = 18;
	spriteMap[ 2 ].h = 28;

	//Clip range for left
	spriteMap[ 3 ].x = 118;
	spriteMap[ 3 ].y = 0;
	spriteMap[ 3 ].w = 18;
	spriteMap[ 3 ].h = 28;
}

void DrawManager::drawPlayer(int x, int y, int clip)
{
	applySurface(x, y, this->pPlayerSurface_, this->pScreenSurface_, &spriteMap[clip]);
}

void DrawManager::drawBackground(SDL_Rect camera)
{
	applySurface(0, 0, pBackgroundSurface_, pScreenSurface_, &camera);
}

void DrawManager::applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool DrawManager::flip()
{
	int ret = SDL_Flip(this->pScreenSurface_);
	return ret;
}

void DrawManager::clearSurfaces()
{
	//Free the surfaces
	SDL_FreeSurface(this->pScreenSurface_);
	SDL_FreeSurface(this->pBackgroundSurface_);
	SDL_FreeSurface(this->pPlayerSurface_);
}
