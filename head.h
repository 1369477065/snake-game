#pragma once
#define _CRT_SECURE_NO_WARNINGS

#undef _UNICODE
#undef UNICODE

#include<stdio.h>
#include<graphics.h>
#include<easyx.h>
#include<time.h>
#include<stdlib.h>

char get_first(void);
char get_choice(void);
int get_velocity(void);
bool havewall(void);
void GameInit(void);
void GameDraw(void);
void SnakeMove(bool);
void GetKeyState(void);
void EatFood(void);
void DontEatSelf(void);
void GameOver(void);

#define WIN_WIDTH 500
#define WIN_HEIGHT 300
#define MAX_SNAKE 100