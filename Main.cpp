#include "moving.h"
#include "board.h"
int main() {
    int length = 6;
    int height = 4;
    int hard = 1;
    POKEMON** content = createContent(length, height);
    createBoard(content, length, height);
    moveCursor(content, length, height);
    return 0;
}