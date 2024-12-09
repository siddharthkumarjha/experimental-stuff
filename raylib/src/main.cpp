#include "raylib.h"
#include <thread>

int main(void)
{
    InitWindow(500, 500, "My first window");

    int x = 0, y = 0;
    int dx = 1, dy = 0;

    using namespace std::chrono_literals;
    while(!WindowShouldClose())
    {
        // if(x <= 0 or x >= (GetScreenWidth() - 50))
        //     dx = -dx;
        // if(y <= 0 or y >= (GetScreenHeight() - 50))
        //     dy = -dy;

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(x, y, 50, 50, RED);
        EndDrawing();

        x += dx;
        y += dy;
        std::this_thread::sleep_for(10ms);
    }
    CloseWindow();
    return 0;
}
