/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "vector2f.h"
#include "spm_defines.h"

class Entity
{
public:
    Entity();
    ~Entity();

    virtual void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
    virtual void HandleInput(SDL_Event event);
    virtual void Update(double m_DeltaTime);
    virtual void Render(SDL_Surface* m_pScreen);
	virtual void TriggerEvent();
    void CheckLevelEdge();
    bool IsRenderable();

    SDL_Rect GetBounds();
    SDL_Rect GetFrameBounds();
    SDL_Rect NormalizeBounds(const SDL_Rect& rect);

    static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);
	static bool CheckBoxCollision(const Vector2f& pos, const Vector2f& size, const int entId1, const int entId2);
	static bool CheckCameraCollision(const Vector2f& pos, const Vector2f& size);
    static bool CheckCollision(Entity& entityA, Entity& entityB);
    static bool GetAlphaXY(Entity& entity, int x, int y);

    Vector2f m_Position;
    Vector2f m_Size;
    Vector2f m_Velocity;
    Vector2f m_Speed;
	bool m_Active;
	bool m_DoRespawn;

    SDL_Surface* m_pSurface;

    int m_EntId;
    int m_TilesX;
    int m_TilesY;
    Uint32 m_MoveFlag;
	EntityType m_Type;
	int m_Hp;

    int m_Frame;
    int m_FrameCount;
    double m_FrameInterval;
    double m_FrameTimeRemaining;

    static std::vector<Entity*> EntityList;
};
