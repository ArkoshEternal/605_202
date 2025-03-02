#ifndef TEST_STACK_CPP
#define TEST_STACK_CPP

#include "stack.h"
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;
//
// Test the Stack class
void test_stack() {
    // Test constructor
    Stack<int> stack;
    assert(stack.is_empty());
    assert(stack.size() == 0);

    // Test push
    for (int i = 0; i < 10; i++) {
        stack.push(i);
        assert(!stack.is_empty());
        assert(stack.size() == i + 1);
    }

    // Test peek
    for (int i = 9; i >= 0; i--) {
        assert(stack.peek() == i);
        stack.pop();
    }

    // Test pop
    for (int i = 9; i >= 0; i--) {
        stack.push(i);
        assert(stack.pop() == i);
    }

    // Test is_empty
    assert(stack.is_empty());

    cout << "All tests passed!" << endl;
}

int main() {
    test_stack();
    return 0;
}
#endif // TEST_STACK_CPP