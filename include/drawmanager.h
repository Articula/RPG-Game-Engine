/*
 * drawmanager.h
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */

#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "configuration.h"
#include "worldBuilder.h"

class DrawManager
{
  public:

	static DrawManager* getInstance();
	static void setInstance(DrawManager* pDrawManager);

	static DrawManager* pDrawManager_;
	DrawManager();
	virtual ~DrawManager();

	virtual bool createSurface();
	virtual bool loadFiles();
	SDL_Surface* loadImage(std::string filename);
	virtual void spriteClipping();
	void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
	virtual void drawBackground(SDL_Rect camera);
	virtual void drawPlayer(int x, int y, int clip);
	virtual bool flip();
	virtual void clearSurfaces();

	//The portions of the sprite map to be blitted
	SDL_Rect spriteMap[4];

  private:
	SDL_Surface *pBackgroundSurface_;
	SDL_Surface *pPlayerSurface_;
	SDL_Surface *pScreenSurface_;
};


#endif /* DRAWMANAGER_H_ */
