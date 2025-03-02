/**
 * @file main.cpp
 * @author Duncan Parke (duncanparke@proton.me)
 * @brief Program which takes in a file containing 
 * prefix expressions and converts it to postfix
 * expressions, as output.txt
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
#include <fstream>
#include <cstdlib>
#include "prefix_convert.h"


// Program entry point
int main(int argc, char *argv[]) { 
    // Handle CLI
    if (argc != 3) { 
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Open the file as read
    ifstream file(argv[1]);
    if (!file.is_open()) { 
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    // open and clear the output file
    ofstream outfile(argv[2]);
    if (!outfile.is_open()) { 
        cout << "Error opening output file: " << argv[2] << endl;
        return 1;
    }
    outfile.clear();
    // convert if valid
    string line;
    outfile << "Prefix expressions:" << endl;
    outfile << "---------------------" << endl;
    while (getline(file, line)) { 
        outfile << line << endl;
    }
    // reset file to beginning
    file.clear();
    file.seekg(0, ios::beg);
    // convert to postfix and output
    outfile << "Postfix expressions:" << endl;
    outfile << "---------------------" << endl;
    while (getline(file, line)) { 
        // Check if the line is a valid prefix expression
        if (!is_valid_prefix(line)) { 
            outfile << "Invalid prefix expression" << endl;
            continue;
        }
        // clean up the line    
        outfile << convert_to_postfix(line) << endl; 
    }
    // Copy the output to the original file
    file.close();
    outfile.close();
}

