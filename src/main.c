#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"
#include "map_manager.h"
#include "animation.h"
#include "timer.h"
#include "animator.h"

void TimerTestPrintOneTime(void* data)
{
    TraceLog(LOG_INFO, "one time timer");
}

void TimerTestPrintRepeat(void* data)
{
    int numberTest = -1;
    if(data != NULL)
    {
        numberTest = *(int*)data;
        *(int*)data += 1;
    }
    TraceLog(LOG_INFO, "forever timer %d", numberTest);
}

void TimerTestPrintTimes(void* data)
{
    TraceLog(LOG_INFO, "times timer");
}

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Kamikaze");

    Vector2 playerPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    Camera2D camera = { 0 };
    camera.offset = (Vector2){600, 400};
    camera.target = (Vector2){300, 200};
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    //timer tests
SetTraceLogLevel(LOG_DEBUG);
    TimerInit();
    AnimationInit();
    Animator3D animator;
    const DatabaseRecord3DAnimation* data = AnimationGetCharacterData("knight");
    Animator3DCreate(&animator, data, EAST);
    int animIndex = 0;
    Animator3DSetAnimation(&animator, animIndex);


    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) playerPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += 2.0f;

        //timer tests
        int tickMs = (int)(GetFrameTime() * 1000);
        TimerTicks(tickMs);
        if(IsKeyPressed(KEY_P))
        {
            TimerPauseSet(!TimerGetPauseState());
        }
        if(IsKeyPressed(KEY_M))
        {
            DIRECTION dir = (animator.direction + 1) % 8;
            Animator3DDirectionSet(&animator, dir);
        }
        if(IsKeyPressed(KEY_N))
        {
            if(animator.isRunning) Animator3DStop(&animator);
            else Animator3DStart(&animator);

        }
        if(IsKeyPressed(KEY_K))
        {
            animIndex++;
            if(animIndex >= animator.animations->animationsCount) animIndex = 0;
            Animator3DSetAnimation(&animator, animIndex);
        }
        else if(IsKeyPressed(KEY_J))
        {
            animIndex--;
            if(animIndex < 0) animIndex = animator.animations->animationsCount - 1;
            Animator3DSetAnimation(&animator, animIndex);
        }
        BeginDrawing();

            ClearBackground(DARKGREEN);
            BeginMode2D(camera);
            Animator3DDraw(&animator, 100.0f, 100.0f);
            DrawCircle(100, 100, 3, RED);
            const char* animName = animator.currentAnimation->data.name;
            char* animType;
            if(animator.sharedData->animationType == ANIM_TYPE_LOOP) animType = "loop";
            else if(animator.sharedData->animationType == ANIM_TYPE_SINGLE) animType = "single";
            else if(animator.sharedData->animationType == ANIM_TYPE_PINGPONG) animType = "ping-pong";
            else animType = "NOT DEFINED";
            DrawText(animName, 130, 80, 10, WHITE);
            DrawText(animType, 130, 90, 10, WHITE);
            char buffer[16];
            sprintf(buffer, "%d", animator.data.currentFrame);
            DrawText(buffer, 180, 90, 10, WHITE);

            DrawText(animator.currentAnimation->dirAnimations[EAST].frames[animator.data.currentFrame].sprite.name, 130, 100, 10, WHITE);
            DrawRectangleV(playerPosition, (Vector2){25, 25}, MAROON);
            EndMode2D();
        EndDrawing();
    }


    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
