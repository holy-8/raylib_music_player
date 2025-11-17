#pragma once


#include "raylib.h"


typedef struct MusicList
{
    int length;
    Music* list;
    char** names;
} MusicList;


MusicList* MusicListLoad(const char* path);

void MusicListUnload(MusicList* this);

void MusicListFree(MusicList* this);
