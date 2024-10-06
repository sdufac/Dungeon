#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "player_control.h"
#include "npc.h"
#include "stddef.h"

#define MAP_SIZE_X 5
#define MAP_SIZE_Y 5

#define PLAYER_MOVE_RANGE 5
#define TURN_ANGLE 1.5708f

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 540;

    InitWindow(screenWidth, screenHeight, "Dungeon");

    //General anim
    //--------------------------------------------------------------------------------------
    enum animState animState = NONE;

    //Turn anim
    //--------------------------------------------------------------------------------------
    const float turnDuration = 0.3;
    float timeTurnAnim = turnDuration;

    float oldAngle = 0;
    float rotateSum = 0;

    bool gauche = false;

    //Forward anim
    //--------------------------------------------------------------------------------------
    const float forwardDuration = 0.3;
    float timeForwardAnim = forwardDuration; float oldCoord = 0;
    float coordSum = 0;

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 1.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_CUSTOM;

    //Map
    //--------------------------------------------------------------------------------------
    int map[MAP_SIZE_X][MAP_SIZE_Y] = {{1,1,1,2,1}, //1=floor
                                       {1,2,1,2,1}, //2=wall
                                       {1,1,1,2,1}, 
                                       {2,1,1,1,1},
                                       {2,2,1,2,2}};
    //--------------------------------------------------------------------------------------
    AnimData turnData;
    turnData.camera = &camera;
    turnData.targetTime = turnDuration;
    turnData.currentTime = timeTurnAnim;
    turnData.oldValue = oldAngle;
    turnData.sum = rotateSum;

    AnimData forwardData;
    forwardData.camera = &camera;
    forwardData.targetTime = forwardDuration;
    forwardData.currentTime = timeForwardAnim;
    forwardData.oldValue = oldCoord;
    forwardData.sum = coordSum;

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //NPC
    //--------------------------------------------------------------------------------------
    Npc monoko;
    monoko.spritePath = "img/Monoko.png";
    monoko.texture = LoadTexture(monoko.spritePath); 
    monoko.position = (Vector3){15,((float)monoko.texture.height)/2/100,20};
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advance camera controls, it's reecommended to compute camera movement manually

        monoko.toScreenPosition = GetWorldToScreen(monoko.position, camera);
        //Turn Animation--------------------------------------------------------------------------
        Vector3 nextPosition = Vector3Add(Vector3Scale(GetCameraForward(&camera),PLAYER_MOVE_RANGE),camera.position);
        int checkX = nextPosition.x / PLAYER_MOVE_RANGE;
        int checkZ = nextPosition.z / PLAYER_MOVE_RANGE;
        
        if(IsKeyDown(KEY_UP) && animState == NONE){
            if((checkX >= 0 && checkX <=MAP_SIZE_X - 1) && (checkZ >= 0 && checkZ <=MAP_SIZE_Y - 1)){
                if(map[checkX][checkZ] == 1){
                    forwardData.currentTime = 0;
                }
            }
        }
        else if(IsKeyDown(KEY_LEFT) && animState == NONE){
            turnData.currentTime = 0;
            gauche = true;
        }
        else if(IsKeyDown(KEY_RIGHT) && animState == NONE){
            turnData.currentTime = 0;
            gauche = false;
        }

        checkTurn(&turnData,&animState,gauche); 
        checkForward(&forwardData,&animState);


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                for(int i = 0; i< MAP_SIZE_X; i++){
                    for (int j =0; j< MAP_SIZE_Y; j++){
                        if(map[i][j]==1){
                            Vector3 floorPosition = { (i*PLAYER_MOVE_RANGE) , 0.0f, (j*PLAYER_MOVE_RANGE) };
                            Vector3 ceilingPosition = { (i*PLAYER_MOVE_RANGE) , PLAYER_MOVE_RANGE, (j*PLAYER_MOVE_RANGE) };

                            DrawPlane(floorPosition, (Vector2){PLAYER_MOVE_RANGE,PLAYER_MOVE_RANGE}, PINK);
                            DrawCubeV(ceilingPosition,(Vector3){PLAYER_MOVE_RANGE,0.1f,PLAYER_MOVE_RANGE},PINK);
                        }
                        else if(map[i][j]==2){ 
                            Vector3 wallSize = {PLAYER_MOVE_RANGE , PLAYER_MOVE_RANGE, PLAYER_MOVE_RANGE};
                            Vector3 wallPosition = {i*PLAYER_MOVE_RANGE, wallSize.y/2, j*PLAYER_MOVE_RANGE};
                            DrawCubeV(wallPosition,wallSize,GRAY);
                        }
                    }
                }

                // Draw player cube
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                    DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
                }
                DrawBillboard(camera,monoko.texture,monoko.position,3.0f,WHITE);

            EndMode3D();

            // Draw info boxes
            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
                                              (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                              (cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                              (cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
            DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                    (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
            DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
            DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);
            DrawText(TextFormat("Monoko %f", monoko.position.y), 610, 105, 10, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
