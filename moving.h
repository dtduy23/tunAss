#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include "board.h"
#include "matching.h"
void gotoxy(int x, int y);
void hideCursor();
void moveCursor(POKEMON** content, int length, int height);
void setColorForRegionAroundCursor(int cursorX, int cursorY, int color);
void regenerative(POKEMON** content, int x, int y, int i, int j);