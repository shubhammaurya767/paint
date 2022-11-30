#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;
unordered_map<int, string> colorname;
void drawBox(int x, int y, int size)
{
    setcolor(BLACK);
    double semisize = size / 2;
    rectangle(x - semisize, y - semisize, x + semisize, y + semisize);
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    if (x1 <= x2)
    {
        if (y1 <= y2)
            rectangle(x1, y1, x2, y2);
        else
            rectangle(x1, y2, x2, y1);
    }
    else
    {
        if (y1 <= y2)
            rectangle(x2, y1, x1, y2);
        else
            rectangle(x2, y2, x1, y1);
    }
}

void brushTool(int x, int y, int radius, int color)
{
    int curr_color = getcolor();
    setcolor(color);
    circle(x, y, radius);
    putpixel(x, y, color);
    while (radius >= 0)
        circle(x, y, --radius);
    setcolor(curr_color);
}

void drawfilledSquare(int x, int y, int size, int color)
{
    int curr_color = getcolor();
    setcolor(color);
    int x1 = x - size;
    int x2 = x + size;
    int y1 = y - size;
    int y2 = y + size;
    putpixel((x1 + x2) / 2, (y1 + y2) / 2, color);
    rectangle(x1, y1, x2, y2);
    while (x2 - x1 >= 0 && y2 - y1 >= 0)
        rectangle(++x1, ++y1, --x2, --y2);
    setcolor(curr_color);
}

void decreaseSize(int &size)
{
    if (size <= 1)
        size = 1;
    else
        size--;
    delay(100);
}

void increaseSize(int &size)
{
    size++;
    delay(100);
}
void displaySize(const int &size, const int &width, const int &height)
{
    outtextxy(width + 62, height, (char *)"     ");
    outtextxy(width, height, (char *)"Size: ");
    string s = to_string(size);
    if (size <= 9)
        outtextxy(width + 70, height, &*s.begin());
    else if (size >= 100)
        outtextxy(width + 62, height, &*s.begin());
    else
        outtextxy(width + 66, height, &*s.begin());
}

void displayColor(const int &color, const int &width, const int &height)
{
    outtextxy(width, height, (char *)"                                                                                             ");
    string s = "Color: " + colorname[color];
    outtextxy(width, height, &*s.begin());
}

void displayColorInfo(int width, int height)
{
    int boxsize = 26;
    int xSpacing = boxsize + 10;
    int ySpacing = boxsize + 10;
    int elementsInRow = 4;

    int count = 0;
    int x = width;
    int y = height;

    for (int color = 0; color <= 15; color++)
    {
        if (count % elementsInRow == 0)
        {
            y += ySpacing;
            x = width;
        }
        drawBox(x, y, boxsize);
        setfillstyle(1, color);
        floodfill(x, y, BLACK);
        x += xSpacing;
        count++;
    }
}

