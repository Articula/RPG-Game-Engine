/*
 * drawable.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */
#include <string>

#include "include/drawable.h"


Drawable::Drawable()
{
  this->positionLeft_ = 0;
  this->positionTop_ = 0;
  this->width_ = 0;
  this->height_ = 0;
  this->imageName_ = std::string("");
}

Drawable::~Drawable()
{
}
