# Duncan Parke 
# Test script for lab one
import os
import random
import string

def generate_prefix_expression(depth = 3, valid = True): 
    ''' recursive function to generate a prefix expression '''
    if valid == False: 
        # Generate a random string of letters
        while True: 
            operand_cnt = 0
            operator_cnt = 0
            string_length = random.randint(1, 10)
            candidate = ''.join(random.choices(string.ascii_uppercase + string.ascii_lowercase + string.digits + '*$+-%"#,/ ;!=', k=string_length))
            for s in candidate: 
                if s not in string.ascii_uppercase + '+-*/$': 
                    return candidate
                elif s in string.ascii_uppercase: 
                    operand_cnt += 1
                elif s in '+-*/$':
                    operator_cnt += 1
            
            if not operand_cnt == operator_cnt+1:  
                return candidate
            
    if depth == 0 or random.random() > 0.7:  
        return str(random.choice(string.ascii_uppercase))
    
    operator = random.choice(['+', '-', '*', '/', "$"])
    left = generate_prefix_expression(depth - 1)
    right = generate_prefix_expression(depth - 1) 
    return f"{operator}{left}{right}"

def write_to_file(filename, content):
    with open(filename, 'w') as file:
        file.write(content)

# Predictive model sourced from here; https://www.geeksforgeeks.org/prefix-postfix-conversion/
def convert_prefix_to_postfix(s):
    ''' Convert a prefix expression to postfix expression '''
    stack = []
    operators = set(['+', '-', '*', '/', "$"])
    s = s[::-1]
    # iterating through individual tokens
    for i in s:

        # if token is operator
        if i in operators:

            # pop 2 elements from stack
            a = stack.pop()
            b = stack.pop()

            # concatenate them as operand1 +
            # operand2 + operator
            temp = a+b+i
            stack.append(temp)

            # else if operand
        else:
            stack.append(i)
    return stack[-1]

def run_tests():

    # Generate 20 valid or invalid prefix expressions
    test_strings = []
    for i in range(20):
        my_valid = random.choice([True, False])
        test_strings.append([generate_prefix_expression(3, my_valid), my_valid])

    # Write the test strings to a file
    print(test_strings)
    write_to_file(f"{os.getcwd()}/../src/test.txt", "\n".join([f"{s[0]}" for s in test_strings]))

    # Generate expected output: 
    expected_strings = []
    for pair in test_strings: 
        if pair[1]:
            # Valid prefix expression
            expected_strings.append(f"{convert_prefix_to_postfix(pair[0])}\n")
        else:
            expected_strings.append("Invalid prefix expression\n")

    # Run the a.out executable
    # Ensure the executable is built and ready to run
    os.system(f"cd {os.getcwd()}/../src; pwd; make clean; make run")

    # Check the output against the expected model
    with open(f"{os.getcwd()}/../src/output.txt", 'r') as file:
        output = file.readlines()

    # get last 20 lines of output
    output = output[-20:]

    for i in range(len(test_strings)):

        if test_strings[i][1]:
            # Valid prefix expression
            assert output[i] == expected_strings[i], f"Test failed for valid prefix expression: {test_strings[i][0]}. Expected: {expected_strings[i]}, Got: {output[i]}"
        else:
            # Invalid prefix expression
            assert output[i] == expected_strings[i], f"Test failed for invalid prefix expression: {test_strings[i][0]}. Expected: {expected_strings[i]}, Got: {output[i]}"
    print("All tests passed!")


if __name__ == "__main__":
    run_tests()