/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"
#include "spm_timer.h"

class Enemy : public Entity
{
public:
    Enemy(int hp, int damage, int interval, Vector2f speed);
	Enemy(const Enemy& instance);
    void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
    void Update(double m_DeltaTime);
    void Render(SDL_Surface* m_pScreen);
	bool Respawn();
	int GetAttackDamage() const;
private:
	int m_OrigHp;
	int m_AttackDamage;
	int m_AttackTimeInterval;
	Timer m_AttackTimer;
};
