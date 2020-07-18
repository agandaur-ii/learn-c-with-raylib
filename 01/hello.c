#include "raylib.h"

int main(void)
{
  int windowWidth = 800;
  int windowHeight = 450;
  InitWindow(windowWidth, windowHeight, "My first Raylib program");

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      BeginDrawing();

      ClearBackground(RAYWHITE);

      char greeting[] = "Hello, raylib!";
      int textLength = MeasureText(greeting, 20);

      DrawText(greeting, windowWidth / 2 - textLength / 2, windowHeight / 2, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
