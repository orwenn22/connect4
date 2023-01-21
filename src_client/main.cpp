#include <raylib.h>

#include <Engine/Game.h>

#include "MenuState.h"

int main() {
    InitWindow(512, 512, "Connect 4");
    SetTargetFPS(60);

    Game* mygame = new Game();
    mygame->SetState(new MenuState("Press Enter to connect"));

    while(!WindowShouldClose()) {
        mygame->Update();

        BeginDrawing();
            ClearBackground(BLACK);
            mygame->Draw();
            DrawFPS(10, 10);
        EndDrawing();
    }

    delete mygame;
    CloseWindow();
    return 0;
}