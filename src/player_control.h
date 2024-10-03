#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H
#include "raylib.h"

#define PLAYER_MOVE_RANGE 5
#define TURN_ANGLE 1.5708f

enum animState {NONE,FORWARD,TURN};

void checkTurn(Camera3D *camera,float targetTime, float *currentTime,enum animState *animState,float *oldAngle,bool gauche, float *rotateSum);
void checkForward(Camera3D *camera,float targetTime, float *currentTime,enum animState *animState,float *oldPosition, float *positionSum);

#endif
