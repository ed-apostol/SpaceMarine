/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_pickup.h"
#include "spm_collision.h"
#include "spm_player.h"

Pickup::Pickup(int hp, int fire, int time) : m_AddHp(hp), m_FireTimeInterval(fire), m_TimeSpawn(time)
{
    m_Type = PICKUP;
	m_Show = true;
};

Pickup::Pickup(const Pickup& pickup)
{
	*this = pickup;
	Entity::EntityList.push_back(this);
	m_EntId = Entity::EntityList.size()-1;
	m_Type = PICKUP;
	m_Frame = rand() % m_FrameCount; // randomize enemy animation
	while (true) {
        m_Position = Vector2f(rand()%LVL_WIDTH, rand()%LVL_HEIGHT);
		if (!Collision::CollManager.IsCollided(m_Position, m_Size, m_EntId, NULL)) break;
    }
	Collision::CollManager.Add(m_Position, m_Size, m_EntId);
	m_PickupTimerRegen.Start();
};

void Pickup::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    Entity::Load(filename, tilesX, tilesY, numframe, frameRate);
}

void Pickup::TriggerEvent()
{
	m_Show = false;
	Collision::CollManager.Remove(m_Position, m_Size, m_EntId);
	m_PickupTimerRegen.Start();
	if (m_AddHp != -1) Player::Marine.m_Hp += m_AddHp;
	if (m_FireTimeInterval != -1) Player::Marine.UpdateFireTimeInterval(m_FireTimeInterval);
}

void Pickup::Update(double m_DeltaTime)
{
	if (!m_Show && m_PickupTimerRegen.GetTicks() >= m_TimeSpawn) {
		m_Show = true;
		while (true) {
			m_Position = Vector2f(rand()%LVL_WIDTH, rand()%LVL_HEIGHT);
			int tempEntId = INVALID_ID;
			if (!Collision::CollManager.IsCollided(m_Position, m_Size, m_EntId, &tempEntId)) break;
			else {
				if (Entity::EntityList[tempEntId]->m_Type != STATIC) break;
			}
		}
		Collision::CollManager.Add(m_Position, m_Size, m_EntId);
		m_PickupTimerRegen.Start();
	}

	if (m_Show) Entity::Update(m_DeltaTime);
}

void Pickup::Render(SDL_Surface* m_pScreen)
{
    if (m_Show) Entity::Render(m_pScreen);
}
