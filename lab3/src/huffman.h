/**
 * @file huffman.h
 * @brief Header file for Huffman encoding and decoding.
 * 
 * This file contains the declarations for the Huffman encoding and decoding
 * functions, as well as the data structures used to build the Huffman tree.
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <vector>

// Node structure for the Huffman tree
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencyTable);

// Function to generate the Huffman codes
void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes);

// Function to encode a given text using Huffman codes
std::string encodeText(const std::string& text, const std::unordered_map<char, std::string>& huffmanCodes);

// Function to decode a Huffman-encoded string
std::string decodeText(const std::string& encodedText, HuffmanNode* root);

// Function to preprocess text before encoding
std::string preprocessText(const std::string& text, const std::unordered_map<char, int>& frequencyTable);

// Function to free the memory allocated for the Huffman tree
void freeHuffmanTree(HuffmanNode* root);

// Function to print out the Huffman tree: 
// Must use preorder traversal p4 of spec
void printHuffmanTree(HuffmanNode* root, const std::string& prefix = "", bool isLeft = true, const std::string& edgeLabel = "");

#endif // HUFFMAN_H