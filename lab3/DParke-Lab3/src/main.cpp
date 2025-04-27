/**
 * @file main.cpp
 * @author Duncan Parke (dparke2@jh.edu)
 * @brief This is an implementation of a huffman encoding
 * application. It takes in a frequency table and builds a
 * huffman tree to encode and decode messages.
 * 
 * It also takes in a clear text file and output a huffman
 * encoded file, and vice versa for decoding.
 * @version 0.1
 * @date 2025-04-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <fstream>
#include <string> 
#include <unordered_map>
#include "huffman.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <frequency_table> <clear_text> <encoded_output> <decoded_output>" << std::endl;
        return 1;
    }

    std::string freqTablePath = argv[1];
    std::string clearTextPath = argv[2];
    std::string encodedOutputPath = argv[3];
    std::string decodedOutputPath = argv[4];

    // Read the frequency table from the file
    std::ifstream freqFile(freqTablePath);
    if (!freqFile) {
        std::cerr << "Error: Could not open frequency table file." << std::endl;
        return 1;
    }

    std::unordered_map<char, int> frequencyTable;
    char character;
    int frequency;

    while (freqFile >> character) {
        freqFile.ignore(3); // Ignore the " - " part
        freqFile >> frequency;
        frequencyTable[character] = frequency;
    }
    freqFile.close();

    // Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(frequencyTable);

    if (!root) {
        std::cerr << "Error: Failed to build Huffman tree." << std::endl;
        return 1;
    }

    // Print the Huffman tree to standard output
    std::cout << "Huffman Tree:" << std::endl;
    printHuffmanTree(root);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Read the clear text from the file
    std::ifstream clearTextFile(clearTextPath);
    if (!clearTextFile) {
        std::cerr << "Error: Could not open clear text file." << std::endl;
        return 1;
    }

    std::string clearText((std::istreambuf_iterator<char>(clearTextFile)), std::istreambuf_iterator<char>());
    clearTextFile.close();

    // Preprocess the clear text using the frequency table
    clearText = preprocessText(clearText, frequencyTable);

    // Encode the text
    std::string encodedText = encodeText(clearText, huffmanCodes);

    // Print the encoded text to standard output
    std::cout << "Encoded Text:" << std::endl;
    std::cout << encodedText << std::endl;

    // Calculate and display the compression ratio
    size_t originalSize = clearText.size() * 8; // Original size in bits (8 bits per character)
    size_t compressedSize = encodedText.size(); // Compressed size in bits
    double compressionRatio = static_cast<double>(compressedSize) / originalSize;

    std::cout << "Compression Ratio: " << compressionRatio << std::endl;

    // Write the encoded text to the file
    std::ofstream encodedFile(encodedOutputPath);
    if (!encodedFile) {
        std::cerr << "Error: Could not open encoded output file." << std::endl;
        return 1;
    }
    encodedFile << encodedText;
    
    // Echo the frequency table to the encoded output file
    encodedFile << "Frequency Table:" << std::endl;
    for (const auto& pair : frequencyTable) {
        encodedFile << pair.first << " - " << pair.second << std::endl;
    }
    encodedFile << std::endl;

    // Echo the clear text to the encoded output file
    encodedFile << "Clear Text:" << std::endl;
    encodedFile << clearText << std::endl;
    encodedFile << std::endl;

    // Echo the encoded text to the encoded output file
    encodedFile << "Encoded Text:" << std::endl;
    encodedFile << encodedText << std::endl;

    encodedFile.close();

    // Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // Write the decoded text to the file
    std::ofstream decodedFile(decodedOutputPath);
    if (!decodedFile) {
        std::cerr << "Error: Could not open decoded output file." << std::endl;
        return 1;
    }
    
    // Echo the encoded text to the decoded output file
    decodedFile << "Encoded Text:" << std::endl;
    decodedFile << encodedText << std::endl;
    decodedFile << std::endl;

    // Echo the decoded text to the decoded output file
    decodedFile << "Decoded Text:" << std::endl;
    decodedFile << decodedText << std::endl;

    decodedFile.close();

    // Free the Huffman tree memory
    freeHuffmanTree(root);

    return 0;
}
