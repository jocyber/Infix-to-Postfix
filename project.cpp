#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "infixToPostfix.h"

#define MAX_CHAR_COUNT 20

int main()
{
   const int WindowWidth {600};
   const int WindowHeight {600};
   bool mouseOnText = false;
   std::string input = "";
   int letterCount = 0;
   
   Rectangle textbox {100, 200, 400, 40};
   
   InitWindow(WindowWidth, WindowHeight, "Infix to Postfix Converter");
   SetTargetFPS(30);
   
    
   while(!WindowShouldClose())
   {
        BeginDrawing();
    
        ClearBackground(Color{GRAY});
        DrawText("Enter Infix Expression: ",155, 150, 25, WHITE);
        DrawRectangleRec(textbox,WHITE);
        std::string postfix = conversion(input);
        
        
        if(CheckCollisionPointRec(GetMousePosition(), textbox)) mouseOnText = true;
        else mouseOnText = false;
        
        if(mouseOnText)
        {
            int key = GetKeyPressed();
            
            while(key > 0)
            {
                if((letterCount < MAX_CHAR_COUNT) && (((key >= 40) && (key <= 43)) || (key == 45) || (key == 47) || (key == 123) || (key == 125) || ((key >= 48) && (key <= 57)))) {
                    char temp = (char)key;
                    input.push_back(temp);
                    letterCount++;
                }
                
                key = GetKeyPressed();
            }
            
            
            if(IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                input.pop_back();
                if(letterCount < 0) letterCount = 0; 
            }
        }

        if(mouseOnText) DrawRectangleLines(textbox.x, textbox.y, textbox.width, textbox.height, RED);
        DrawText(input.c_str(), textbox.x + 3, textbox.y + 6, 30, RED);
        
        std::string expression = "Postfix: " + postfix;
        DrawText(expression.c_str(), textbox.x + 3, textbox.y + 60, 30, WHITE);
        EndDrawing();
   }       
   
   CloseWindow();
    
   return EXIT_SUCCESS;
}