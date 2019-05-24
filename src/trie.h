#ifndef TRIE_H_
#define TRIE_H_

//struktura wierzcholka drzewa historii
struct TrieNode {
    struct Element* listhead;
    struct TrieNode* children[4];
    struct Element* listequivalent;
};

struct Element* get_list_head(struct TrieNode* node);

void set_list_head(struct TrieNode* node, struct Element* head);

struct TrieNode* get_new_trie_node();

void insert(struct TrieNode* head, char* str);

struct TrieNode* prefix_node(struct TrieNode* node, char* prefix);

struct TrieNode* prefix_node_parent(struct TrieNode* node, char* prefix);

int number_of_child(struct TrieNode* node, char* prefix);

void deletion_helper(struct TrieNode* curr);

void deletion(struct TrieNode* head, char* prefix);

#endif