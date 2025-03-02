# Analysis

> Duncan Parke

My implementation of lab one handles converting prefix to postfix by using a stack data structure, which is necessary to implement the stack-based algorithm of reverse iterating through the input string, popping two operands off the stack when encountering an operator, and pushing all operands
it runs into onto the stack for later popping off.

The stack is implemented using a dynamically sized array, which is initialized to a fixed length, and then doubled whenever it breaches the allocated memory. This implementation is useful because it is has a very efficient pop and push function, which is 0(1) assuming we keep track of the head pointer of the stack. It is suboptimal for memory utilization, as the memory allocated will stay allocated until the end of the program, no matter how much the stack shrinks. However, the efficiency of the pop/push functions make it a good implementation, and saves us the allocation cost on the pop and push functions.

For the design, I stuck with the relatively simple approach to take in the input, check the expressions to determine if it is a valid prefix expression (one less operator than number of operands, begins with an operator unless a single character), and if so, run the algorithm described above against it.

Because of the requirements to echo the input before the output, I just dump the input file into the output file, and then run the simple approach described above to output corresponding either error messages or postfix functions.

In my implementation, we have to iterate through the string twice: once to determine if it is a valid string, and again if it is a valid string to convert to postfix. If it goes to postfix, its another o(n), where n is the length of the string.

Thus, we'll have an o(n*m), where n is the number of strings input and m is the average length of the strings input.

I think I handled errors pretty well, especially any errors with opening up the files. I did end up implementing a pretty robust checking function in python, which I ended up regretting just because it took a while to get non-valid prefix expressions working because of a small error I overlooked building my scripting files. However, now that I have the test framework built out, I can pretty much just reuse it in future assignments to robust error checking.

As far as above and beyond, I think my documentation is very clean and readable. I also believe my test mechanism would be classified under enhancements, but I might be wrong. You can run it from the test directory, on pretty much any linux based system. I haven't tested it on mac or windows operating systems.
