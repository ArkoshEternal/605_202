/**
 * @file main.cpp
 * @author Duncan Parke (duncanparke@proton.me)
 * @brief Implementation of a prefix post expression converter
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "stack.h"

using namespace std;

bool is_operator(string string) { 
    return (string == "+" || string == "-" || string == "*" || string == "/" || string == "$");
}

bool is_alpha(string string) { 
    return (string[0] >= 'a' && string[0] <= 'z') || (string[0] >= 'A' && string[0] <= 'Z');
}

// Program entry point
int main() { 
    // Initialize Stack 
    Stack<string> u_stack; 

    // Initialize variables
    string expression;
    // Get user input
    cout << "Enter a prefix expression: ";
    cin >> expression;
    // Parse the expression into chars
    // Perform conversion
    for (int i = expression.size() - 1; i >= 0; i--) {
        // If operator, have to pop twice from stack
        string temp = "";
        if (is_operator(string(1, expression[i]))) {
            temp += u_stack.pop();
            temp += u_stack.pop();
            temp += expression[i];
            u_stack.push(temp);
        } 
        else if (is_alpha(string(1, expression[i]))) {
            u_stack.push(string(1, expression[i]));
        }
        else if (expression[i] == ' ') {
            continue;
        }
        else { 
            cout << "Invalid character Detected. Try again" << endl;
            return 1;
        }
    }
    cout << "Postfix expression: " << u_stack.pop() << endl;
    return 0;
}