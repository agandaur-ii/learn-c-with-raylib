#include "raylib.h"

int hitLeft(float x, float size)
{
  if (x - size <= 0)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int hitRight(float x, float size)
{
  if (x + size >= 800)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int hitTop(float y, float size)
{
  if (y - size <= 0)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int hitBottom(float y, float size)
{
  if (y + size >= 450)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}


int inRect(Rectangle rect, Vector2 position) {
  if (position.y >= rect.y && position.y <= rect.y + rect.height) { // right height
    if (position.x >= rect.x && position.x <= rect.x + rect.width) { // hit
      return 1;
    }
  }
  return 0;
}

int hitPaddle(Rectangle paddle, Vector2 position, float size) {
  // balls can only hit at left or right at the origin,
  // so we don't have to worry about angle hits too much.
  Vector2 leftEdge = { position.x - size, position.y };
  Vector2 rightEdge = { position.x + size, position.y };
  // TODO: we could use the speed to decide which edge to test
  if (inRect(paddle, leftEdge) || inRect(paddle, rightEdge)) {
    return 1;
  }

  return 0;
}

int main()
{
  int windowWidth = 800;
  int windowHeight = 450;

  Rectangle paddle1 = { 40, windowHeight/2 - 50, 20, 100 };
  Rectangle paddle2 = { windowWidth - 40, windowHeight/2 - 50, 20, 100 };

  Vector2 position = { windowWidth / 2 - 5, windowHeight / 2 - 5 };
  Vector2 speed = { 5, 5 };

  int paddle1Score = 0;
  int paddle2Score = 0;

  float paddleSpeed = 3.0f;
  InitWindow(windowWidth, windowHeight, "Pong");

  float size = 10.0f;

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      if (hitTop(position.y, size) == 1)  {
        speed.y = speed.y * -1;
      } else if (hitBottom(position.y, size) == 1) {
        speed.y = speed.y * -1;
      } else if (hitLeft(position.x, size) == 1) {
        paddle2Score += 1;
        position.x = windowWidth / 2 - 5;
        position.y = windowHeight / 2 - 5;
      } else if (hitRight(position.x, size) == 1) {
        paddle1Score += 1;
        position.x = windowWidth / 2 - 5;
        position.y = windowHeight / 2 - 5;
      } else if (hitPaddle(paddle1, position, size)) {
        speed.x = speed.x * -1;
        position.x = paddle1.x + paddle1.width + size;
      } else if (hitPaddle(paddle2, position, size)) {
        speed.x = speed.x * -1;
        position.x = paddle2.x - size;
      }

      if (IsKeyDown(KEY_W)) {
        paddle1.y -= paddleSpeed;
      }

      if (IsKeyDown(KEY_S)) {
        paddle1.y += paddleSpeed;
      }

      if (IsKeyDown(KEY_UP)) {
        paddle2.y -= paddleSpeed;
      }

      if (IsKeyDown(KEY_DOWN)) {
        paddle2.y += paddleSpeed;
      }

      position.x += speed.x;
      position.y += speed.y;

      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawCircleV(position, size, BLACK);

      DrawRectangleRec(paddle1, BLACK);
      DrawRectangleRec(paddle2, BLACK);

      DrawText(FormatText("%i - %i", paddle1Score, paddle2Score), windowWidth / 2 - 25, 20, 20, BLACK);
      DrawText(FormatText("(%f, %f)", position.x, position.y), windowWidth / 2 - 25, 40, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
