/*
 * File: Assignment-2
 *
 * Author-1: Shehryar Ahmad (2021598)
 * Author-2: Zaid Bin Muzammil (2021718)
 *
 * Description: Infix Postfix implementation using Stack Array and 
 *              functions to evaluate postfix expression.
*/

#include <iostream>
#include <stack>
#include <math.h>

using namespace std;

stack <char> stack1;

int addition(int x, int y);
int subtraction(int x,int);
int multiplication(int x,int y);
int division(int x,int y);

int x = 0;


class InfixToPostfix
{

public:

    InfixToPostfix(const string &inf) : infix(inf) { }

    int getPrecedenceOfOperators(char);

    string convertInfixToPostfix();

private:
    string infix;

};
/**
 * @brief Check precedence of operators and return it to the caller
*/


int InfixToPostfix::getPrecedenceOfOperators(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '^')
        return 3;
    else
        return 0;
}

/**
 * @brief Converts the given infix expression to postfix expression.
*/

string InfixToPostfix::convertInfixToPostfix()
{
    
    string postfix = "";
    string postfix1 = "";
    int i = 0;
    while(infix[i] != '\0')
    {
        //if scanned character is open bracket push it on stack
        if(infix[i] == '(' || infix[i] == '[' || infix[i] == '{')
            stack1.push(infix[i]);

        //if scanned character is opened bracket pop all literals from stack till matching open bracket gets poped
        else if(infix[i] == ')' || infix[i] == ']' || infix[i] == '}')
        {
            if(infix[i] == ')')
            {
                while(stack1.top() != '(')
                {
                    postfix = postfix + stack1.top();
                    stack1.pop();
                }
            }
            if(infix[i] == ']')
            {
                while(stack1.top() != '[')
                {
                    postfix = postfix + stack1.top();
                    stack1.pop();
                }
            }
            if(infix[i] == '}')
            {
                while(stack1.top() != '{')
                {
                    postfix = postfix + stack1.top();
                    stack1.pop();
                }
            }
            stack1.pop();
        }
            //if scanned character is operator
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
        {
            //very first operator of infix is to be pushed on stack
            if(stack1.empty()) {
                stack1.push(infix[i]);

            } else{
                
                if(getPrecedenceOfOperators(stack1.top()) >= getPrecedenceOfOperators(infix[i]))
                {
                    postfix = postfix + stack1.top();
                    stack1.pop();
                    stack1.push(infix[i]);
                }
                else
                {
                    stack1.push(infix[i]);
                }
            }
        }
        else
        {
            //if literal is operand, put it on to final postfix expression
            postfix = postfix + infix[i];
        }
        i++;
    }

    //poping out all remainig operator literals & adding to final postfix expression
    if(!stack1.empty())
    {
        while(!stack1.empty())
        {
            postfix = postfix + stack1.top();
            stack1.pop();
        }
    }

    int n= postfix.length();

     for (int i = 0; i < n; i++)
    {
        // if the character is an operand we push it in the stack
        // we have considered single digits only here
        if ( postfix[i] >= '0' &&  postfix[i] <= '9')
        {
            stack1.push( postfix[i] - '0');
        }
        // if the character is an operator we enter else block
        else
        {
            // we pop the top two elements from the stack and save them in two integers
            int a = stack1.top();
            stack1.pop();
            int b = stack1.top();
            stack1.pop();
            //performing the operation on the operands
            switch (postfix[i])
            {
                case '+': // addition
                          stack1.push(addition(a,b));
                          break;
                case '-': // subtraction
                          stack1.push(subtraction(a,b));
                          break;
                case '*': // multiplication
                          stack1.push(multiplication(a,b));
                          break;
                case '/': // division
                          stack1.push(division(a,b));
                          break;
                case '^': // exponent
                          stack1.push(pow(b,a));
                          break;
            }
        }
    }
    x= stack1.top();

    

    
    return postfix;

}
/**
 * @brief Evaluates the functions specified and returns values to the caller
*/

int addition(int x,int y)
{
    return (x+y);
}
int subtraction(int x,int y)
{
    return (x-y);
}
int multiplication(int x,int y )
{
    return (x*y);
}
int division(int x,int y)
{
    return (x/y);
}


int main()                      //Driver Code
{
    string infix;

    cout << "Enter mathematical Expression: ";
    getline(cin,infix);
    InfixToPostfix p(infix);
    cout << "\nInfix Expression        :" << infix << endl;
    cout << "\nPostfix Expression      : " << p.convertInfixToPostfix() << endl;
    cout << "The sum of postfix expression is: " << x << endl;
}