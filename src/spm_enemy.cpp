/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_entity.h"
#include "spm_enemy.h"
#include "spm_player.h"
#include "spm_collision.h"
#include "spm_soundfx.h"

Enemy::Enemy(int hp, int damage, int interval, Vector2f speed) : m_OrigHp(hp), m_AttackDamage(damage), m_AttackTimeInterval(interval)
{
	m_Hp = hp;
	m_Speed = speed;
	m_Type = ENEMY;
	m_DoRespawn = false;
};

Enemy::Enemy(const Enemy& instance) {
	*this = instance;
	Entity::EntityList.push_back(this);
	m_EntId = Entity::EntityList.size()-1;
	m_Type = ENEMY;
	m_Frame = rand() % m_FrameCount; // randomize enemy animation
	while(!Respawn());
	m_AttackTimer.Start();
}
    
void Enemy::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    Entity::Load(filename, tilesX, tilesY, numframe, frameRate);
}

void Enemy::Update(double deltaTime)
{
	bool isCollided = false;
	int collidedEntId = INVALID_ID;

	if (m_DoRespawn) {
		if (!Respawn()) return;
	}
   
	m_Velocity = (Player::Marine.m_Position - m_Position);
	m_Velocity.normalise();
	m_Velocity *= m_Speed;

	if (Collision::CollManager.IsCollided(m_Position + (m_Velocity * deltaTime), m_Size, m_EntId, &collidedEntId)) {
    	isCollided = true;
		if (m_AttackTimer.GetTicks() >= m_AttackTimeInterval && PLAYER == Entity::EntityList[collidedEntId]->m_Type) {
			Player::Marine.m_Hp -= m_AttackDamage;
			SoundFX::GameSoundsList[SoundFX::SND_HIT].Play(-1, 1);
			m_AttackTimer.Start(); // reset timer for next attack
		} else {
    		for (int i = 0; i < EnemyMovementTries; ++i) { 
    			m_Velocity = Vector2f(rand()%LVL_WIDTH, rand()%LVL_HEIGHT) - m_Position; // direct movement to player is collided, try other random moves
    			m_Velocity.normalise();
    			m_Velocity *= m_Speed;
    			if (!Collision::CollManager.IsCollided(m_Position + (m_Velocity * deltaTime), m_Size, m_EntId, NULL)) {
    				isCollided = false;
    				break;
    			}
    		}
		}
    }

    if (!isCollided) {
        Collision::CollManager.Remove(m_Position, m_Size, m_EntId);
        m_Position += (m_Velocity * deltaTime);
        Collision::CollManager.Add(m_Position, m_Size, m_EntId);
    }

    CheckLevelEdge();

	Entity::Update(deltaTime);
}

void Enemy::Render(SDL_Surface* m_pScreen)
{
    if (!m_DoRespawn) Entity::Render(m_pScreen);
}

bool Enemy::Respawn()
{
    m_Position = Vector2f(rand()%LVL_WIDTH, rand()%LVL_HEIGHT);
	if (CheckCameraCollision(m_Position, m_Size)) return false;
    if (Collision::CollManager.IsCollided(m_Position, m_Size, m_EntId, NULL)) return false;
	Collision::CollManager.Add(m_Position, m_Size, m_EntId);
	m_DoRespawn = false;
	m_Hp = m_OrigHp; // reset HP to original
	return true;
}

int Enemy::GetAttackDamage() const
{
	return m_AttackDamage;
}	


