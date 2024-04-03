#ifndef _STRUCT_H_
#define _STRUCT_H_	

#include<string>
using namespace std;

#define BOARDLENGTH 9
#define BOARDHEIGHT 5

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

struct position {
	int x, y;
};

struct player {
	string name = "";
	int point, life;
};

struct POKEMON
{
	char data = 0;
	int colorWord = 0;
	int colorConsole = 0;
	bool isSelected = false;
};

#endif