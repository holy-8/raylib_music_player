#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "raylib.h"


typedef struct MusicList
{
    int length;
    int capacity;
    Music* list;
    char** names;
} MusicList;


void MusicListIncreaseCapacity(MusicList* this, bool initialize)
{
    if (initialize)
    {
        this->list = malloc(sizeof(Music) * this->capacity);
        this->names = malloc(sizeof(char*) * this->capacity);
    }
    else
    {
        this->capacity = round(this->capacity * 1.5);
        this->list = realloc(this->list, sizeof(Music) * this->capacity);
        this->names = realloc(this->names, sizeof(char*) * this->capacity);
    }
}

MusicList* MusicListLoad(const char* path, char** allowedExtensions, const int allowedExtensionsLength)
{
    MusicList* this = malloc(sizeof(MusicList));
    this->length = 0;
    this->capacity = 4;
    this->list = NULL;
    this->names = NULL;

    if (!DirectoryExists(path))
        return this;

    FilePathList files = LoadDirectoryFiles(path);

    MusicListIncreaseCapacity(this, true);

    for (int curFile = 0; curFile < files.count; curFile++)
    {
        if (this->length >= this->capacity)
            MusicListIncreaseCapacity(this, false);

        for (int curExtension = 0; curExtension < allowedExtensionsLength; curExtension++)
        {
            if (IsFileExtension(files.paths[curFile], allowedExtensions[curExtension]))
                goto validExtension;
        }

        continue;

        validExtension:
            Music curMusicStream = LoadMusicStream(files.paths[curFile]);
            if (IsMusicValid(curMusicStream))
            {
                this->list[this->length] = curMusicStream;
                this->names[this->length] = malloc(strlen(files.paths[curFile]) + 1);
                strcpy(this->names[this->length], GetFileNameWithoutExt(files.paths[curFile]));
                this->length++;
            }
            else
            {
                UnloadMusicStream(curMusicStream);
            }
    }

    return this;
}

void MusicListUnload(MusicList* this)
{
    for (int curMusic = 0; curMusic < this->length; curMusic++)
    {
        UnloadMusicStream(this->list[curMusic]);
    }
}

void MusicListFree(MusicList* this)
{
    for (int curName = 0; curName < this->length; curName++)
    {
        free(this->names[curName]);
    }

    free(this->names);
    free(this->list);
    free(this);
}
