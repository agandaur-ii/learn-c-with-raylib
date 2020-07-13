#include "raylib.h"

int hitVirticle(int positionX, int size)
{
  if (positionX <= 0 || positionX + size >= 800)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int hitHorizontal(int positionY, int size)
{
  if (positionY <= 0 || positionY + size >= 450)
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

  int saverPositionX = 140;
  int saverPositionY = 140;

  int speedX = 1;
  int speedY = 1;

  InitWindow(windowWidth, windowHeight, "Pause");

  int size = 120;
  int boarderSize = 10;

  char saverText[] = "DVD";
  int textLength = MeasureText(saverText, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      if (hitVirticle(saverPositionX, size) == 1)
        {
          speedX = speedX * -1;
        }
      else if (hitHorizontal(saverPositionY, size) == 1)
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
