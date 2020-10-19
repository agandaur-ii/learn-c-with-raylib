# Making games with raylib

https://www.raylib.com/index.html

> raylib is a simple and easy-to-use
> library to enjoy videogames programming.

Use raylib because it is fun and in C. it does 2d and
3d and is inspired by XNA and other game frameworks that make amazing
games.

## Install

Install instructions can be found on GitHub under the "Development
Platforms" side bar header.

[Wiki](https://github.com/raysan5/raylib/wiki)

Think about keeping a couple tabs open with,
- [Examples](https://www.raylib.com/examples.html)
- [Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)

Open while you play so you can find out more about raylib as you go.

There are a number of ways to install and configure raylib to work,
but for the purposes of this tutorial I am going to assume that you
can compile and run programs in a way that is fun and easy for you.

On my machine I installed raylib with `brew install raylib` and run my
programs with

```
gcc -g -Wall <my-program>.c `pkg-config --libs --cflags raylib`
```

for the simple examples throughout this tutorial. Any additional
configuration or compilation steps you have to do will be explained
when we get to them.

## Writting the simplest program

Lets write the simplest raylib program we can in C. We can write


```c
#include "raylib.h"

int main()
{
  InitWindow(800, 450, "My first Raylib program");
  SetTargetFPS(60);
  while (!WindowShouldClose())
    {
      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("Hello, raylib!", 0, 0, 20, BLACK);

      EndDrawing();
    }

  CloseWindow();
  return 0;
}

```

copy paste this into your program file then compile and run it and you
should see a window like this!

<image of the program that this creates>

If you have having problems getting this to work, remember to google
your error messages and try to undo things one at a time to see what
specific thing broke.

Assuming this worked for you congratulations! we have a working
program. It isn't quite a game yet, but it works!

## Breaking down our program

Lets go through the program and talk about what each line is doing at
a high level. If you are already familiar with C or raylib, feel free
to skip this section.

```c
#include "raylib.h"
```

this line tells your program to include the `raylib.h` file in your
program. This gives you access to the functions that raylib defines
for your program like the `InitWindow` method and the `DrawText`
method.

If you are an absolute beginner there are some words that probably
want to learn more about. Feel free to dive into these if they are
interesting, or continue on and learn about these things later. for
now you just need to know that this is what you write in your program
to make it use your raylib code.

- what is a .h file?
- What is a library?
- what is a function?
- what is `#include "raylib.h"` actually doing?

```c
int main()
```

This is how you define a function that your program will call when it
starts. the `int` part is the return value `main` is the function name
that you can refer to it by and (void) is the list of arguments that
`main` takes. You can mostly consider this, "the thing you type to
begin your program to tell it what to do when it starts," but we can
dive into some of the details more if you are curious.

- What is an `int`?
- Why return an `int`?
- Why call it `main`?

```c
InitWindow(800, 450, "My first Raylib program");
```

This tells raylib to create a window that is 800 pixels wide and 450
pixels tall with a title bar set to "My first Raylib program"

<picture showing the title bar>

You can change these values, recompile your program and run it again to see what how the window and the title changes.

- what is the bit in quotes?


```c
SetTargetFPS(60);
```

This tells raylib how many frames per second it should aim to render per second. This helps simplify your program because it makes it less likely that you have to deal with the amount of time between frames. since raylib will try to take care of that for you.

```c
while (!WindowShouldClose())
```

This line tells raylib to continue doing the code in the `{}` until the `WindowShouldClose`. `WindowShouldClose` checks if the user presses the escape key or the `x` to close the window.

- What is a `while`?
- why all the parenthesis?
- What is the `!`?

```c
BeginDrawing();
```

This tells raylib that the code under this is going to draw things to the screen. This is important to let raylib start creating the internal resources that it needs to render a new frame. We can think of this as the code that starts the drawing block.

```c
ClearBackground(RAYWHITE);
```

This deletes everything from the background and draws the color `RAYWHITE` over the background.

```c
DrawText("Hello, raylib!", 0, 0, 20, BLACK);
```

This tells raylib to put the words "Hello, raylib!" at 0 pixels away from the top left side and 0 pixels away from the to top of the screen at `20` pixels font size in a `BLACK` color.


```c
EndDrawing();
```

This tells raylib that we are done drawing and it is set to render the frame to the user's screen.

```c
CloseWindow();
```

Now that we are done with the `while` loop we can close the window and finish our program.

```c
return 0;
```

You can read more about c return codes, but if we made it here in our program we assume that the program succeeded and can return a `0` telling the system that nothing went wrong.

## modifying our program

Lets make some changes to our program to make a few things more clear for the next time we try to read it. The first line we might want to update is,

```c
InitWindow(800, 450, "My first Raylib program");
```

We have a couple numbers here where it is hard to know what they might mean. What is 800? what is 450? Instead we can give these two numbers names so that we can refer to them by a name to make it clearer what they are for.

We can give these numbers names and refer to them later in our program. We can do this by changing our code to,

```c
int windowWidth = 800;
int windowHeight = 450;
InitWindow(windowWidth, windowHeight, "My first Raylib program");
```

This is how you make a variable in C. you say what the variable is. In this case a `int` which for now we can think of as how we tell the program to store a number.

This change can make later changes in our program easier. For example now that we can refer to the window size in our program by name, it is much easier to center our text on the screen.

Lets go ahead and give that a try. We can center our text by placing it at half the width of the window and half the height of the window.

```c
DrawText("Hello, raylib!", windowWidth / 2, windowHeight / 2, 20, BLACK);
```
<offcenter text image>

nice! better then before, but not quite in the center. That is because the location of text on the screen is in the upper left corner. Sometimes in programming we refer to this as the `origin point`. So in order to center our text on the screen, we need to subtract half of the width of the text from the x position of the text so that the center of the text is at the center of the screen.

To do this we have to do a couple things. First lets grab the `"Hello, raylib!"` we want to render to the screen and make it a variable as well.
```c
char greeting[] = "Hello, raylib!";

DrawText(greeting, windowWidth / 2, windowHeight / 2, 20, BLACK);
```

This names our text `"Hello, raylib!"` `greeting` and references it when we call `DrawText`

Next `raylib` offers us a method `MeasureText` that we can use to find out how big a bit of text is on the screen. We should be able to use that to take that measurement and shift the text by that measurement to center it on the screen.

That would update our code to look like this

```c
char greeting[] = "Hello, raylib!";
int textLength = MeasureText(greeting, 20);

DrawText(greeting, windowWidth / 2 - textLength / 2, windowHeight / 2, 20, BLACK);
```

TODO:
- Text needs to move up by half the font size to be truely centered
- move the `greeting` string and `Measure text` out of the game loop. Also explain why it needs to be called after the `InitWindow` method is called.
