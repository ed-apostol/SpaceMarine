/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_entity.h"
#include "spm_surface.h"
#include "spm_camera.h"
#include "spm_collision.h"

std::vector<Entity*> Entity::EntityList;

Entity::Entity()
{
    this->m_pSurface = NULL;
    this->m_TilesX = 0;
    this->m_TilesY = 0;
    this->m_Size.x = 0;
    this->m_Size.y = 0;
    this->m_Frame = 0;
    this->m_FrameCount =0;
    this->m_FrameInterval = 0;
    this->m_FrameTimeRemaining = 0;

    this->m_Size.x = 0;
    this->m_Size.y = 0;

    this->m_MoveFlag = 0;
    this->m_Velocity = 0;
    this->m_Speed = 0;
	this->m_Hp = 0;

	this->m_Active = true;
	this->m_DoRespawn = false;
}

void Entity::Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate)
{
    this->m_pSurface = Surface::OnLoad(filename);
    this->m_TilesX = tilesX;
    this->m_TilesY = tilesY;
    this->m_Size.x = m_pSurface->w / tilesX;
    this->m_Size.y = m_pSurface->h / tilesY;
    this->m_Frame = 0;
    this->m_FrameCount = numframe;
    this->m_FrameInterval = 1 / frameRate;
    this->m_FrameTimeRemaining = m_FrameInterval;

    this->m_MoveFlag = 0;
    this->m_Velocity = 0;
}

Entity::~Entity()
{
    SDL_FreeSurface(m_pSurface);
}

void Entity::HandleInput(SDL_Event event)
{
    // None
}

void Entity::Update(double deltaTime)
{
    m_FrameTimeRemaining -= deltaTime;
    if(m_FrameTimeRemaining < 0) {
        m_Frame++;
        m_Frame %= m_FrameCount;
        m_FrameTimeRemaining = m_FrameInterval;
    }
}

void Entity::Render(SDL_Surface* screen)
{
    SDL_Rect location = GetBounds();
    SDL_Rect clip = GetFrameBounds();

    if (!IsRenderable()) return;
    Surface::OnDraw(m_pSurface, &clip, screen, &location);
}

void Entity::TriggerEvent() 
{
}

void Entity::CheckLevelEdge()
{
    if (m_Position.x < 0) m_Position.x = 0;
    if (m_Position.y < 0) m_Position.y = 0;
    if (m_Position.x > LVL_WIDTH - m_Size.x) m_Position.x = (Sint16)(LVL_WIDTH - m_Size.x);
    if (m_Position.y > LVL_HEIGHT - m_Size.y) m_Position.y = (Sint16)(LVL_HEIGHT - m_Size.y);
}

bool Entity::IsRenderable()
{
    SDL_Rect bgBox, coll;

    bgBox.x = m_Position.x;
    bgBox.y = m_Position.y;
    bgBox.w = m_Size.x;
    bgBox.h = m_Size.y;

    coll = Intersection(bgBox, Camera::GameCam.m_Rect);

    if (coll.w == 0 && coll.h == 0) return false;
    return true;
}

SDL_Rect Entity::GetBounds()
{
    SDL_Rect bounds;
    bounds.x = (Sint16)(m_Position.x - Camera::GameCam.m_Rect.x);
    bounds.y = (Sint16)(m_Position.y - Camera::GameCam.m_Rect.y);
    bounds.w = (Sint16)(m_Size.x);
    bounds.h = (Sint16)(m_Size.y);

    return bounds;
}

SDL_Rect Entity::GetFrameBounds()
{
    SDL_Rect frameBounds;
    frameBounds.x = (Sint16)(m_Frame % m_TilesX * m_Size.x);
    frameBounds.y = (Sint16)(m_Frame / m_TilesY * m_Size.y);
    frameBounds.w = (Sint16)(m_Size.x);
    frameBounds.h = (Sint16)(m_Size.y);

    return frameBounds;
}

