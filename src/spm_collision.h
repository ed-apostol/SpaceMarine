/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "vector2f.h"
#include <vector>

typedef std::vector<int> CollEntry;

class Collision
{
public:
    Collision();
    ~Collision();

    void Add(const Vector2f& pos, const Vector2f& size, const int entID);
    void AddToBucket(int x, int y, int entID);
    void Remove(const Vector2f& pos, const Vector2f& size, const int entID);
    void RemoveFromBucket(int x, int y, int entID);
    bool IsCollided(const Vector2f& pos, const Vector2f& size, const int entID, int* outEntID);
    int GetIdx(int x, int y) const;

    static Collision CollManager;
private:
    int m_X;
    int m_Y;
    int m_CellSize;
    CollEntry* m_pCollisionA;
};




