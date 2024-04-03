#include "matching.h"

// Ki?m tra I matching
bool checkI(POKEMON** content, int x1, int y1, int x2, int y2) {
	// Hai ô không th? gi?ng nhau
	if (x1 == x2 && y1 == y2) return false;

	// Ki?m tra hai ô có gi?ng nhau không
	if ((abs(x1 - x2) == 1 && y1 == y2) || (x1 == x2 && abs(y1 - y2) == 1)) return true;

	// Tr??ng h?p hai ô n?m trên cùng m?t hàng
	if (y1 == y2) {
		int startX = min(x1, x2) + 1;
		int endX = max(x1, x2);
		for (int i = startX; i < endX; ++i) {
			if (content[i][y1].data != 0) return false; // Ki?m tra xem có ô tr?ng n?m gi?a chúng không
		}
		return true;
	}

	// Tr??ng h?p hai ô n?m trên cùng m?t c?t
	if (x1 == x2) {
		int startY = min(y1, y2) + 1;
		int endY = max(y1, y2);
		for (int i = startY; i < endY; ++i) {
			if (content[x1][i].data != 0) return false; // Ki?m tra xem có ô tr?ng n?m gi?a chúng không
		}
		return true;
	}

	return false;
}
// Ki?m tra L matching
bool checkL(POKEMON** content, int x1, int y1, int x2, int y2)
{
	// Hai ô không th? t?o L matching
	if (x1 == x2 && y1 == y2) return false;

	// Ki?m tra xem có th? t?o L matching t? hai ô ???c ch?n
	if (checkI(content, x1, y1, x2, y1) && checkI(content, x2, y2, x2, y1) && content[x2][y1].data == 0)
		return true;
	if (checkI(content, x1, y1, x1, y2) && checkI(content, x2, y2, x1, y2) && content[x1][y2].data == 0)
		return true;

	return false;
}
// Ki?m tra Z matching
bool checkZ(POKEMON** content, int x1, int y1, int x2, int y2)
{
	// Ki?m tra hai ô không trùng nhau
	if (x1 == x2 && y1 == y2) return false;

	// Ki?m tra xiên xu?ng
	/*
	  x
		x
		  x
	*/
	if ((x1 > x2 && y1 > y2) || (x1 < x2 && y1 < y2))
	{
		int tempx1 = min(x1, x2), tempx2 = max(x1, x2), tempy1 = min(y1, y2), tempy2 = max(y1, y2);
		// Ki?m tra Z ??ng
		for (int i = tempx1 + 1; i < tempx2; ++i)
		{
			if (checkL(content, tempx1, tempy1, i, tempy2) && checkL(content, i, tempy1, tempx2, tempy2))
				return true;
		}
		// Ki?m tra Z ngang
		for (int i = tempy1 + 1; i < tempy2; ++i)
		{
			if (checkL(content, tempx1, tempy1, tempx2, i) && checkL(content, tempx1, i, tempx2, tempy2))
				return true;
		}
	}
	// Ki?m tra xiên lên
	/*
		  x
		x
	  x
	*/
	if ((x1 > x2 && y1 < y2) || (x1<x2 && y1 > y2))
	{
		int tempx1 = min(x1, x2), tempx2 = max(x1, x2), tempy1 = max(y1, y2), tempy2 = min(y1, y2);
		// Ki?m tra Z ??ng
		for (int i = tempx1 + 1; i < tempx2; ++i)
		{
			if (checkL(content, tempx1, tempy1, i, tempy2) && checkL(content, i, tempy1, tempx2, tempy2))
				return true;
		}
		// Ki?m tr Z ngang
		for (int i = tempy2 + 1; i < tempy1; ++i)
		{
			if (checkL(content, tempx1, tempy1, tempx2, i) && checkL(content, tempx1, i, tempx2, tempy2))
				return true;
		}
	}
	return false;
}
// Ki?m tra U matching
//bool checkU(POKEMON** content, int x1, int y1, int x2, int y2)