SDL_Rect Entity::NormalizeBounds(const SDL_Rect& rect)
{
    SDL_Rect normalized;
    normalized.x = rect.x - (Sint16)m_Position.x + (Sint16)m_Size.x/2 + GetFrameBounds().x;
    normalized.y = rect.y - (Sint16)m_Position.y + (Sint16)m_Size.y/2 + GetFrameBounds().y;
    normalized.w = rect.w;
    normalized.h = rect.h;

    return normalized;
}

SDL_Rect Entity::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
    int x1 = Maximum(boundsA.x, boundsB.x);
    int y1 = Maximum(boundsA.y, boundsB.y);
    int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
    int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

    int width = x2 - x1;
    int height = y2 - y1;

    if(width > 0 && height > 0) {
        SDL_Rect intersect = {x1, y1, width, height};
        return intersect;
    } else {
        SDL_Rect intersect = {0, 0, 0, 0};
        return intersect;
    }
}

bool Entity::CheckBoxCollision(const Vector2f& pos, const Vector2f& size, const int entId1, const int entId2)
{
	if (entId1 == entId2) return false;
	Entity* entityB = Entity::EntityList[entId2];
	if (INVALID_ID == entId1 && (PICKUP == entityB->m_Type || PLAYER == entityB->m_Type)) return false; // this is a bullet and player || pickup colliding
	if (PICKUP == entityB->m_Type && (PLAYER != Entity::EntityList[entId1]->m_Type)) return false; // collide only with player
	SDL_Rect entbox1 = {pos.x, pos.y, size.x, size.y};
    SDL_Rect entbox2 = {entityB->m_Position.x, entityB->m_Position.y, entityB->m_Size.x, entityB->m_Size.y};
    SDL_Rect coll = Intersection(entbox1, entbox2);
    if (coll.w != 0 || coll.h != 0) return true;
	return false;
}

bool Entity::CheckCameraCollision(const Vector2f& pos, const Vector2f& size)
{
	SDL_Rect entbox1 = {pos.x, pos.y, size.x, size.y};
    SDL_Rect coll = Intersection(entbox1, Camera::GameCam.m_Rect);
    if (coll.w != 0 || coll.h != 0) return true;
	return false;
}

bool Entity::CheckCollision(Entity& entityA, Entity& entityB)
{
    SDL_Rect collisionRect = Intersection(entityA.GetBounds(), entityB.GetBounds());

    if(collisionRect.w == 0 && collisionRect.h == 0)
        return false;

    SDL_Rect normalA = entityA.NormalizeBounds(collisionRect);
    SDL_Rect normalB = entityB.NormalizeBounds(collisionRect);

    for(int y = 0; y <= collisionRect.h; y++)
        for(int x = 0; x <= collisionRect.w; x++)
            if(GetAlphaXY(entityA, normalA.x + x, normalA.y + y) && GetAlphaXY(entityB, normalB.x + x, normalB.y + y))
                return true;

    return false;
}

bool Entity::GetAlphaXY(Entity& entity, int x, int y)
{
    int bpp = entity.m_pSurface->format->BytesPerPixel;
    Uint8* p = (Uint8*)entity.m_pSurface->pixels + y * entity.m_pSurface->pitch + x * bpp;
    Uint32 pixelColor;

    switch(bpp) {
    case(1):
        pixelColor = *p;
        break;
    case(2):
        pixelColor = *(Uint16*)p;
        break;
    case(3):
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixelColor = p[0] << 16 | p[1] << 8 | p[2];
        else
            pixelColor = p[0] | p[1] << 8 | p[2] << 16;
        break;
    case(4):
        pixelColor = *(Uint32*)p;
        break;
    }

    Uint8 red, green, blue, alpha;
    SDL_GetRGBA(pixelColor, entity.m_pSurface->format, &red, &green, &blue, &alpha);

    return alpha > 200;
}
