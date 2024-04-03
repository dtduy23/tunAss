#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <cstring>
#include "struct.h"
void setCursorPosition(int x, int y); 
POKEMON** createContent(int length, int height);
void createBox(char s, int x, int y);
void clearBox(int x, int y);
void createBoard(POKEMON** content, int length, int height);
void printColor(char s);
