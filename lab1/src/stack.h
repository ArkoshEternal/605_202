/**
 * @file stack.h
 * @author 
 * @brief Template for a stack, implemented using a dynamic array
 * 
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

template <typename T>
class Stack {
    private:
        int top;
        int cur_size;
        T *stack_array;

    public:
        Stack(); 
        ~Stack();
        bool is_empty();
        int size(); 
        void push(T item);
        T pop();
        T peek();
};

#include "stack.cpp"

#endif // STACK_H
