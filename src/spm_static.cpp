/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_entity.h"
#include "spm_static.h"
#include "spm_collision.h"

Static::Static()
{
	m_Type = STATIC;
};

void Static::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    Entity::Load(filename, tilesX, tilesY, numframe, frameRate);
	Entity::EntityList.push_back(this);
	m_EntId = Entity::EntityList.size()-1;
	while (true) {
        m_Position = Vector2f(rand()%LVL_WIDTH, rand()%LVL_HEIGHT);
		if (!Collision::CollManager.IsCollided(m_Position, m_Size, m_EntId, NULL)) break;
    }
	Collision::CollManager.Add(m_Position, m_Size, m_EntId);
};
