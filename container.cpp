/*
 * container.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: faye
 */


#include "include/container.h"
#include <list>
#include <stdio.h>

Container::Container():
  Drawable()
{
  this->pId_             = NULL;
  this->pParent_         = NULL;
  this->children_        = std::list<Container*>();
}

Container::~Container()
{
  // free the children
  std::list<Container*>           children = this->GetChildren();
  std::list<Container*>::iterator it       = children.begin();
  for(; it != children.end(); it++)
  {
    delete (*it);
  }
}

std::list<Container*> Container::GetChildren ()
{
  return this->children_;
}

bool Container::LoadAttribute (const std::string* attribute,
                               const std::string* value)
{
  int rc = true;

  return rc;
} // LoadAttribute
