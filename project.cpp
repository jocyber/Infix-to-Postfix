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
   bool mouseOnButton = false;
   bool buttonPressed = false;
   
   std::string input = "";
   std::string inputCopy = "";
   int letterCount = 0;
   int position = 0;
   std::string postfix;
   const std::string underscore {"_"};
   
   Rectangle textbox {100, 200, 400, 40};
   Rectangle button {510, 200, 75, 40};

   
   InitWindow(WindowWidth, WindowHeight, "Infix to Postfix Converter");
   SetTargetFPS(30);
   
    
   while(!WindowShouldClose())
   {
        BeginDrawing();
    
        ClearBackground(Color{GRAY});
        DrawText("Enter Infix Expression: ",155, 150, 25, WHITE);
        DrawRectangleRec(textbox,WHITE);
        DrawRectangleRec(button, WHITE);
        
        std::string expression;
        std::string answer;
        static std::string warning = "Expression is not balanced.";
        static std::string temp;
        static std::string tempAnswer;
        
        if(CheckCollisionPointRec(GetMousePosition(), textbox)) mouseOnText = true;
        else mouseOnText = false;
        
        if(CheckCollisionPointRec(GetMousePosition(), button)) mouseOnButton = true;
        else mouseOnButton = false;
        
        if(mouseOnButton && IsMouseButtonPressed(0)) 
            buttonPressed = true;
        else { 
            buttonPressed = false;
        }
        
        if(mouseOnText)
        {
            int key = GetKeyPressed();
            
            while(key > 0)
            {
                if((letterCount < MAX_CHAR_COUNT) && (((key >= 40) && (key <= 43)) || (key == 45) || (key == 47) || (key == 123) || (key == 125) || ((key >= 48) && (key <= 57)))) {
                    char tempChar = (char)key;
                    input.insert(position, 1, tempChar);
                    inputCopy.insert(position, 1, tempChar);
                    letterCount++;
                    position++;
                }
                
                key = GetKeyPressed();
            }
            
            if(IsKeyPressed(KEY_BACKSPACE))
            {
                if(!(letterCount <= 0) && position - 1 >= 0) {
                    letterCount--;
                    position--;
                    input.erase(position, 1);
                    inputCopy.pop_back();
                }
            }
            
            if(IsKeyPressed(KEY_LEFT)) {
                if(position - 1 >= 0) {
                    position--;
                    inputCopy.pop_back();
                }
            }
            if(IsKeyPressed(KEY_RIGHT)) {
                if(position + 1 <= letterCount) {
                    inputCopy.push_back(input[position]);
                    position++;
                }
            }
            
            DrawText(underscore.c_str(), textbox.x + 6 + MeasureText(inputCopy.c_str(), 30), textbox.y + 12, 30, RED);
        }

        if(mouseOnText) DrawRectangleLines(textbox.x, textbox.y, textbox.width, textbox.height, RED);
        DrawText(input.c_str(), textbox.x + 3, textbox.y + 6, 30, RED);
        
        if(mouseOnButton) DrawRectangleLines(button.x, button.y, button.width, button.height, RED);
        DrawText("Enter", button.x + 5, button.y + 8, 24, RED);
        
        if(buttonPressed){
            if(isParenMatching(input)) {
                postfix = conversion(input);
                
                expression = "Postfix: " + postfix;
                answer = "Answer: " + std::to_string(evaluate(postfix));
                
                temp = expression;
                tempAnswer = answer;
                DrawText(temp.c_str(), textbox.x + 3, textbox.y + 60, 30, WHITE);
                DrawText(tempAnswer.c_str(), textbox.x + 3, textbox.y + 90, 30, WHITE);
            }else
                DrawText(warning.c_str(), textbox.x + 3, textbox.y + 200, 30, WHITE);
        }else {
            DrawText(temp.c_str(), textbox.x + 3, textbox.y + 60, 30, WHITE);
            DrawText(tempAnswer.c_str(), textbox.x + 3, textbox.y + 90, 30, WHITE);
            
            if(!isParenMatching(input))
                 DrawText(warning.c_str(), textbox.x + 3, textbox.y + 200, 30, WHITE);
        }
           
        
        EndDrawing();
   }       
   
   CloseWindow();
    
   return EXIT_SUCCESS;
}
