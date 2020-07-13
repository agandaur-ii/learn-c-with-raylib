# Making the DVD pause screen

<dvd screen shot>

Lets make a dvd pause screen. We can start by writing really similar code to our greeting example, but lets just change the message to "DVD"

```c
#include "raylib.h"

int main(void)
{
  int windowWidth = 800;
  int windowHeight = 450;
  InitWindow(windowWidth, windowHeight, "Pause");

  char saverText[] = "DVD";
  int textLength = MeasureText(saverText, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText(saverText, windowWidth / 2 - textLength / 2, windowHeight / 2, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
```

To make it look more like the dvd pause screen we expect, lets add a box around the our text "DVD". Lets update the part between `BeginDrawing` and `EndDrawing`.

```c
ClearBackground(RAYWHITE);

DrawRectangle(windowWidth / 2 - 60, windowHeight / 2 - 60, 120, 120, BLACK);
DrawRectangle(windowWidth / 2 - 50, windowHeight / 2 - 50, 100, 100, RAYWHITE);
DrawText(saverText, windowWidth / 2 - textLength / 2, windowHeight / 2 - 10, 20, BLACK);
```
We have a bunch of magic numbers in here. At a high level we are trying to draw a black square around the text. To do this we draw a black filled-in square behind the text, then a smaller white square inside of the black square to make the square look like it is an outline rather then being a fully black square.

We can start pulling these numbers out into variables to help us understand what exactly they mean.

Lets start by looking at the larger outer rectangle:

```c
DrawRectangle(windowWidth / 2 - 60, windowHeight / 2 - 60, 120, 120, BLACK);
```

The square is 120 wide and 120 pixels tall. Lets start by pulling this out as a `size` of the square.

```c
int size = 120;
DrawRectangle(windowWidth / 2 - 60, windowHeight / 2 - 60, size, size, BLACK);
```

The next magic number is `60` which is really intended to act as half of the size of the cube. That way we move it over by half its size to center it much like we did with the text. We can update our code to communicate that.

```c
int size = 120;
DrawRectangle(windowWidth / 2 - size / 2, windowHeight / 2 - size / 2, size, size, BLACK);
```


Now lets do something similar with our white square. we want it to be 10 pixels smaller in each direction. We can think of this as the size of the boarder. We can write our code something like,

```c
int size = 120;
int boarderSize = 10;
DrawRectangle(windowWidth / 2 - size / 2, windowHeight / 2 - size / 2, size, size, BLACK);
DrawRectangle(windowWidth / 2 - size / 2 - boarderSize, windowHeight / 2 - size / 2 - boarderSize, size, size, RAYWHITE);
```

```c
#include "raylib.h"

int main(void)
{
  int windowWidth = 800;
  int windowHeight = 450;
  InitWindow(windowWidth, windowHeight, "Pause");

  int size = 120;
  int boarderSize = 10;

  char saverText[] = "DVD";
  int textLength = MeasureText(saverText, 20);

  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(windowWidth / 2 - size / 2, windowHeight / 2 - size / 2, size, size, BLACK);
      DrawRectangle(windowWidth / 2 - size / 2 + boarderSize, windowHeight / 2 - size / 2 + boarderSize, size - boarderSize * 2, size - boarderSize * 2, RAYWHITE);
      DrawText(saverText, windowWidth / 2 - textLength / 2, windowHeight / 2 - 10, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}
```

Now that we have our shape on the screen, lets look at how we can move this shape. Lets start by setting our box's location as two variables. Lets add these two variables near the top of our `main` function.

```c
int saverPositionX = 140;
int saverPositionY = 140;
```

then update our drawing code to use these variables

```c
DrawRectangle(saverPositionX, saverPositionY, size, size, BLACK);
DrawRectangle(saverPositionX + boarderSize, saverPositionY + boarderSize, size - boarderSize*2, size - boarderSize *2, RAYWHITE);
DrawText(saverText, saverPositionX + size/2 - textLength/2, saverPositionY + size / 2 - 10, 20, BLACK);
```

Now that we have that variable created, we can minimulate it! Lets add the lines

```c
saverPositionX += 1;
saverPositionY += 1;
```

right before the `BeginDrawing();` line.

Running the example again shows our square sailing off towards the bottom right corner of the screen. Great! we made something move on our screen!

If we can get our square to bounce off the edges, our dvd pause screen should be basically done!

We can make our square bounce by changing its direction when it hits an edge.

There are two concepts we should add to our program based on that. The square should have a speed. We can codify that as a variable for the x and y speed of the square.

Up at the top of `main` with our other variables lets add,
```c
int speedX = 1;
int speedY = 1;
```

The next concept we should look at defining is "hitting the edge."

Since the origin of the square is in the upper left, we will know that the square is hitting the top when the `saverPositionY` is zero or less. same with the left wall. When `saverPositionX` is 0 or less we know that we are hitting the left wall.

The right wall is different however, we know that we hit the right wall when `saverPositionX + saze` equals `windowSize`. same with the bottom, but with `saverPositionY`.

Lets add a function that tells us when we hit the top or bottom and a second function that tells us when you hit left or right. We can use these functions to reverse our direction in the X or Y.

```c
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
```

We can use these functions to decide when the square should change directions. and update our square's speed based on that. right above where we update our squares position, we can check if we need to reverse the direction of the square and do that there.

```c
if (hitVirticle(saverPositionX, size) == 1)
  {
    speedX = speedX * -1;
  }
else if (hitHorizontal(saverPositionY, size) == 1)
  {
    speedY = speedY * -1;
  }
```

Now when our cube hits the edges it should turn around.


# Further improvements

- extract window size
- convert to vectors next lesson
