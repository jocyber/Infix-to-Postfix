#ifndef CONVERT
#define CONVERT

#include <iostream>
#include "StackADT.h"
#include <string.h>

int isOperand(char x) 
    {return (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == '^' ? 0 : 1);}

int priority(char x) 
    {return (x == '+' || x == '-' ? 1 : x == '*' || x == '/' ? 3 : x == '^' ? 6 : x == '(' ? 7 : x == ')' ? 0 : 0);}

int stackPrior(char x)
    {return (x == '+' || x == '-' ? 2 : x == '*' || x == '/' ? 4 : x == '^' ? 5 : x == '(' ? 0 : 0);}

int isOperator(char x) {return (x == '+' ||  x == '-' || x == '*' || x == '/' ? 1 : 0);}

bool isParenMatching(const std::string &expression) {
    Stack<char> st;

    for(const char &x : expression) {
        if(x == '(' || x == '[' || x == '{')
            st.push(x);

        else if ((st.isEmpty() && x == ')') || (st.isEmpty() && x == ']') ||
        (st.isEmpty() && x == '}'))
            return false;

        else if(x == ')' || x == ']' ||
        x == '}') {
            char temp = st.pop();
        
            if((temp == '(' && x != ')') || (temp == '[' && x != ']' || 
            (temp == '{' && x != '}')))
               return false;
               
        }
    }

    return ((st.isEmpty()) ? true : false);
}

std::string conversion(const std::string &infix)
{
    Stack<char> st;
    std::string postfix = "";

    for(int i = 0; i < infix.length();) {

        if(infix[i] != ' ') {
            if(isOperand(infix[i]))
                postfix.push_back(infix[i++]);
            else if(priority(infix[i]) > stackPrior(st.stackTop())) {
                st.push(infix[i++]);
            }
            else {
                if(priority(infix[i]) < stackPrior(st.stackTop()))
                    postfix.push_back(st.pop());

                if(priority(infix[i]) == stackPrior(st.stackTop()) && !st.isEmpty()) {
                    i++;
                    st.pop();
                }
            }
        }else i++;
    }

    while(!st.isEmpty())
        postfix.push_back(st.pop());
            
    return postfix;
}

int evaluate(const std::string &postfix) {

    Stack<int> st;
    int result;

    for(const char &x : postfix) {
        if(isOperand(x)){
            st.push(x - '0');
        }
        else if(isOperator(x)) {
            int second = st.pop();
            int first = st.pop();

            switch(x){
                case '+' : result = first + second; st.push(result); break;
                case '-' : result = first - second; st.push(result); break;
                case '*' : result = first * second; st.push(result); break;
                case '/' : result = first / second; st.push(result); break;
            }
        }
    }

    return st.pop();

}


#endif