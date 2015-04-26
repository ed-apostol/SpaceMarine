/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_player.h"
#include "spm_collision.h"
#include "spm_camera.h"

Player Player::Marine;

Player::Player()
{
	m_DoFireBullet = false;
	m_Hp = StartHP;
	m_Score = 0;
	m_Type = PLAYER;
	m_FireTimeInterval = FireTimeInterval; // init
};

Player::~Player()
{
	m_BulletList.clear();
};

void Player::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    Entity::Load(filename, tilesX, tilesY, numframe, frameRate);
    Entity::EntityList.push_back(this);
	m_Speed = MovementSpeedVector;
    m_EntId = Entity::EntityList.size()-1;
	
    m_Position = Vector2f(LVL_WIDTH/2, LVL_HEIGHT/2);
    Collision::CollManager.Add(m_Position, m_Size, m_EntId);
	m_FireTimer.Start();
}

void Player::HandleInput(SDL_Event event)
{
    Uint32 flag = 0;
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		switch(event.key.keysym.sym) {
		case SDLK_w: {
			flag = MOVE_UP;
			break;
		}
		case SDLK_a: {
			flag = MOVE_LEFT;
			break;
		}
		case SDLK_s: {
			flag = MOVE_DOWN;
			break;
		}
		case SDLK_d: {
			flag = MOVE_RIGHT;
			break;
		}
		default: {
			break;
		}
		}
		if (event.type == SDL_KEYDOWN) {
			m_MoveFlag |= flag;
		} else if (event.type == SDL_KEYUP){
			m_MoveFlag ^= flag;
		}
	}
	if (event.type == SDL_MOUSEMOTION) {
		m_MousePos = Vector2f(event.motion.x, event.motion.y);
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		m_DoFireBullet = true;
		FireBullet();
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		m_DoFireBullet = false;
	}
}

void Player::FireBullet()
{
	Bullet* bullet = new Bullet(m_Bullet);
	m_BulletList.push_back(bullet);
	bullet->m_EntId = INVALID_ID;
	bullet->m_Position = this->m_Position + (this->m_Size / 2);
	bullet->m_Velocity = (Vector2f(Camera::GameCam.m_Rect.x + m_MousePos.x, Camera::GameCam.m_Rect.y + m_MousePos.y) - bullet->m_Position);
	bullet->m_Velocity.normalise();
	bullet->m_Velocity *= bullet->m_Speed;
	m_FireTimer.Start();
}

void Player::UpdateBullets(double deltaTime)
{
	std::vector<std::list<Bullet*>::iterator> bulletDelList;
	// update bullets and check for removal
	for (std::list<Bullet*>::iterator it = m_BulletList.begin(); it != m_BulletList.end(); ++it) {
		(*it)->Update(deltaTime);
		int tempEntId;
		if (Collision::CollManager.IsCollided((*it)->m_Position + ((*it)->m_Velocity * deltaTime), (*it)->m_Size, INVALID_ID, &tempEntId)) { // collision with enemy, remove
			bulletDelList.push_back(it); // save for removal
			// enemy hit, re-spawn
			Entity *tempEnt = Entity::EntityList[tempEntId];
			if (tempEnt->m_Type == ENEMY) {
				tempEnt->m_Hp -= 1; // TODO: use bullet damage here, add weapon class
				if (tempEnt->m_Hp <= 0) {
					Collision::CollManager.Remove(tempEnt->m_Position, tempEnt->m_Size, tempEnt->m_EntId);
					tempEnt->m_DoRespawn = true;
				}
				m_Score += 1; // TODO: use bullet damage here
			}
		} else if (!CheckCameraCollision((*it)->m_Position, (*it)->m_Size)){ // off-screen, remove
			bulletDelList.push_back(it); // save for removal
		} else if (((*it)->m_Position.x <= (*it)->m_Size.x) // collision with level edge, remove
		|| ((*it)->m_Position.x >= LVL_WIDTH - (*it)->m_Size.x)
		|| ((*it)->m_Position.y <= (*it)->m_Size.y)
		|| ((*it)->m_Position.y >= LVL_HEIGHT - (*it)->m_Size.y)) {
			bulletDelList.push_back(it); // save for removal
		} 
	}
	// remove bullets
	for (int i = 0; i < bulletDelList.size(); ++i) {
		m_BulletList.erase(bulletDelList[i]);
	}
}

