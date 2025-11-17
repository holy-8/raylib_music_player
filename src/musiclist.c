#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "raylib.h"


typedef struct MusicList
{
    int length;
    Music* list;
    char** names;
} MusicList;


MusicList* MusicListLoad(const char* path)
{
    MusicList* this = malloc(sizeof(MusicList));

    if (!DirectoryExists(path))
    {
        this->length = 0;
        this->list = NULL;
        this->names = NULL;
        return this;
    }

    FilePathList files = LoadDirectoryFiles(path);

    this->length = files.count;
    this->list = malloc(sizeof(Music) * files.count);
    this->names = malloc(sizeof(char*) * files.count);

    for (int curFile = 0; curFile < files.count; curFile++)
    {
        this->list[curFile] = LoadMusicStream(files.paths[curFile]);
        this->names[curFile] = malloc(strlen(files.paths[curFile]) + 1);
        strcpy(this->names[curFile], GetFileNameWithoutExt(files.paths[curFile]));
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