void displayShapeInfo(int width, int height)
{
    int gap = 20;
    string l1 = "NUM1:  BRUSH TOOL";
    outtextxy(width, height, &*l1.begin());
    string l2 = "NUM2:  RECTANGLE";
    outtextxy(width, height + gap, &*l2.begin());
    string l3 = "NUM3:  LINE";
    outtextxy(width, height + 2 * gap, &*l3.begin());
    string l4 = "NUM4:  FLOOD FILL";
    outtextxy(width, height + 3 * gap, &*l4.begin());
    string l5 = "NUM5:  CIRCLE";
    outtextxy(width, height + 4 * gap, &*l5.begin());
}
void displaySideBarLine(int width, int height)
{
    int curr_color = getcolor();
    setcolor(BLACK);
    line(width, 0, width, height);
    setcolor(curr_color);
}
void displayClearAll(int width, int height)
{
    drawBox(width + 20, height, 50); // clearall button
    outtextxy(width + 2, height - 8, (char *)"Clear");
    outtextxy(width - 4, height + 30, (char *)"(Space)");
}
void displaySave(int width, int height)
{
    drawBox(width + 90, height, 50); // save button
    outtextxy(width + 72, height - 8, (char *)"Save");
    outtextxy(width + 70, height + 30, (char *)"(Enter)");
}
void preWriitenText(int width, int height, int sidebarWidth, int size, int color)
{
    outtextxy(width / 3, 10, (char *)"***** PAINT APPLICATION - Shubham Maurya - shubhammaurya767@gmail.com *****");
    displaySideBarLine(sidebarWidth - 10, height);
    setfillstyle(1,WHITE);
    floodfill(sidebarWidth + 1, 1, BLACK);
    displaySize(size, sidebarWidth, 20);     // size width height
    displayColor(color, sidebarWidth, 52);   // color width height
    displayColorInfo(sidebarWidth + 18, 60); // display color info: side bar
    displayClearAll(sidebarWidth + 18, 264);
    displaySave(sidebarWidth + 18, 264);

    displayShapeInfo(sidebarWidth, 350); // display shape info: side bar
    drawBox(sidebarWidth + 50, 28, 16);  // minus box
    line(sidebarWidth + 46, 28, sidebarWidth + 54, 28);
    drawBox(sidebarWidth + 100, 28, 16); // plus box
    line(sidebarWidth + 96, 28, sidebarWidth + 104, 28);
    line(sidebarWidth + 100, 24, sidebarWidth + 100, 32);
}
void sidebarOperations(POINT cursorPos, int width, int height, int &size, int &color)
{
    int sidebarWidth = width * 0.9;
    if (cursorPos.y > 20 && cursorPos.y < 36) // size
    {
        delay(50);
        if (cursorPos.x > sidebarWidth + 42 && cursorPos.x < sidebarWidth + 58) // decrease size
            decreaseSize(size);
        if (cursorPos.x > sidebarWidth + 92 && cursorPos.x < sidebarWidth + 108) // increase size
            increaseSize(size);
        displaySize(size, sidebarWidth, 20); // size width height
    }
    else if (cursorPos.y >= 83 && cursorPos.y <= 217) // color pallete heigth
    {
        int x = sidebarWidth + 5;
        int inc = 26;
        int sp = 10;
        if (cursorPos.y >= 83 && cursorPos.y <= 109) // row 1
        {
            if (cursorPos.x >= x && cursorPos.x <= x + inc)
                color = 0;
            else if (cursorPos.x >= x + inc + sp && cursorPos.x <= x + 2 * (inc + sp))
                color = 1;
            else if (cursorPos.x >= x + 2 * (inc + sp) && cursorPos.x <= x + 3 * (inc + sp))
                color = 2;
            else if (cursorPos.x >= x + 3 * (inc + sp) && cursorPos.x <= x + 4 * (inc + sp))
                color = 3;
        }
        else if (cursorPos.y >= 119 && cursorPos.y <= 145)
        {
            if (cursorPos.x >= x && cursorPos.x <= x + inc)
                color = 4;
            else if (cursorPos.x >= x + inc + sp && cursorPos.x <= x + 2 * (inc + sp))
                color = 5;
            else if (cursorPos.x >= x + 2 * (inc + sp) && cursorPos.x <= x + 3 * (inc + sp))
                color = 6;
            else if (cursorPos.x >= x + 3 * (inc + sp) && cursorPos.x <= x + 4 * (inc + sp))
                color = 7;
        }
        else if (cursorPos.y >= 155 && cursorPos.y <= 181)
        {
            if (cursorPos.x >= x && cursorPos.x <= x + inc)
                color = 8;
            else if (cursorPos.x >= x + inc + sp && cursorPos.x <= x + 2 * (inc + sp))
                color = 9;
            else if (cursorPos.x >= x + 2 * (inc + sp) && cursorPos.x <= x + 3 * (inc + sp))
                color = 10;
            else if (cursorPos.x >= x + 3 * (inc + sp) && cursorPos.x <= x + 4 * (inc + sp))
                color = 11;
        }
        else if (cursorPos.y >= 191 && cursorPos.y <= 217)
        {
            if (cursorPos.x >= x && cursorPos.x <= x + inc)
                color = 12;
            else if (cursorPos.x >= x + inc + sp && cursorPos.x <= x + 2 * (inc + sp))
                color = 13;
            else if (cursorPos.x >= x + 2 * (inc + sp) && cursorPos.x <= x + 3 * (inc + sp))
                color = 14;
            else if (cursorPos.x >= x + 3 * (inc + sp) && cursorPos.x <= x + 4 * (inc + sp))
                color = 15;
        }
        displayColor(color, sidebarWidth, 52);
    }
    else if (cursorPos.y >= 239 && cursorPos.y <= 289) // bigbuttons
    {
        if (cursorPos.x >= sidebarWidth + 13 && cursorPos.x <= sidebarWidth + 63) // clear all button
        {
            clearmouseclick(VK_LBUTTON);
            cleardevice();
            preWriitenText(width, height, sidebarWidth, size, BLACK);
            delay(200);
        }
        else if (cursorPos.x >= sidebarWidth + 83 && cursorPos.x <= sidebarWidth + 133) // save button
        {
            clearmouseclick(VK_LBUTTON);
            writeimagefile("img.jpeg");
            cleardevice();
            preWriitenText(width, height, sidebarWidth, size, BLACK);
            delay(200);
        }
    }
}
void storecolornames()
{
    colorname.insert({0, "BLACK"});
    colorname.insert({1, "BLUE"});
    colorname.insert({2, "GREEN"});
    colorname.insert({3, "CYAN"});
    colorname.insert({4, "RED"});
    colorname.insert({5, "MAGENTA"});
    colorname.insert({6, "BROWN"});
    colorname.insert({7, "LIGHTGRAY"});
    colorname.insert({8, "DARKGRAY"});
    colorname.insert({9, "LIGHTBLUE"});
    colorname.insert({10, "LIGHTGREEN"});
    colorname.insert({11, "LIGHTCYAN"});
    colorname.insert({12, "LIGHTRED"});
    colorname.insert({13, "LIGHTMAGENTA"});
    colorname.insert({14, "YELLOW"});
    colorname.insert({15, "WHITE"});
}

