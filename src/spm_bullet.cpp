/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_bullet.h"

Bullet::Bullet()
{
	m_Type = BULLET;
};

Bullet::Bullet(const Bullet& bullet)
{
	*this = bullet;
	m_Type = BULLET;
};

void Bullet::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    Entity::Load(filename, tilesX, tilesY, numframe, frameRate);
    m_Speed = BulletSpeedVector;
    m_EntId = INVALID_ID;
}

void Bullet::Update(double deltaTime)
{
	m_Position += (m_Velocity * deltaTime);

    CheckLevelEdge();

	Entity::Update(deltaTime);
}

void Bullet::Render(SDL_Surface* m_pScreen)
{
    Entity::Render(m_pScreen);
}
