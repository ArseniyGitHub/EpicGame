#include <string>
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <memory>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#define RAYGUI_IMPLEMENTATION
#include "Game.h"
#define cu8(str) reinterpret_cast<const char*>(u8##str)
#define u8str(str) (char*)(void*)str
/*
int windowsX, windowsY;

struct Player{
    Vector2 pos{0, 0};
    Color clr {255, 0, 0, 255};
    Player(){

    }
};
*/
/*
void playerlost(){
    int* p;
    *p = 9;
}
 */
/*
void movecam(Camera2D& cam2a, Player& player){
    cam2a.target = player.pos;
}


int mainloop2d(){
    float dts = 0.;
    Player player; //
    Camera2D cam2b;
    cam2b.offset = (Vector2){GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    player.pos = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    cam2b.zoom = 1;
    cam2b.rotation = 0;
    cam2b.target = player.pos;
    while(!WindowShouldClose()) {
        dts = GetFrameTime();
        BeginDrawing();
        ClearBackground((Color){255, 0, 255, 50});
        DrawText(TextFormat("fps: %d", GetFPS()), 50, 50, 90, (Color){0, 255, 0, 100});
        BeginMode2D(cam2b);
        DrawCircle(400, 400, 60, Color({0, 0, 0, 255}));
        DrawCircle(player.pos.x, player.pos.y, 30, player.clr);
        player.pos.x -= dts * 100;
        player.pos.y -= dts * 100;
        movecam(cam2b, player);
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 1;
};;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

int mainloop3d(){
    Camera3D cam4b;
    cam4b.position = {10, 10, 10};
    cam4b.target = {0, 0, 0};
    cam4b.up = {0.f, 1.f, 0.f};
    cam4b.projection = CAMERA_PERSPECTIVE;
    cam4b.fovy = 90;
    std::vector<Vector3> cps = {
            {0, 0, 0},
            {10, 0, 0},
            {0, 0, 10}
    };

    while(!WindowShouldClose()){
        // playerlost();
        BeginDrawing();

        ClearBackground((Color){0, 100, 100, 50});
        DrawText(TextFormat("Windows 95 is starting... fps: %d", GetFPS()), 50, 50, 90, (Color){0, 255, 0, 100});
        BeginMode3D(cam4b);

        for(auto& e : cps){
            DrawCube(e, 2, 2, 2, Color({255, 255, 255, 254}));
            DrawCubeWires(e, 2, 2, 2, Color({0, 0, 0, 254}));
        }

        EndMode3D();
        EndDrawing();
    }
    return 1;
}
*/
/*
int main(){

    InitWindow(0, 0, u8str(u8"Привет"));
    // SetTargetFPS(100000);
    int windowsX = GetScreenWidth();
    int windowsY = GetScreenHeight();
    SetWindowSize(windowsX, windowsY);
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(Color{0, 0, 0, 255});
        DrawCircle(100, 100, 60, Color{255, 255, 0, 255});
        EndDrawing();
    }

};;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/

int main(){
    Game game;
    game.run();
}

