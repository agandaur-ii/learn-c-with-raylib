#include "raylib.h"
#include "stdio.h"

Rectangle imageFrame(int x, int y, int imageUnits)
{
  Rectangle part = { x * imageUnits, y * imageUnits, imageUnits, imageUnits };
  return part;
}

Vector2 imageLocation(int i, float imageUnits)
{
  int x = i % 4;
  int y = i / 4;
  Vector2 position = { x * imageUnits, y * imageUnits };
  return position;
}

// 0  1  2  3
// 4  5  6  7
// 8  9  10 11
// 12 13 14 15

typedef struct Piece
{
  int x;
  int y;
  int empty;
} piece;

int main(void)
{
    const int screenWidth = 256;
    const int screenHeight = 256;

    InitWindow(screenWidth, screenHeight, "Slide Puzzle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D picture = LoadTexture("resources/pigeon.png"); // Texture loading
    int imageUnits = picture.width/4;

    struct Piece pieces[16];

    int missingPieceId = 15;

    int pieceNum = 0;

    for (int y = 0; y < 4; y++)
      {

        for (int x = 0; x < 4; x++)
          {
            if (pieceNum != 15)
              {
                struct Piece piece = { x, y, 0 };
                pieces[pieceNum] = piece;
              }
            else
              {
                struct Piece piece = { x, y, 1 };
                pieces[pieceNum] = piece;

              }
            pieceNum++;
          }

      }

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      if (IsKeyPressed(KEY_RIGHT) && (missingPieceId + 1) % 4 != 0)
        {
          int targetPieceId = missingPieceId + 1;
          piece temp = pieces[missingPieceId];

          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_LEFT) && (missingPieceId) % 4 != 0)
        {
          int targetPieceId = missingPieceId - 1;
          piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_UP) && missingPieceId - 4 > 1)
        {
          int targetPieceId = missingPieceId - 4;
          piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_DOWN) && missingPieceId + 4 < 15)
        {
          int targetPieceId = missingPieceId + 4;
          piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }

      BeginDrawing();

      ClearBackground(RAYWHITE);

      for (int i = 0; i < 16; i++)
        {
          if (pieces[i].empty == 0)
            {
              Vector2 loc = imageLocation(i, imageUnits);
              Rectangle frame = imageFrame(pieces[i].x, pieces[i].y, imageUnits);
              DrawTextureRec(picture, frame, loc, WHITE);
              DrawRectangleLinesEx(frame, 1, BLACK);
            }
        }
      EndDrawing();
    }
    UnloadTexture(picture);       // Texture unloading
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
