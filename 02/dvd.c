#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

enum ColisionDireciton { None, Virticle, Horizontal };

int hitEdge(int positionX, int positionY, int size)
{
  if (positionX <= 0 || positionX + size >= WINDOW_WIDTH)
    {
      return Horizontal;
    }
  else if (positionY <= 0 || positionY + size >= WINDOW_HEIGHT)
    {
    return Virticle;
    }
  else
    {
      return None;
    }
}

int main(void)
{
  int windowHeight = 450;
  char saverText[] = "DVD";

  int saverPositionX = 100;
  int saverPositionY = 140;
  int size = 100;
  int boarderSize = 10;

  int speedX = 2;
  int speedY = 3;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PAUSED");

  int textLength = MeasureText(saverText, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      int hitDirection = hitEdge(saverPositionX, saverPositionY, size);
      if (hitDirection == Horizontal)
        {
          speedX = speedX * -1;
        }
      else if (hitDirection == Virticle)
        {
          speedY = speedY * -1;
        }

      saverPositionX += speedX;
      saverPositionY += speedY;

      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(saverPositionX, saverPositionY, size, size, BLACK);
      DrawRectangle(saverPositionX + boarderSize, saverPositionY + boarderSize, size - boarderSize*2, size - boarderSize *2, RAYWHITE);

      DrawText(saverText, saverPositionX + size/2 - textLength/2, saverPositionY + size / 2 - 10, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
