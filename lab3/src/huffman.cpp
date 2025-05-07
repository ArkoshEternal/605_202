/**
 * @file huffman.cpp
 * @brief Implementation of Huffman encoding and decoding functions.
 */

#include "huffman.h"
#include <queue>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <functional>

// Comparator for the priority queue
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function that removes non-alpha chars per 4/14 email and converts to upper case
std::string preprocessText(const std::string& text, const std::unordered_map<char, int>& frequencyTable) {
    std::string processedText;
    for (char ch : text) {
        char upperCh = std::toupper(ch);
        if (frequencyTable.find(upperCh) != frequencyTable.end()) {
            processedText += upperCh;
        }
    }
    return processedText;
}

HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencyTable) {
    if (frequencyTable.empty()) {
        std::cerr << "Error Reading Frequency Table" << std::endl;
        return nullptr;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;

    for (const auto& pair : frequencyTable) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.empty() ? nullptr : pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

std::string encodeText(const std::string& text, const std::unordered_map<char, std::string>& huffmanCodes) {
    std::string encodedText;
    for (char ch : text) {
        encodedText += huffmanCodes.at(ch);
    }
    return encodedText;
}

std::string decodeText(const std::string& encodedText, HuffmanNode* root) {
    if (!root) {
        std::cerr << "Error: Huffman tree is null." << std::endl;
        return "";
    }

    std::string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            std::cerr << "Error: Invalid bit in encoded text." << std::endl;
            return "";
        }

        if (!current) {
            std::cerr << "Error: Traversal reached a null node." << std::endl;
            return "";
        }

        if (!current->left && !current->right) {
            decodedText += current->character;
            current = root;
        }
    }

    return decodedText;
}

void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return;

    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);

    delete root;
}

void printHuffmanTree(HuffmanNode* root, const std::string& prefix, bool isLeft, const std::string& edgeLabel) {
    if (root) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // Print the edge label (0 or 1)
        if (!edgeLabel.empty()) {
            std::cout << "(" << edgeLabel << ") ";
        }

        // Print the character and frequency
        if (root->character == '\0') {
            std::string subtreeCharacters;
            std::function<void(HuffmanNode*)> collectCharacters = [&](HuffmanNode* node) {
                if (!node) return;
                if (node->character != '\0') subtreeCharacters += node->character;
                collectCharacters(node->left);
                collectCharacters(node->right);
            };
            collectCharacters(root);

            std::cout << "[" << subtreeCharacters << ": " << root->frequency << "]";
        } else {
            std::cout << "[" << root->character << ": " << root->frequency << "]";
        }
        std::cout << std::endl;

        // Recur for left and right subtrees with edge labels
        printHuffmanTree(root->left, prefix + (isLeft ? "│   " : "    "), true, "0");
        printHuffmanTree(root->right, prefix + (isLeft ? "│   " : "    "), false, "1");
    }
}