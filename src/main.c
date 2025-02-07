#include "raylib.h"
#include "map_manager.h"

#include "animation.h"

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 360;

    InitWindow(screenWidth, screenHeight, "Kamikaze");

    Vector2 playerPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    Texture2D texture = LoadTexture("../resources/characters/knight/knight-0.png");
    //AnimationPushFrame("knight", "melee2_0_019,knight-0,1,786,62,98,5,60");
    Ani
    SetTargetFPS(60);
    if(!MapParser(0)){
        TraceLog(LOG_ERROR, "Map Loader Error");
    }
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) playerPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += 2.0f;
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleV(playerPosition, (Vector2){25, 25}, MAROON);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}