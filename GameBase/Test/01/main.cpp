//#include "../../External/raygui/raygui.h"
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
#include "../../Engine/Game.h"

int main() {
    Game game;
    game.run();
}
