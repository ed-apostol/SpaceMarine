/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"
#include "spm_bullet.h"
#include "spm_timer.h"
#include <list>

class Player : public Entity
{
public:
	static const int StartHP = 100;

    Player();
	~Player();
    void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
    void HandleInput(SDL_Event event);
    void Update(double m_DeltaTime);
    void Render(SDL_Surface* m_pScreen);

	void SetBullet(const Bullet& bullet);
	void FireBullet();
	void UpdateBullets(double m_DeltaTime);

	void UpdateFireTimeInterval(int fire);
	int GetScore() const;

	static Player Marine;
private:
	int m_Score;
	int m_FireTimeInterval;
	bool m_DoFireBullet;
	Timer m_FireTimer;
	Vector2f m_MousePos;
	Bullet m_Bullet;
	std::list<Bullet*> m_BulletList;
};
