/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*b
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "game.h"
#include <iostream>


class Window
{

public:
    Window(int screenWidth, int screenHeight) noexcept
    {
        InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    }
    Window(const Window&) = delete;//copy construct
    Window& operator=(const Window&) = delete;//copy assignment
    Window(Window&&) = delete;//move construct
    Window& operator=(Window&&) = delete; //move assignment

    ~Window()
    {
        CloseWindow();
    }
};


int main(void)
{    
    try
    { 
        constexpr int screenWidth = 1920;
        constexpr int screenHeight = 1080;

        Window window(screenWidth, screenHeight);
        SetTargetFPS(60); 

        Game game{};

        while (!WindowShouldClose())
        {
            game.Update();
            BeginDrawing();
            ClearBackground(BLACK);
            game.Render();
            EndDrawing();
        }
    }
    catch (const std::exception& _exception)
    {
        std::cerr << "Exception caught: " << _exception.what() << std::endl;
    }

    return 0;
}