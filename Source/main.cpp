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

#include "raylib.h"
#include "game.h"


class Window
{

public:
    Window(int screenWidth, int screenHeight)
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
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    Window window(screenWidth, screenHeight);
    SetTargetFPS(60); 

    Game game{};


    
    //--------------------------------------------------------------------------------------



  
    



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //if (IsKeyPressed(KEY_SPACE))
        //{
        //    PlaySound(sound);
        //}

        //if (IsKeyPressed(KEY_BACKSPACE))
        //{
        //    StopSound(sound);
        //}

        game.Update();
      

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

       

        game.Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

 
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    //CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    std::string filename = "level.txt";  

    return 0;
}