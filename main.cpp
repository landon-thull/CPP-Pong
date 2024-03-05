#include <iostream>
#include <raylib.h>

using namespace std;

int main () {
    cout << "Starting the game" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}