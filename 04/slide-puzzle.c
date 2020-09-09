#include "raylib.h"
#include "stdio.h"

#define IMAGE_UNITS 64 /* int imageUnits = picture.width/4; */


Rectangle imageFrame(int x, int y)
{
  Rectangle part = { x * IMAGE_UNITS, y * IMAGE_UNITS, IMAGE_UNITS, IMAGE_UNITS };
  return part;
}

Vector2 imageLocation(int i)
{
  int x = i % 4;
  int y = i / 4;
  Vector2 position = { x * IMAGE_UNITS, y * IMAGE_UNITS };
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
} Piece;

typedef enum Direction
  {
   North,
   South,
   East,
   West,
   None
  } Direction;

Direction allowedMoveDirection(int loc, int space) {
  // TODO: these are kinda backwards
  if (loc - 4 == space) {
    return South;
  } else if (loc + 4 == space) {
    return North;
  } else if (loc + 1 == space) {
    return East;
  } else if (loc - 1 == space) {
    return West;
  }
  return None;
}

Vector2 addDelta(int locId, int missingPieceId, Vector2 loc, Vector2 delta) {
  Vector2 updated;
  updated.x = loc.x;
  updated.y = loc.y;
  switch (allowedMoveDirection(locId, missingPieceId)) {
  case North:
    if (delta.y > 0) {
      if (delta.y > 64.0f) {
        updated.y += 64.0f;
      } else {
        updated.y += delta.y;
      }
    }
    break;
  case South:
    if (delta.y < 0) {
      if (delta.y < -64.0f) {
        updated.y += -64.0f;
      } else {
        updated.y += delta.y;
      }
    }
    break;
  case East:
    if (delta.x > 0) {
      if (delta.x > 64.0f) {
        updated.x += 64.0f;
      } else {
        updated.x += delta.x;
      }
    }
    break;
  case West:
    if (delta.x < 0) {
      if (delta.x < -64.0f) {
        updated.x += -64.0f;
      } else {
        updated.x += delta.x;
      }
    }
    break;
  case None:
    break;
  }
  return updated;
}

int pieceUnderCursor(Vector2 pos) {
  int gridX = pos.x / IMAGE_UNITS;
  int gridY = pos.y / IMAGE_UNITS;

  int id = (gridX + (gridY * 4));
  return id;
}

int main()
{
    const int screenWidth = 256;
    const int screenHeight = 256;

    InitWindow(screenWidth, screenHeight, "Slide Puzzle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D picture = LoadTexture("resources/pigeon.png"); // Texture loading

    struct Piece pieces[16];

    int missingPieceId = 15;
    int selectedId = -1;
    Vector2 startingMousePosition = { 0,0 };
    Vector2 delta = { 0,0 };
    int pieceNum = 0;

    for (int y = 0; y < 4; y++)
      {

        for (int x = 0; x < 4; x++)
          {
            pieces[pieceNum].x = x;
            pieces[pieceNum].y = y;

            if (pieceNum == 15) {
              pieces[pieceNum].empty = 1;
            } else {
              pieces[pieceNum].empty = 0;
            }
            pieceNum++;
          }
      }

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        startingMousePosition = GetMousePosition();
        selectedId = pieceUnderCursor(startingMousePosition);
      }

      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 newMousePosition = GetMousePosition();
        delta.x = newMousePosition.x - startingMousePosition.x;
        delta.y = newMousePosition.y - startingMousePosition.y;
      }

      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        selectedId = -1;

        /* printf("delta is (%f, %f) when the mouse was released\n", delta.x, delta.y); */
        if (delta.x > 32) { // snap right
          int targetPieceId = missingPieceId - 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        } else if (delta.x < -32) { // snap left
          int targetPieceId = missingPieceId + 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        } else if (delta.y > 32) { // snap up
          int targetPieceId = missingPieceId - 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        } else if (delta.y < -32) { // snap down
          int targetPieceId = missingPieceId + 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        } else { // not far enough! no snap!

        }
      }

      if (IsKeyPressed(KEY_LEFT) && (missingPieceId + 1) % 4 != 0)
        {
          int targetPieceId = missingPieceId + 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_RIGHT) && (missingPieceId) % 4 != 0)
        {
          int targetPieceId = missingPieceId - 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_DOWN) && missingPieceId - 4 >= 0)
        {
          int targetPieceId = missingPieceId - 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_UP) && missingPieceId + 4 <= 15)
        {
          int targetPieceId = missingPieceId + 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }


      BeginDrawing();

      ClearBackground(RAYWHITE);

      for (int i = 0; i < 16; i++)
        {
          if (pieces[i].empty == 0) {
              if (i == selectedId) {
                Vector2 loc = imageLocation(i);
                Vector2 locWithDelta = addDelta(i, missingPieceId, loc, delta);
                Rectangle frame = imageFrame(pieces[i].x, pieces[i].y);
                DrawTextureRec(picture, frame, locWithDelta, WHITE);
                DrawRectangleLines(locWithDelta.x, locWithDelta.y, frame.width, frame.height, BLACK);
              } else {
                Vector2 loc = imageLocation(i);
                Rectangle frame = imageFrame(pieces[i].x, pieces[i].y);
                DrawTextureRec(picture, frame, loc, WHITE);
                DrawRectangleLines(loc.x, loc.y, frame.width, frame.height, BLACK);
              }
          }
        }
      EndDrawing();
    }
    UnloadTexture(picture);       // Texture unloading
    CloseWindow();                // Close window and OpenGL context
    return 0;
}
