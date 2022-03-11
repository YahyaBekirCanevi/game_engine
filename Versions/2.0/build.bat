@echo off
g++ *.cpp glew.c -o game.exe --static -Wall -DGLEW_STATIC -L libglfw3.lib  -L libglew32.lib -L libglew32mx.lib -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32 -lglew32mx
