#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 154, 255};

int player_score = 0;
int computer_score = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;
    Color color = WHITE;

    void Draw() {
        DrawCircle(x, y, radius, color);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            computer_score++;
            ResetBall();
        } else if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) y = 0;
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;
    Color color = WHITE;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, color);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }

        LimitMovement();
    }
};

class ComputerPaddle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 < ball_y) {
            y += speed;
        } else if (y + height / 2 > ball_y) {
            y -= speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle player;
ComputerPaddle computer;

int main () {
    cout << "===== START GAME =====" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.color = Yellow;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;
    player.color = BLUE;

    computer.width = 25;
    computer.height = 120;
    computer.x = 10;
    computer.y = screen_height / 2 - player.height / 2;
    computer.speed = 6;
    computer.color = RED;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // updating
        ball.Update();
        player.Update();
        computer.Update(ball.y);

        // check collisions
        if (CheckCollisionCircleRec(
            Vector2{ball.x, ball.y},
            ball.radius,
            Rectangle{player.x, player.y, player.width, player.height}
            )) {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(
            Vector2{ball.x, ball.y},
            ball.radius,
            Rectangle{computer.x, computer.y, computer.width, computer.height}
            )) {
            ball.speed_x *= -1;
        }

        // drawing
        // center ball in screen
        ClearBackground(DarkGreen);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, LightGreen);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        computer.Draw();
        DrawText(TextFormat("%i", computer_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), screen_width * .75 + 20, 20, 80, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}