int main()
{
    int height = GetSystemMetrics(SM_CYSCREEN);
    int width = GetSystemMetrics(SM_CXSCREEN);
    initwindow(width, height, "", -3, -3);
    floodfill(width / 2, height / 2, WHITE);
    int sidebarWidth = 0.9 * width;
    storecolornames();
    int color = 0;
    circle(sidebarWidth + 10, height / 2, RED);
    floodfill(sidebarWidth + 10, height / 2, RED);
    setcolor(BLACK);
    setbkcolor(WHITE);
    POINT cursorPos;
    int size = 15;
    int choice = 1;
    preWriitenText(width, height, sidebarWidth, size, color);

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (1)
    {
        int curr_color = getcolor();
        GetCursorPos(&cursorPos);
        if (GetAsyncKeyState(VK_ADD))
        {
            increaseSize(size);
            displaySize(size, 0.9 * width, 20); // size width height
        }
        if (GetAsyncKeyState(VK_SUBTRACT))
        {
            decreaseSize(size);
            displaySize(size, 0.9 * width, 20); // size width height
        }
        if (GetAsyncKeyState(VK_NUMPAD1))
        {
            choice = 1;
        }
        else if (GetAsyncKeyState(VK_NUMPAD2))
        {
            choice = 2;
        }
        else if (GetAsyncKeyState(VK_NUMPAD3))
        {
            choice = 3;
        }
        else if (GetAsyncKeyState(VK_NUMPAD4))
        {
            choice = 4;
        }
        else if (GetAsyncKeyState(VK_NUMPAD5))
        {
            choice = 5;
        }
        else if (ismouseclick(WM_LBUTTONDOWN))
        {
            x1 = cursorPos.x;
            y1 = cursorPos.y;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        else if (ismouseclick(WM_LBUTTONUP))
        {
            x2 = cursorPos.x;
            y2 = cursorPos.y;
            clearmouseclick(WM_LBUTTONUP);
            if (choice == 2)
            {
                drawRectangle(x1, y1, x2, y2);
                drawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
            }
            if (choice == 3)
            {
                line(x1, y1, x2, y2);
                line(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
            }
            if (choice == 5)
            {
                double dia = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
                int xc = (x1 + x2) / 2;
                int yc = (y1 + y2) / 2;
                circle(xc, yc, dia / 2);
                circle(xc, yc, dia / 2 - 1);
            }
        }
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            if (cursorPos.x <= 0.9 * width-size)
            {
                switch (choice)
                {
                case 1:
                    brushTool(cursorPos.x, cursorPos.y, size, color);
                    break;
                case 2:
                    break;
                case 3:
                    // drawLine(cursorPos.x, cursorPos.y, color);
                    break;
                case 4:
                    setfillstyle(1, color);
                    floodfill(cursorPos.x, cursorPos.y, BLACK);
                    break;
                }
            }
            // sidebar operations
            else
                sidebarOperations(cursorPos, width, height, size, color);
        }

        if (GetAsyncKeyState(VK_SPACE))
        {
            cleardevice();
            preWriitenText(width, height, sidebarWidth, size, BLACK);
            delay(200);
        }

        if (GetAsyncKeyState(VK_RETURN))
        {
            writeimagefile("img.jpeg");
            cleardevice();
            preWriitenText(width, height, sidebarWidth, size, BLACK);
            delay(500);
        }
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }
}
