/**
 * @file prefix_convert.h
 * @author Duncan Parke (duncanparke@proton.me)
 * @brief Functions to convert prefix expressions 
 *        recursively to postfix
 * @version 0.1
 * @date 2025-03-15
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PREFIX_CONVERT_H
#define PREFIX_CONVERT_H
#include <iostream>
#include <string>

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

// Recursive helper function to help with converting from prefix 
// to postfix

string converter_helper(istringstream &input) {
    char c; 
    if(!(input >> c)) { 
        return ""; // Return empty string if no more input
    }

    if (value_type(string(1,c)) == OPERATOR) { 
        // If the character is an operator, recursively get the left and right operands
        string left_operand = converter_helper(input);
        string right_operand = converter_helper(input);
        // Return the postfix expression
        return left_operand + right_operand + string(1,c);
    } 
    return string(1,c); 
}
// Recursive function which converts valid prefix expression to postfix
// Read More: https://en.wikipedia.org/wiki/reverse_polish_notation
string convert_to_postfix_recursive(const string &line)
{  
    istringstream iss(line);
    return converter_helper(iss);
}
#endif // PREFIX_CONVERT_H