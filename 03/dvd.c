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

int main(void)
{
  int windowWidth = 800;
  int windowHeight = 450;

  Vector2 position = { 140, 140 };
  Vector2 speed = { 1, 1 };

  InitWindow(windowWidth, windowHeight, "Pause");

  int size = 120;
  int boarderSize = 10;

  char text[] = "DVD";
  int textLength = MeasureText(text, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      if (hitVirticle(position.x, size) == 1)
        {
          speed.x = speed.x * -1;
        }
      else if (hitHorizontal(position.y, size) == 1)
        {
          speed.y = speed.y * -1;
        }

      position.x += speed.x;
      position.y += speed.y;


      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(position.x, position.y, size, size, BLACK);
      DrawRectangle(position.x + boarderSize, position.y + boarderSize, size - boarderSize * 2, size - boarderSize * 2, RAYWHITE);

      DrawText(text, position.x + size / 2 - textLength / 2, position.y + size / 2 - 10, 20, BLACK);


      EndDrawing();
    }

  CloseWindow();
  return 0;
}
