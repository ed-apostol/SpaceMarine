/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "vector2f.h"
#include "spm_defines.h"
#include "spm_entity.h"
#include "spm_collision.h"
#include <vector>

Collision Collision::CollManager;

Collision::Collision()
{
    m_CellSize = CELLSIZE;
    m_X = (LVL_WIDTH / CELLSIZE) + 1; // just add one always
    m_Y = (LVL_HEIGHT / CELLSIZE) + 1; // just add one always
    m_pCollisionA = new CollEntry[m_X * m_Y]; /// reserve enough entries
}

Collision::~Collision()
{
    delete[] m_pCollisionA;
}

void Collision::Add(const Vector2f& pos, const Vector2f& size, const int entID)
{
    int x1 = pos.x / m_CellSize;
    int x2 = Minimum(LVL_WIDTH, (pos.x + size.x)) / m_CellSize;
    int y1 = pos.y / m_CellSize;
    int y2 = Minimum(LVL_HEIGHT, (pos.y + size.y)) / m_CellSize;

    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            AddToBucket(x, y, entID);
        }
    }
}

void Collision::AddToBucket(int x, int y, int entID)
{
    m_pCollisionA[GetIdx(x, y)].push_back(entID);
}

void Collision::Remove(const Vector2f& pos, const Vector2f& size, const int entID)
{
    int x1 = pos.x / m_CellSize;
    int x2 = Minimum(LVL_WIDTH, (pos.x + size.x)) / m_CellSize;
    int y1 = pos.y / m_CellSize;
    int y2 = Minimum(LVL_HEIGHT, (pos.y + size.y)) / m_CellSize;

    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            RemoveFromBucket(x, y, entID);
        }
    }
}

void Collision::RemoveFromBucket(int x, int y, const int entID)
{
    const int key = GetIdx(x, y);
    if (m_pCollisionA[key].size() == 0) return;
    for (int Idx = 0; Idx < m_pCollisionA[key].size(); ++Idx) {
        if (entID == m_pCollisionA[key][Idx]) {
            m_pCollisionA[key].erase(m_pCollisionA[key].begin()+Idx);
            break;
        }
    }
}

bool Collision::IsCollided(const Vector2f& pos, const Vector2f& size, const int entID, int* outEntID) 
{
    int x1 = pos.x / m_CellSize;
    int x2 = Minimum(LVL_WIDTH, (pos.x + size.x)) / m_CellSize;
    int y1 = pos.y / m_CellSize;
    int y2 = Minimum(LVL_HEIGHT, (pos.y + size.y)) / m_CellSize;

    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            const int key = GetIdx(x, y);
            for (int Idx = 0; Idx < m_pCollisionA[key].size(); ++Idx) {
				if (Entity::CheckBoxCollision(pos, size, entID,  m_pCollisionA[key][Idx])) {
					if (NULL != outEntID) *outEntID = m_pCollisionA[key][Idx];
					return true;
				}
            }
        }
    }
    return false;
}

int Collision::GetIdx(int x, int y) const
{
    return ((y * m_X) + x);
}



