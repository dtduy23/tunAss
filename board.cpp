#include "board.h"
// Di chuyển con trỏ đến vị trí (x, y) trên màn hình console
void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, coord);
}
// Tạo nội dung mảng 2 chiều
POKEMON** createContent(int length, int height)
{
    // Tạo theo độ khó
    length += 2;
    height += 2;
    // Tạo seed
    std::srand(std::time(nullptr));

    // Tạo mảng content
    POKEMON** content = new POKEMON* [height];
    for (int i = 0; i < height; ++i)
    {
        content[i] = new POKEMON[length];
    }

    // Tạo nội dung
    int size = (length - 2) * (height - 2);
    char* a = new char[size];
    int* c = new int[size];
    for (int i = 0; i < size; ++i)
    {
        a[i] = 'A' + i % 15;// Sử dụng % để đảm bảo giá trị không vượt quá 15 ký tự
        a[i + 1] = a[i];
        c[i] = int(a[i] - 'A') % 7 + 31;
        c[i + 1] = c[i];
        ++i;
    }
    for (int i = 0; i < size; ++i)
    {
        int pos = rand() % size;
        std::swap(a[i], a[pos]);
        std::swap(c[i], c[pos]);
    }

    // Đặt nội dung vào bên trong viền
    int k = 0;
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < length - 1; ++j)
        {
            content[i][j].data = a[k];
            content[i][j].colorWord = c[k];
            ++k;
        }
    }
    delete[] a;
    return content;
}
// Hàm in ra màn hình ký tự với màu đã chỉ định
void printColor(char s) {
    int color = int(s - 'A') % 7 + 31;
    std::cout << "\033[" << color << "m" << s << "\033[0m";
}
// Tạo box dựa trên vị trí chỉ định
void createBox(char s, int x, int y)
{
    if (s != 0)
    {
        setCursorPosition(x, y);
        std::cout << " ------- ";
        setCursorPosition(x, y + 1); // đưa con trỏ xuống vị trí đầu hàng 2 của box
        std::cout << "|       |";
        setCursorPosition(x, y + 2);// đưa con trỏ xuống vị trí đầu hàng 3 của box
        std::cout << "|   ";
        printColor(s);
        std::cout << "   |";
        setCursorPosition(x, y + 3);// đưa con trỏ xuống vị trí đầu hàng 4 của box
        std::cout << "|       |";
        setCursorPosition(x, y + 4);// đưa con trỏ xuống vị trí đầu hàng 5 của box
        std::cout << " ------- ";
    }
    else
    {
        setCursorPosition(x, y);
        std::cout << "         ";
        setCursorPosition(x, y + 1); // đưa con trỏ xuống vị trí đầu hàng 2 của box
        std::cout << "         ";
        setCursorPosition(x, y + 2);// đưa con trỏ xuống vị trí đầu hàng 3 của box
        std::cout << "         ";
        setCursorPosition(x, y + 3);// đưa con trỏ xuống vị trí đầu hàng 4 của box
        std::cout << "         ";
        setCursorPosition(x, y + 4);// đưa con trỏ xuống vị trí đầu hàng 5 của box
        std::cout << "         ";
    }

}
// Xóa box dựa trên tọa độ x,y
void clearBox(int x, int y)
{
    x -= 4; y -= 2;
    setCursorPosition(x, y);
    std::cout << "         ";
    setCursorPosition(x, y + 1); // đưa con trỏ xuống vị trí đầu hàng 2 của box
    std::cout << "         ";
    setCursorPosition(x, y + 2);// đưa con trỏ xuống vị trí đầu hàng 3 của box
    std::cout << "         ";
    setCursorPosition(x, y + 3);// đưa con trỏ xuống vị trí đầu hàng 4 của box
    std::cout << "         ";
    setCursorPosition(x, y + 4);// đưa con trỏ xuống vị trí đầu hàng 5 của box
    std::cout << "         ";
}
// Tạo box dựa trên độ dài và chiều cao
void createBoard(POKEMON** content, int length, int height)
{
    int boxWidth = 9; // Chiều rộng của mỗi ô box
    int boxHeight = 5; // Chiều cao của mỗi ô box
    length += 2;
    height += 2;
    // Duyệt qua từng ô trong ma trận
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            // Tính toạ độ của ô box hiện tại
            int x = j * boxWidth;
            int y = i * boxHeight;

            // Tạo ô box cho phần nội dung
            createBox(content[i][j].data, x, y);
        }
    }
}
