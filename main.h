// main.h
// MazeGame

// Created by Yannis Panagis
// header file to contain global variables for the game

#include <iostream>
#include <unistd.h>

#ifndef MazeGame_main_h
#define MazeGame_main_h

extern int posX;
extern int posY;

extern int exitPosX;
extern int exitPosY;

extern int enemy1PosX;
extern int enemy1PosY;

extern int enemy2PosX;
extern int enemy2PosY;

extern int enemy3PosX;
extern int enemy3PosY;

extern int prevX;
extern int prevY;

extern int tokens;

extern bool goblinDead;
extern bool caveTrollDead;
extern bool orcDead;
extern bool playerDead;

extern bool gameOver;
extern bool firstGame;

#endif