void Player::Update(double deltaTime)
{
	//add bullets
	if (m_DoFireBullet && m_FireTimer.GetTicks() >= m_FireTimeInterval) {
		FireBullet();
	}

	// bullet update
	UpdateBullets(deltaTime);

	m_Velocity = 0;
	bool addVel;
	int tempEntID = INVALID_ID;
	if (m_MoveFlag & MOVE_UP) {
		addVel = true;
		if (Collision::CollManager.IsCollided(m_Position + ((m_Speed * MoveUpVectMul) * deltaTime), m_Size, m_EntId, &tempEntID)) {
			if (PICKUP == Entity::EntityList[tempEntID]->m_Type) {
				Entity::EntityList[tempEntID]->TriggerEvent();
			} else addVel = false;
		}
		if (addVel) m_Velocity += MoveUpVectMul;
	}
	if (m_MoveFlag & MOVE_LEFT) {
		addVel = true;
		if (Collision::CollManager.IsCollided(m_Position + ((m_Speed * MoveLeftVectMul) * deltaTime), m_Size, m_EntId, &tempEntID)) {
			if (PICKUP == Entity::EntityList[tempEntID]->m_Type) {
				Entity::EntityList[tempEntID]->TriggerEvent();
			} else addVel = false;
		}
		if (addVel) m_Velocity += MoveLeftVectMul;
	}
	if (m_MoveFlag & MOVE_DOWN) {
		addVel = true;
		if (Collision::CollManager.IsCollided(m_Position + ((m_Speed * MoveDownVectMul) * deltaTime), m_Size, m_EntId, &tempEntID)) {
			if (PICKUP == Entity::EntityList[tempEntID]->m_Type) {
				Entity::EntityList[tempEntID]->TriggerEvent();
			} else addVel = false;
		}
		if (addVel) m_Velocity += MoveDownVectMul;
	}
	if (m_MoveFlag & MOVE_RIGHT) {
		addVel = true;
		if (Collision::CollManager.IsCollided(m_Position + ((m_Speed * MoveRightVectMul) * deltaTime), m_Size, m_EntId, &tempEntID)) {
			if (PICKUP == Entity::EntityList[tempEntID]->m_Type) {
				Entity::EntityList[tempEntID]->TriggerEvent();
			} else addVel = false;
		}
		if (addVel) m_Velocity += MoveRightVectMul;
	}

	if (m_Velocity.x != 0 || m_Velocity.y != 0) {
		m_Velocity.normalise();
		m_Velocity *= m_Speed;
		Collision::CollManager.Remove(m_Position, m_Size, m_EntId);
		m_Position += (m_Velocity * deltaTime);
		Collision::CollManager.Add(m_Position, m_Size, m_EntId);
	}

    CheckLevelEdge();
	Entity::Update(deltaTime);

	// Game over...
	if (m_Hp <= 0) {
		m_Active = false;
		Collision::CollManager.Remove(m_Position, m_Size, m_EntId);	
	}
}

void Player::SetBullet(const Bullet& bullet)
{
	m_Bullet = bullet;
}

void Player::Render(SDL_Surface* m_pScreen)
{
	for (std::list<Bullet*>::iterator it = m_BulletList.begin(); it != m_BulletList.end(); ++it) {
		(*it)->Render(m_pScreen);
	}

    Entity::Render(m_pScreen);
}

void Player::UpdateFireTimeInterval(int fire) 
{
	m_FireTimeInterval -= fire;
	if (m_FireTimeInterval < MinimumFireTimeInterval) m_FireTimeInterval = MinimumFireTimeInterval;
}

int Player::GetScore() const
{
	return m_Score;
}
