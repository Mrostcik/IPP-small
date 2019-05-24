#ifndef INPUT_H_
#define INPUT_H_
#include "trie.h"

char* input_line(char* str, bool *end);

void input_distribution(struct TrieNode* root, char* str);

#endif