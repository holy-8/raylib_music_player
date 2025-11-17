#include <stdio.h>
#include "raylib.h"
#include "musiclist.h"
#include "helpers.h"


void MusicPlayeScene(MusicList* musicList)
{
    int currentTrack = 0;

    bool pause = false;
    bool startPlaying = true;

    float currentDuration = 0;
    float currentPosition = 0;
    float timePlayed = 0.0f;

    char* currentTrackName;
    char currentTrackDurationText[256];

    while (!WindowShouldClose())
    {
        if (startPlaying)
        {
            startPlaying = !startPlaying;
            PlayMusicStream(musicList->list[currentTrack]);
        }

        UpdateMusicStream(musicList->list[currentTrack]);

        currentDuration = GetMusicTimeLength(musicList->list[currentTrack]);
        currentPosition = GetMusicTimePlayed(musicList->list[currentTrack]);

        timePlayed = currentPosition / currentDuration;

        if (timePlayed >= 0.999f)
        {
            StopMusicStream(musicList->list[currentTrack]);
            currentTrack = limit_value(currentTrack + 1, musicList->length - 1, 0);
            startPlaying = true;
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            StopMusicStream(musicList->list[currentTrack]);
            currentTrack = limit_value(currentTrack + 1, musicList->length - 1, 0);
            startPlaying = true;
        }
        else if (IsKeyPressed(KEY_LEFT))
        {
            StopMusicStream(musicList->list[currentTrack]);
            currentTrack = limit_value(currentTrack - 1, musicList->length - 1, 0);
            startPlaying = true;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            pause = !pause;

            if (pause)
                PauseMusicStream(musicList->list[currentTrack]);
            else
                ResumeMusicStream(musicList->list[currentTrack]);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        currentTrackName = musicList->names[currentTrack];

        sprintf(
            currentTrackDurationText, "%dm. %ds. / %dm. %ds.",
            getMinutes(currentPosition), getSeconds(currentPosition),
            getMinutes(currentDuration), getSeconds(currentDuration)
        );

        DrawText(currentTrackName, 150, 150, 32, LIGHTGRAY);

        DrawRectangle(150, 200, 400, 12, LIGHTGRAY);
        DrawRectangle(150, 200, (int)(timePlayed*400.0f), 12, PINK);
        DrawRectangleLines(148, 198, 404, 16, GRAY);
        DrawText(currentTrackDurationText, 566, 200, 20, LIGHTGRAY);

        DrawText("Press SPACE to pause.", 150, 250, 20, LIGHTGRAY);
        DrawText("Arrow keys to play next/prev track.", 150, 280, 20, LIGHTGRAY);

        EndDrawing();
    }

    MusicListUnload(musicList);
    MusicListFree(musicList);

    CloseAudioDevice();
    CloseWindow();
}

void NoMusicScene(MusicList* musicList)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("There's no music to load! :(", 150, 150, 32, LIGHTGRAY);

        EndDrawing();
    }

    MusicListFree(musicList);

    CloseAudioDevice();
    CloseWindow();
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Music player :3");
    SetWindowIcon(LoadImage("images/img.png"));

    InitAudioDevice();
    SetTargetFPS(60);

    MusicList* musicList = MusicListLoad("music/");

    if (musicList->length <= 0)
        NoMusicScene(musicList);
    else
        MusicPlayeScene(musicList);

    return 0;
}
