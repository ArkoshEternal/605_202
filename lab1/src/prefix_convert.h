/**
 * @file prefix_convert.h
 * @author Duncan Parke (duncanparke@proton.me)
 * @brief Functions to convert prefix expressions to postfix expressions
 * @version 0.1
 * @date 2025-03-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PREFIX_CONVERT_H
#define PREFIX_CONVERT_H
#include "stack.h"
#include <iostream>
#include <string>
// Enum to classify characters
typedef enum { 
    OPERATOR, 
    OPERAND,
    SPACE, 
    INVALID
} char_type_e;  

using namespace std;

// Function to classify characters into operators, operands, and invalid characters
// Returns enum char_type_e which indicates the type of character
char_type_e value_type(string c) { 
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "$") { 
        return OPERATOR;
    } else if (c >= "A" && c <= "Z") { 
        return OPERAND;
    } else if (c == " ") {
        return SPACE;
    } else { 
        return INVALID;
    }
}

// Function to check if a string is a valid prefix expression
// Returns true if valid, false otherwise
// Read more: https://en.wikipedia.org/wiki/Polish_notation
bool is_valid_prefix(string expression) { 
    int operator_count = 0;
    int operand_count = 0;
    // Check if the expression is empty
    if (expression.empty()) { 
        return false;
    }
    else if (value_type(string(1,expression[0])) != OPERATOR && expression.size() != 1) { 
        return false;
    }
    // Check if the expression is a valid prefix expression
    for (int i = 0; i < expression.size(); i++) { 
        char_type_e type = value_type(string(1, expression[i]));
        if (type == OPERATOR) { 
            operator_count++;
        } else if (type == OPERAND) { 
            operand_count++;
        }
        if (type == INVALID) { 
            return false;
        }
    }
    return (operator_count + 1 == operand_count);
}

// Function which converts valid prefix expressions to postfix
// Read More: https://en.wikipedia.org/wiki/reverse_polish_notation
string convert_to_postfix(string line)
{
    Stack<string> u_stack;
    for (int i = line.size() - 1; i >= 0; i--)
    {
        if (value_type(string(1, line[i])) == OPERATOR)
        {
            string op1 = u_stack.pop();
            string op2 = u_stack.pop();
            u_stack.push(op1 + op2 + line[i]);
        }
        else if (value_type(string(1, line[i])) == OPERAND)
        {
            u_stack.push(string(1, line[i]));
        }
    }
    // Write the postfix expression to the file
    return u_stack.pop(); 
}

#endif // PREFIX_CONVERT_H