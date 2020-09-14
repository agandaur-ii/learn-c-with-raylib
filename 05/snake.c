#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define GRID_SIZE 25
#define GRID_MARGIN 2
#define GRID_WIDTH 20
#define GRID_HEIGHT 20

typedef struct Coordinate {
  int x;
  int y;
} Coordinate;

typedef struct SnakeCell {
  Coordinate position;
  void * next;
} SnakeCell;

Vector2 gridToPixels(Coordinate cor) {
  return (Vector2){ cor.x * GRID_SIZE, cor.y * GRID_SIZE };
}

void drawGrid() {
  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
      DrawRectangleLines(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE, LIGHTGRAY);
    }
  }
}

void drawSquare(Coordinate cor, Color color) {
  Vector2 pixelPosition = gridToPixels(cor);
  DrawRectangle(pixelPosition.x + 1, pixelPosition.y + 1, GRID_SIZE - GRID_MARGIN, GRID_SIZE - GRID_MARGIN, color);
}

int main()
{
  int windowWidth = GRID_SIZE * GRID_WIDTH;
  int windowHeight = GRID_SIZE * GRID_HEIGHT;
  InitWindow(windowWidth, windowHeight, "My first Raylib program");

  Coordinate speed = { 1, 0 };

  Coordinate food = { GetRandomValue(0, GRID_WIDTH), GetRandomValue(0, GRID_HEIGHT) };

  int frameCounter = 0;

  struct SnakeCell * head = malloc(sizeof(struct SnakeCell) * GRID_WIDTH * GRID_HEIGHT);
  struct SnakeCell * curSnakeCell = head;
  struct SnakeCell * nextSnakeCell = head;
  struct SnakeCell * nextMallocSpot = head;
  nextMallocSpot++;

  curSnakeCell->position.x = 10;
  curSnakeCell->position.y = 10;
  curSnakeCell->next = nextMallocSpot;
  curSnakeCell = curSnakeCell->next;
  nextMallocSpot++;

  curSnakeCell->position.x = 9;
  curSnakeCell->position.y = 250;
  curSnakeCell->next = nextMallocSpot;
  curSnakeCell = curSnakeCell->next;
  nextMallocSpot++;

  curSnakeCell->position.x = 8;
  curSnakeCell->position.y = 250;
  curSnakeCell->next = nextMallocSpot;
  curSnakeCell = curSnakeCell->next;
  nextMallocSpot++;

  curSnakeCell->position.x = 7;
  curSnakeCell->position.y = 250;
  curSnakeCell->next = NULL;
  nextMallocSpot++;

  curSnakeCell = head;

  SetTargetFPS(30);
  while (!WindowShouldClose())
    {
      // TODO: since the snake doesn't move every frame
      //       the snake can turn on top of itself causing a position
      //       should loose the game
      if (IsKeyPressed(KEY_UP) && speed.y <= 0) {
        speed.x = 0;
        speed.y = -1;
      } else if (IsKeyPressed(KEY_DOWN) && speed.y >= 0) {
        speed.x = 0;
        speed.y = 1;
      } else if (IsKeyPressed(KEY_LEFT) && speed.x <= 0) {
        speed.x = -1;
        speed.y = 0;
      } else if (IsKeyPressed(KEY_RIGHT)  && speed.x >= 0) {
        speed.x = 1;
        speed.y = 0;
      } else if (IsKeyPressed(KEY_R)) {
        curSnakeCell = head;
        memcpy(nextMallocSpot, head, sizeof(struct SnakeCell));
        curSnakeCell = nextMallocSpot;
        curSnakeCell->next = head;
        head = curSnakeCell;
        nextMallocSpot++;
      }

      frameCounter++;
      if (frameCounter > 3) {
        curSnakeCell = head;
        while (curSnakeCell->next != NULL) {
          nextSnakeCell = curSnakeCell;
          curSnakeCell = curSnakeCell->next;
        }

        curSnakeCell->position.x = head->position.x + speed.x;
        curSnakeCell->position.y = head->position.y + speed.y;
        curSnakeCell->next = head;
        nextSnakeCell->next = NULL;
        head = curSnakeCell;
        frameCounter = 0;
      }


      if (head->position.x == food.x && head->position.y == food.y) {
        // TODO: not inside yourself
        food.x = GetRandomValue(0, GRID_WIDTH - 1);
        food.y = GetRandomValue(0, GRID_HEIGHT - 1);

        printf("FOOD (%i, %i)\n", food.x, food.y);

        curSnakeCell = head;
        memcpy(nextMallocSpot, head, sizeof(struct SnakeCell));
        curSnakeCell = nextMallocSpot;
        curSnakeCell->next = head;
        head = curSnakeCell;
        nextMallocSpot++;
      }

      BeginDrawing();

      ClearBackground(RAYWHITE);

      drawGrid();

      curSnakeCell = head;
      while (curSnakeCell != NULL) {
        drawSquare(curSnakeCell->position, BLACK);
        curSnakeCell = curSnakeCell->next;
      }

      drawSquare(food, RED);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
