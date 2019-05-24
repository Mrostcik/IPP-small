#ifndef TWOWAYLIST_H_
#define TWOWAYLIST_H_

//struktura elementu listy
struct Element {
    struct TrieNode* node;
    unsigned long long energy;
    struct Element* next;
    struct Element* prev;
    unsigned long long length;
};

struct Element* get_new_element(struct TrieNode* x);

void through_list(struct Element* head2, unsigned long long energ, struct Element* head);

void delete_element(struct Element* element);
#endif