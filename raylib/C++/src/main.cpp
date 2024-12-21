#include "raylib.h"
#include <thread>

int x = 0, y = 0;
int dx = 1, dy = 1;

void boundsCheck()
{
    x += dx;
    y += dy;

    if(x == 0 or x == (GetScreenWidth() - 50))
        dx = -dx;
    if(y == 0 or y == (GetScreenHeight() - 50))
        dy = -dy;
}

int main(void)
{
    InitWindow(500, 500, "My first window");

    using namespace std::chrono_literals;
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(x, y, 50, 50, RED);
        EndDrawing();

        boundsCheck();

        std::this_thread::sleep_for(10ms);
    }
    CloseWindow();
    return 0;
}
