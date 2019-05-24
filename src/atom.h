#ifndef ATOM_H_
#define ATOM_H_
#include "trie.h"

void declare_hist(struct TrieNode* root, char* history);

void remove_hist(struct TrieNode* root, char* history);

int valid_hist(struct TrieNode* root, char* history);

unsigned long long energy1_hist(struct TrieNode* root, char* history);

int energy2_hist(struct TrieNode* root, char* history, unsigned long long energ);

int equal_hist(struct TrieNode* root, char* history_a, char* history_b);

#endif