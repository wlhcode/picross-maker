#ifndef PICROSS_H
#define PICROSS_H

#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <fstream>

const int win_width = 120;
const int win_height = 52;
double win_widthpx;
double win_heightpx;
int curROW=0, curCOL=0;
int makeCNT=0;

using namespace std;

POINT curPOS;
RECT rect;
HWND hwnd;
CONSOLE_FONT_INFOEX cfi;

#endif
