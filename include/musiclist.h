#pragma once


#include "raylib.h"


typedef struct MusicList
{
    int length;
    int capacity;
    Music* list;
    char** names;
} MusicList;


MusicList* MusicListLoad(const char* path, char** allowedExtensions, const int allowedExtensionsLength);

void MusicListUnload(MusicList* this);

void MusicListFree(MusicList* this);
