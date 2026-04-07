#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>    
#include <stdlib.h>   
#include "GenericStack.h"

using namespace std;

// Returns true if token is one of the basic arithmetic operators.
bool isOperator(const string &token) 
{
    return token == "+" || token == "-" || token == "*" || token == "/";
    // Checks if the token is "+", "-", "*" or "/".
}

// Returns the precedence of an operator.
// Higher value means higher precedence.
int precedence(const string &op) 
{
    if(op == "+" || op == "-")
        return 1;
    if(op == "*" || op == "/")
        return 2;
    return 0;
    // Returns an integer representing operator precedence.
}

// Converts an infix expression (with space-separated tokens) to postfix notation.
// Uses a GenericStack to temporarily hold operators.
string infixToPostfix(const string &infix) 
{
    istringstream iss(infix);  // Create an input stream from the infix expression.
    string token, output;      // 'token' holds the current token; 'output' accumulates the postfix expression.
    GenericStack<string> opStack;  // Stack to hold operators.

    while (iss >> token) 
    {     // Process each token.
        if (token == "(") 
        {
            opStack.push(token);  // Push left parenthesis onto the stack.
        }
        else if (token == ")") 
        {
            // Pop and output operators until a left parenthesis is encountered.
            while (!opStack.empty() && opStack.top() != "(") 
            {
                output += opStack.top() + " ";
                opStack.pop();
            }
            if (!opStack.empty())
                opStack.pop();   // Discard the left parenthesis.
        } 
        else if (isOperator(token)) 
        {
            // For an operator, pop from the stack any operator with higher or equal precedence.
            while (!opStack.empty() && isOperator(opStack.top()) &&
                   precedence(opStack.top()) >= precedence(token)) 
            {
                output += opStack.top() + " ";
                opStack.pop();
            }
            opStack.push(token);  // Push the current operator.
        } 
        else 
        {
            // Token is assumed to be an operand (number or variable name).
            output += token + " ";
        }
    }
    // Pop any remaining operators from the stack.
    while (!opStack.empty()) 
    {
        output += opStack.top() + " ";
        opStack.pop();
    }
    return output;  // Return the postfix expression.
}

// Returns true if the string s represents a number (integer or floating-point).
bool isNumber(const string &s) 
{
    if(s.empty())
        return false;
    // Check if the first character is a digit or a sign followed by a digit.
    if(isdigit(s[0]) || ((s[0] == '-' || s[0] == '+') && s.size() > 1 && isdigit(s[1])))
        return true;
    return false;
    // Determines whether the token is numeric.
}

// Evaluates a postfix expression (space-separated tokens) assuming all operands are numeric.
// Uses a GenericStack of doubles for computation.
double evaluatePostfix(const string &postfix) 
{
    istringstream iss(postfix);      // Create an input stream from the postfix expression.
    string token;
    GenericStack<double> numStack;   // Stack for numeric operands.
    while (iss >> token) 
    {
        if (isNumber(token)) 
        {
            // Convert token to double using atof (from stdlib.h) and push it.
            numStack.push(atof(token.c_str()));
        } 
        else if (isOperator(token)) 
        {
            // Pop two numbers, apply the operator, and push the result.
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            if (token == "+")
                numStack.push(a + b);
            else if (token == "-")
                numStack.push(a - b);
            else if (token == "*")
                numStack.push(a * b);
            else if (token == "/")
                numStack.push(a / b);
        }
    }
    return numStack.top();  // The remaining number is the result.
}

int main() 
{
    cout << "Enter infix expressions (space-separated tokens). Ctrl+D (or Ctrl+Z on Windows) to exit." << endl;
    string infix;
    // Continuously prompt the user for infix expressions until end-of-file is reached.
    while (getline(cin, infix)) 
    {
        if (infix.empty())
            continue;  // Skip empty lines.
        
        // Convert the infix expression to postfix notation.
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;

        // Determine if the expression has only numeric operands.
        istringstream iss(infix);
        string token;
        bool allNumeric = true;
        while (iss >> token) 
        {
            if (!isOperator(token) && token != "(" && token != ")" && !isNumber(token)) 
            {
                allNumeric = false;
                break;
            }
        }
        // If all tokens are numeric, evaluate the postfix expression.
        if(allNumeric) 
        {
            double result = evaluatePostfix(postfix);
            cout << "Evaluated result: " << result << endl;
        } 
        else 
        {
            cout << "Expression contains variables; evaluation skipped." << endl;
        }
        cout << "\nEnter next infix expression:" << endl;  // Re-prompt the user.
    }
    return 0;
}