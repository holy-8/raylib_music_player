@echo off
if not exist "build/" mkdir "build/"
gcc -o build/game.exe src/main.c src/helpers.c src/musiclist.c -I include -L lib -lraylib -lgdi32 -lwinmm -Wl,--subsystem,windows
echo build finished
