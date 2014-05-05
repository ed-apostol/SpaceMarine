/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "vector2f.h"

#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

// TODO: transfer to classes

const int SCR_WIDTH = 1024;
const int SCR_HEIGHT = 768;
const int SCR_BPP = 32;
const int LVL_WIDTH = SCR_WIDTH*3;
const int LVL_HEIGHT = SCR_HEIGHT*3;
const float FRAME_RATE = 60.f;
const int NUM_ENEMIES = 500;
const int NUM_STATIC = 20;
const int NUM_PICKUPS = 20;
const int CELLSIZE = 128;
const int INVALID_ID = -1;
const double PI = 3.14159265358979;

enum MoveFlag {
    MOVE_LEFT = 1,
    MOVE_UP = 2,
    MOVE_RIGHT = 4,
    MOVE_DOWN = 8
};

enum EntityType {
    PLAYER = 0,
	ENEMY,
	BULLET,
	STATIC,
	PICKUP
};

const int MinimumFireTimeInterval = 70;
const float FireTimeInterval = 150.f; // adjust, fine-tune
const int EnemyMovementTries = 2; // adjust, fine tune, affects FPS
const float EnemyAttackTimeInterval = 500.f; // adjust, fine-tune

const Vector2f MovementSpeedVector = Vector2f(160, 160);
const Vector2f BulletSpeedVector = MovementSpeedVector * 3; // adjust, fine-tune
const Vector2f MoveUpVectMul = Vector2f(0.0, -1.0);
const Vector2f MoveDownVectMul = Vector2f(0.0, 1.0);
const Vector2f MoveLeftVectMul = Vector2f(-1.0, 0.0);
const Vector2f MoveRightVectMul = Vector2f(1.0, 0.0);


