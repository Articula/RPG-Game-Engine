/*
 * worldBuilder.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: faye
 */

#include "include/worldBuilder.h"
#include <stdio.h>

WorldBuilder* WorldBuilder::pWorldBuilderInstance_ = NULL;

WorldBuilder* WorldBuilder::GetInstance()
{
  if (WorldBuilder::pWorldBuilderInstance_ == NULL)
  {
	  WorldBuilder::SetInstance(new WorldBuilder());
  }
  return WorldBuilder::pWorldBuilderInstance_;
}

void WorldBuilder::SetInstance(WorldBuilder* pWorldBuilder)
{
  if (WorldBuilder::pWorldBuilderInstance_ != NULL)
  {
    // Destroy old instance
    delete WorldBuilder::pWorldBuilderInstance_;
  }
  // Can be set to NULL
  WorldBuilder::pWorldBuilderInstance_ = pWorldBuilder;
}

WorldBuilder::WorldBuilder()
{

}

WorldBuilder::~WorldBuilder()
{

}

ILoadable* WorldBuilder::CreateElement (Container*          root,
                                        const std::string*  element,
                                        const XML_Char**    attribute)
{
	ILoadable* node = NULL;
	int rc = true;

	if (CodeTools::areStringsEqual(element, Level::XML_ELEMENT_NAME_LEVEL))
	{
	  node = (node == NULL) ? new Level() : new Level();
	  this->AddLevel(dynamic_cast<Level*>(node));
	}
	else
	{
	  rc = false;
	}

	if (!rc)
	{
	    fprintf(stderr, "Unknown element: %s \n", element->c_str());
	}

	  return node;

} // CreateElement

void WorldBuilder::LoadAttributes (ILoadable*        node,
                                   const XML_Char**  attribute)
{
  int rc = true;
  std::string* attr = NULL;
  std::string* value = NULL;

  for (int i = 0; attribute[i]; i += 2)
  {
    rc = true;
    attr = new std::string(attribute[i]);
    value = new std::string(attribute[i + 1]);

    rc = node->LoadAttribute(attr, value);

    if (!rc)
    {
    	fprintf(stderr, "Unknown object attribute: %s", attr->c_str());
    }
  }
} // LoadAttributes

void WorldBuilder::AddLevel(Level* level)
{
	if (level != NULL)
	{
		this->m_levels.push_back(level);
	}
} // AddLevel

Level* WorldBuilder::GetLevelById(int id)
{
	for(int i = 0; i < (int)this->m_levels.size(); i++)
	{
		Level* level = this->m_levels.at(i);
		if(level != NULL && (level->GetId() == id))
		{
			return level;
		}
	}

	return NULL;
}
