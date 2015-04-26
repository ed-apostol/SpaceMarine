/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"
#include "spm_timer.h"

class Pickup : public Entity
{
public:
    Pickup(int hp, int fire, int time);
	Pickup(const Pickup& pickup);
    void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
    void Update(double m_DeltaTime);
	void Render(SDL_Surface* m_pScreen);
	void TriggerEvent();
private:
	int m_FireTimeInterval;
	int m_AddHp;
	Timer m_PickupTimerRegen;
	Timer m_EffectivityTimer; // TODO: implement
	bool m_Show;
	int m_TimeSpawn;
};
