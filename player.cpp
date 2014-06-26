/*
 * player.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: faye
 */
#include "include/player.h"
#include "SDL/SDL.h"

//The dimensions of the player
const int  Player::PLAYER_WIDTH = 28;
const int  Player::PLAYER_HEIGHT = 28;

const int Player::PLAYER_SPRITE_UP = 0;
const int Player::PLAYER_SPRITE_DOWN = 2;
const int Player::PLAYER_SPRITE_LEFT = 3;
const int Player::PLAYER_SPRITE_RIGHT = 1;

Player* Player::player;

Player::Player()
{
	this->width_ = PLAYER_WIDTH;
	this->height_ = PLAYER_HEIGHT;
    //Initialise the location and velocity
    this->x_ = 0;
    this->y_ = 0;
    this->xVel_ = 0;
    this->yVel_ = 0;
    this->clip_ = 0;
    this->multiMove_ = Configuration::GetInstance()->GetMultiMove();

    this->buttonLock_ = false;

    this->flagUp_ = false;
    this->flagDown_ = false;
    this->flagLeft_ = false;
    this->flagRight_ = false;

    SDL_Rect camera = { 0, 0, Configuration::GetInstance()->GetScreenWidth(), Configuration::GetInstance()->GetScreenHeight() };
    this->camera_ = camera;
}

Player::~Player()
{
}

void Player::handleInput(int type, int key)
{
	if(this->multiMove_)
	{
		this->multiMoveInput(type, key);
	}
	else
	{
		this->singleMoveInput(type, key);
	}
}

void Player::singleMoveInput(int type, int key)
{
	//If a key was pressed
	if(type == 0)
	{
		if(!this->buttonLock_)
		{
			//Adjust the velocity
			switch(key)
			{
				case SDLK_UP: this->yVel_ -= this->height_ / 2; this->clip_ = PLAYER_SPRITE_UP; this->flagUp_ = true; this->buttonLock_ = true; break;
				case SDLK_DOWN: this->yVel_ += this->height_ / 2; this->clip_ = PLAYER_SPRITE_DOWN; this->flagDown_ = true; this->buttonLock_ = true; break;
				case SDLK_LEFT: this->xVel_ -= this->width_ / 2; this->clip_ = PLAYER_SPRITE_LEFT; this->flagLeft_ = true; this->buttonLock_ = true; break;
				case SDLK_RIGHT: this->xVel_ += this->width_ / 2; this->clip_ = PLAYER_SPRITE_RIGHT; this->flagRight_ = true; this->buttonLock_ = true; break;
			}
		}
	}
	//If a key was released
	else if(type == 1)
	{
		//Adjust the velocity
		switch(key)
		{
			case SDLK_UP: if(this->flagUp_){this->yVel_ += this->height_ / 2; this->buttonLock_ = false; this->flagUp_ = false;} break;
			case SDLK_DOWN: if(this->flagDown_){this->yVel_ -= this->height_ / 2; this->buttonLock_ = false; this->flagDown_ = false;} break;
			case SDLK_LEFT: if(this->flagLeft_){this->xVel_ += this->width_ / 2; this->buttonLock_ = false; this->flagLeft_ = false;} break;
			case SDLK_RIGHT: if(this->flagRight_){this->xVel_ -= this->width_ / 2; this->buttonLock_ = false; this->flagRight_ = false;} break;
		}
	}
}

void Player::multiMoveInput(int type, int key)
{
	//If a key was pressed
	if(type == 0)
	{
		//Adjust the velocity
		switch(key)
		{
			case SDLK_UP: this->yVel_ -= this->height_ / 2; this->clip_ = PLAYER_SPRITE_UP; this->flagUp_ = true; break;
			case SDLK_DOWN: this->yVel_ += this->height_ / 2; this->clip_ = PLAYER_SPRITE_DOWN; this->flagDown_ = true; break;
			case SDLK_LEFT: this->xVel_ -= this->width_ / 2; this->clip_ = PLAYER_SPRITE_LEFT; this->flagLeft_ = true; break;
			case SDLK_RIGHT: this->xVel_ += this->width_ / 2; this->clip_ = PLAYER_SPRITE_RIGHT; this->flagRight_ = true; break;
		}
	}
	//If a key was released
	else if(type == 1)
	{
		//Adjust the velocity
		switch(key)
		{
			case SDLK_UP: this->yVel_ += this->height_ / 2; this->flagUp_ = false; break;
			case SDLK_DOWN: this->yVel_ -= this->height_ / 2; this->flagDown_ = false; break;
			case SDLK_LEFT: this->xVel_ += this->width_ / 2; this->flagLeft_ = false; break;
			case SDLK_RIGHT: this->xVel_ -= this->width_ / 2; this->flagRight_ = false; break;
		}

		this->spriteCheck();
	}
}

void Player::spriteCheck()
{
	if(this->flagUp_)
	{
		this->clip_ = PLAYER_SPRITE_UP;
	}
	else if(this->flagDown_)
	{
		this->clip_ = PLAYER_SPRITE_DOWN;
	}
	else if(this->flagLeft_)
	{
		this->clip_ = PLAYER_SPRITE_LEFT;
	}
	else if(this->flagRight_)
	{
		this->clip_ = PLAYER_SPRITE_RIGHT;
	}
}

void Player::move()
{
	/* TODO:: Stop grabbing this every time a player moves. */
	/* When the current level is set, pass across player boundries */
	Level* pLevel = WorldBuilder::GetInstance()->GetLevelById(Configuration::GetInstance()->GetCurrentLevel());

    //Move the player sprite left or right
	this->x_ += this->xVel_;

    //If the player sprite went too far to the left or right
    if( ( this->x_ < 0 ) || ( this->x_ + this->width_ > pLevel->GetWidth()) )
    {
        //move back
    	this->x_ -= this->xVel_;
    }

    //Move the player sprite up or down
    this->y_ += this->yVel_;

    //If the player sprite went too far up or down
    if( ( this->y_ < 0 ) || ( this->y_ + this->height_ > pLevel->GetHeight() ) )
    {
        //move back
    	this->y_ -= this->yVel_;
    }
}

void Player::show()
{
    //Show the player sprite
	DrawManager::getInstance()->drawPlayer((this->x_ - this->camera_.x), (this->y_ - this->camera_.y), this->clip_);
}

void Player::set_camera()
{
	/*TODO:: Stop grabbing this every time a player moves.*/
	Level* pLevel = WorldBuilder::GetInstance()->GetLevelById(Configuration::GetInstance()->GetCurrentLevel());

    //Center the camera over the player
    this->camera_.x = (this->x_ + (this->width_ / 2)) - (Configuration::GetInstance()->GetScreenWidth() / 2);
    this->camera_.y = (this->y_ + (this->height_ / 2)) - (Configuration::GetInstance()->GetScreenHeight() / 2);

    //Keep the camera in bounds
    if( this->camera_.x < 0 )
    {
    	this->camera_.x = 0;
    }
    if( this->camera_.y < 0 )
    {
    	this->camera_.y = 0;
    }
    if( this->camera_.x > pLevel->GetWidth() - this->camera_.w )
    {
    	this->camera_.x = pLevel->GetWidth() - this->camera_.w;
    }
    if( this->camera_.y > pLevel->GetHeight() - this->camera_.h )
    {
    	this->camera_.y = pLevel->GetHeight() - this->camera_.h;
    }
}

SDL_Rect Player::get_camera()
{
	return this->camera_;
}
