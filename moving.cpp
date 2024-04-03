#include "moving.h"

// Di chuyển con trỏ đến vị trí (x, y) trên màn hình console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Ẩn con trỏ trên màn hình console
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Lấy thông tin con trỏ
    cursorInfo.bVisible = FALSE; // Ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Thiết lập lại thông tin con trỏ
}

// Đặt màu ở vị trí quanh con trỏ
// Lưu trữ màu ban đầu của từng ô trong vùng 7x3
WORD originalColors[7][3];

void setColorForRegionAroundCursor(int cursorX, int cursorY, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Tính toán vùng 7x3 quanh con trỏ
    int startX = max(cursorX - 3, 0);
    int startY = max(cursorY - 1, 0);
    int endX = min(cursorX + 3, 200); // Giới hạn tối đa ở cột 79
    int endY = min(cursorY + 1, 50); // Giới hạn tối đa ở hàng 24

    // Lưu trữ màu ban đầu của từng ô trong vùng 7x3
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole, &info);
            originalColors[x - startX][y - startY] = info.wAttributes & 0xFF; // Lấy chỉ màu của từng ô
        }
    }

    // Thiết lập màu sắc cho vùng 7x3
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
            SetConsoleCursorPosition(hConsole, coord);
            DWORD written;
            FillConsoleOutputAttribute(hConsole, color, 1, coord, &written);
        }
    }

    // Di chuyển con trỏ về vị trí ban đầu
    COORD originalCoord = { static_cast<SHORT>(cursorX), static_cast<SHORT>(cursorY) };
    SetConsoleCursorPosition(hConsole, originalCoord);
}

// Tái tạo lại ô bị thay đổi
void regenerative(POKEMON** content, int x, int y, int i, int j)
{
    if (content[i][j].data != 0)
    {
        x -= 4; y -= 2;
        createBox(content[i][j].data, x, y);
    }
    if (content[i][j].isSelected == true)
    {
        createBox(content[i][j].data, x, y);
        setColorForRegionAroundCursor(x + 4, y + 2, 0x2F);
    }
    if(content[i][j].data == 0)
    {
        x -= 4; y -= 2;
        createBox(0, x, y);
    }
}
// Hàm di chuyển chính
void moveCursor(POKEMON** content, int length, int height) {
    // Xóa màn hình
    //system("cls");

    // Set up lại độ lớn phạm vi di chuyển của con trỏ
    ++length;
    ++height;

    // Đặt vị trí biến
    int i = 1, j = 1;
    int x1 = 1, x2 = 1, y1 = 1, y2 = 1; // biến tạm thời

    // Đặt vị trí con trỏ chuột
    int currentX1, currentY1, currentX2, currentY2;

    // Vị trí ban đầu của con trỏ    
    int x = 13, y = 7;
    gotoxy(x, y);

    // Đặt cờ
    bool flagX = true; // Cờ ấn chọn
    bool flagColor = false; // Cờ màu

    //Đặt màu ở vị trí đầu tiên
    setColorForRegionAroundCursor(x, y, 0xF0);

    // Ẩn con trỏ
    hideCursor();

    // Vòng lặp chính để điều khiển con trỏ
    while (true) {
        // Xử lý phím nhấn
        char ch = _getch();
        

        if (ch == 'q' || ch == 'Q') {
            // Thoát khỏi vòng lặp nếu người dùng nhấn 'Q'
            system("cls");
            break;
        }
        else if (ch == KEY_UP && y > 10) {
            // Phím mũi tên lên
            regenerative(content, x, y, i, j);
            y = y - 5;
            --i;
            gotoxy(x, y);
        }
        else if (ch == KEY_DOWN && y < (4 * height + 1)) {
            // Phím mũi tên xuống
            regenerative(content, x, y, i, j);
            flagColor = false;
            y = y + 5;
            ++i;
            gotoxy(x, y);
        }
        else if (ch == KEY_LEFT && x > 20) {
            // Phím mũi tên trái
            regenerative(content, x, y, i, j);
            x = x - 9;
            --j;
            gotoxy(x, y);
        }
        else if (ch == KEY_RIGHT && x < (8 * length + 1)) {
            // Phím mũi tên phải
            regenerative(content, x, y, i, j);
            x = x + 9;
            ++j;
            gotoxy(x, y);
        }
        // Đổi màu cho vị trí xung quanh 3x3 của con trỏ
        setColorForRegionAroundCursor(x, y, 0xF0);
        if (ch == 'b')
        {
            clearBox(x, y);
            content[i][j].data = 0;

        }
        if (ch == 'x')
        {
            if (flagX == true)
            {
                x1 = i; y1 = j;
                currentX1 = x;
                currentY1 = y;
                setColorForRegionAroundCursor(x, y, 0x2F);    // Set màu nền xanh và màu chữ trắng            
                content[x1][y1].isSelected = true;
                flagColor = true;
                flagX = false;
            }
            else
            {
                x2 = i; y2 = j;
                currentX2 = x;
                currentY2 = y;
                setColorForRegionAroundCursor(x, y, 0x2F);     // Set màu nền xanh và màu chữ trắng
                content[x2][y2].isSelected = true;
                flagColor = true;
                flagX = true;
            }
            if (flagX == true /*&& (content[x1][y1].data == content[x2][y2].data)*/)
            {
                if (checkI(content, x1, y1, x2, y2) || checkL(content, x1, y1, x2, y2) || checkZ(content, x1, y1, x2, y2))
                {
                    clearBox(currentX1, currentY1);
                    clearBox(currentX2, currentY2);
                    content[x1][y1].data = 0;
                    content[x2][y2].data = 0;                    
                }
                content[x1][y1].isSelected = false;
                content[x2][y2].isSelected = false;
                regenerative(content, currentX1, currentY1, x1, y1);
                regenerative(content, currentX2, currentY2, x2, y2);
            }

        }
        // Đặt lại màu cho vị trí hiện tại của con trỏ
        gotoxy(x, y);
    }
}
