/*
 * player.h
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "configuration.h"
#include "drawmanager.h"
#include "worldBuilder.h"

class Player
{
	public:

	static const int PLAYER_WIDTH;
	static const int PLAYER_HEIGHT;

	static const int PLAYER_SPRITE_UP;
	static const int PLAYER_SPRITE_DOWN;
	static const int PLAYER_SPRITE_LEFT;
	static const int PLAYER_SPRITE_RIGHT;

	static Player* player;

    //Initialises the variables
    Player();

    //Destroys the object
    ~Player();

    //Takes key presses and adjusts the player's velocity
    void handleInput(int type, int key);
    void multiMoveInput(int type, int key);
    void singleMoveInput(int type, int key);

    //Moves the player
    void move();

    //Shows the player on the screen
    void show();

    //Sets the camera over the player
    void set_camera();

    //Checks there isn't another button being pressed when one is released. Updates sprite accordingly.
    void spriteCheck();

    //Retrieve Camera for drawing
    SDL_Rect get_camera();

    private:
    //The X and Y offsets of the player
    int x_;
    int y_;

    //The velocity of the player
    int xVel_;
    int yVel_;

    //Flag to indicate whether to process moving multiple directions or not
    bool multiMove_;

    //Button lock so player can only move one direction at a time
    bool buttonLock_;

    //Flags to indicate which buttons are active
    bool flagUp_;
    bool flagDown_;
    bool flagLeft_;
    bool flagRight_;

    int width_;
    int height_;

    int clip_;

    SDL_Rect camera_;
};

#endif /* PLAYER_H_ */
