/*
 * worldBuilder.h
 *
 *  Created on: Jan 3, 2014
 *      Author: faye
 */

#ifndef WORLDBUILDER_H_
#define WORLDBUILDER_H_

#include <vector>
#include "container.h"
#include "expat.h"
#include "codeTools.h"
#include "level.h"
#include "iLoadable.h"

class WorldBuilder
{
	public:

	static WorldBuilder* GetInstance();
	static void SetInstance(WorldBuilder* pWorldBuilder);

	ILoadable* CreateElement               (Container*         root,
	                                               const std::string* element,
	                                               const XML_Char**   attribute);
	void       LoadAttributes              (ILoadable*         node,
	                                               const XML_Char**   attribute);
	Level* GetLevelById (int id);


	private:
	static WorldBuilder*      pWorldBuilderInstance_;
	WorldBuilder();
	~WorldBuilder();

	void AddLevel (Level* level);

	 std::vector<Level*> m_levels;
};


#endif /* WORLDBUILDER_H_ */
