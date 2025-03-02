/**
 * @file stack.cpp
 * @author Duncan Parker (duncanparker@proton.me)
 * @brief implementation for stack.h
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef STACK_CPP
#define STACK_CPP
#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


// Constructor
template <typename T>
Stack<T>::Stack() { 
    cur_size = 100;
    top = -1;
    stack_array = new T[cur_size];
}

// Destructor
template <typename T>
Stack<T>::~Stack() { 
    delete[] stack_array;
}

// Is Empty
// @brief Check if the stack is empty
// @return true if the stack is empty, false otherwise
template <typename T>
bool Stack<T>::is_empty() { 
    return (top == -1);
}

// Size 
// @brief Get the size of the stack
// @return the size of the stack
template <typename T>
int Stack<T>::size() { 
    return top + 1; 
}

// Push
// @brief Push an item onto the stack
// @param item the item to push
template <typename T>
void Stack<T>::push(T item) { 
    if (top == cur_size - 1) { 
        cur_size *= 2;
        T *new_stack_array = new T[cur_size];
        memcpy(new_stack_array, stack_array, (top + 1) * sizeof(T));
        delete[] stack_array;
        stack_array = new_stack_array;
    }
    stack_array[++top] = item; 
}

// Pop
// @brief Pop an item from the stack
// @return the item popped from the stack
template <typename T>
T Stack<T>::pop(){ 
    if (is_empty()) { 
        std::cout << "stack is empty" << std::endl;
        return T(); // Return default value of T
    }
    return stack_array[top--];
}

// Peek
// @brief Peek at the top item of the stack
// @return the top item of the stack
template <typename T> 
T Stack<T>::peek() { 
    if (is_empty()) { 
        std::cout << "stack is empty" << std::endl;
        return T(); // Return default value of T
    }
    return stack_array[top];
}

#endif // STACK_CPP