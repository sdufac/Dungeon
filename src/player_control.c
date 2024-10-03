#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include "player_control.h"

void checkTurn(Camera3D *camera,float targetTime, float *currentTime,enum animState *animState,float *oldAngle,bool gauche, float *rotateSum){
    if(*currentTime<targetTime){
        *animState = TURN;

        *currentTime = *currentTime+GetFrameTime();

        //Percentage of anim completion
        float t = *currentTime / targetTime;

        //Turn anim
        //Calculation of the next angle of rotation
        float newAngle = Lerp(0,TURN_ANGLE,t);
        float deltaAngle = newAngle - *oldAngle;
        *oldAngle = newAngle;
        CameraYaw(camera,deltaAngle * (gauche ? 1 : -1),false);
        
        *rotateSum = *rotateSum + deltaAngle;

        //End of animation
        if(*currentTime>=targetTime){
            CameraYaw(camera,(TURN_ANGLE - *rotateSum) * (gauche ? 1 : -1),false);
            camera->target.x=roundf(camera->target.x);
            camera->target.y=roundf(camera->target.y);
            camera->target.z=roundf(camera->target.z);
        }    
        
    }else if(*animState == TURN){
        *oldAngle=0;
        *rotateSum = 0;

        *animState = NONE;
    }
}
void checkForward(Camera3D *camera,float targetTime, float *currentTime,enum animState* animState,float *oldPosition, float *positionSum){
    if(*currentTime < targetTime){
        *animState = FORWARD;

        *currentTime = *currentTime+GetFrameTime();

        //Percentage of anim completion
        float t = *currentTime / targetTime;
        float newCoord = Lerp(0,PLAYER_MOVE_RANGE,t);
        float deltaCoord = newCoord - *oldPosition;
        *oldPosition = newCoord;

        *positionSum = *positionSum + deltaCoord;

        CameraMoveForward(camera,deltaCoord,false);
        
        //End of animation
        if(*currentTime>=targetTime){
            CameraMoveForward(camera,(PLAYER_MOVE_RANGE - *positionSum),false);
            camera->position.x=roundf(camera->position.x);
            camera->position.y=roundf(camera->position.y);
            camera->position.z=roundf(camera->position.z);
        } 
    }
    else if(*animState == FORWARD){
        *oldPosition = 0;
        *positionSum = 0;

        *animState = NONE;
    }
}
