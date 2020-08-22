#include "raylib.h"

int hitVirticle(int x, int size)
{
  if (x <= 0 || x + size >= 800)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int hitHorizontal(int y, int size)
{
  if (y <= 0 || y + size >= 450)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int main()
{
  int windowWidth = 800;
  int windowHeight = 450;

  Vector2 saverPosition = { 140, 140 };
  Vector2 speed = { 1, 1 };

  InitWindow(windowWidth, windowHeight, "Pause");

  int size = 120;
  int boarderSize = 10;

  char saverText[] = "DVD";
  int textLength = MeasureText(saverText, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      if (hitVirticle(saverPosition.x, size) == 1)
        {
          speed.x = speed.x * -1;
        }
      else if (hitHorizontal(saverPosition.y, size) == 1)
        {
          speed.y = speed.y * -1;
        }

      saverPosition.x += speed.x;
      saverPosition.y += speed.y;


      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(saverPosition.x, saverPosition.y, size, size, BLACK);
      DrawRectangle(saverPosition.x + boarderSize, saverPosition.y + boarderSize, size - boarderSize * 2, size - boarderSize * 2, RAYWHITE);

      DrawText(saverText, saverPosition.x + size / 2 - textLength / 2, saverPosition.y + size / 2 - 10, 20, BLACK);


      EndDrawing();
    }

  CloseWindow();
  return 0;
}
