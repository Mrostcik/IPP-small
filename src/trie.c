#include <stdio.h>
#include <stdlib.h>
#include "twowaylist.h"


struct Element* get_list_head(struct TrieNode* node){
    return (node->listhead);
}

void set_list_head(struct TrieNode* node, struct Element* head){
    node->listhead = head;
}

//funkcja alokujaca nowy wierzcholek drzewa
struct TrieNode* get_new_trie_node() {
    struct TrieNode* root = 
                (struct TrieNode*)malloc(sizeof(struct TrieNode));
    //alokacja nieudana            
    if(root == NULL)
        exit(1);
    
    //kazdy wierzcholek ma odpowiadajaca mu liste - klase abstrakcji od equal
    //lista ta ma stala glowe, ktora nie odpowiada zadnemu wierzcholkowi
    //jest ona tak jakby reprezentantem danej listy
    //sluzy ona do trzymania energii i dlugosci danej listy
    //pozostale elementy odpowiadaja juz jakims wierzcholkom drzewa - historiom
    struct Element* head = get_new_element(NULL);
    struct Element* element = get_new_element(root);
    
    //poczatkowo lista odpowiadajaca wierzcholkowi sklada sie z
    //stalej glowy oraz elementu odpowiadajacemu wierzcholkowi
    head->next = element;
    element->prev = head;
    root->listhead = head;
    root->listequivalent = element;
    
    for (int i=0;i<4;i++)
        root->children[i] = NULL;
    
    return root;
}

//funkcja dodajaca slowo - historie do drzewa
//zgodnie z zasadami drzewa Trie tzn.
//np. slowo 012 odpowiada korzen->children[0]->children[1]->children[2]
void insert(struct TrieNode* head, char* str){
    while(*str){
        if(head->children[*str - '0'] == NULL){
            head->children[*str - '0'] = get_new_trie_node();
        }
        
        head = head->children[*str - '0'];
        str++;
    }
}

//funkcja wyszukujaca podany prefix - historie w drzewie
struct TrieNode* prefix_node(struct TrieNode* node, char* prefix){
    while(*prefix){
        if((node->children[*prefix - '0'] != NULL)){
            node = node->children[*prefix - '0'];
        }
        else
            return NULL;
        
        prefix++;
    }
    return node;
}

//funkcja wyszukujaca ojca podanego prefixa - histori
struct TrieNode* prefix_node_parent(struct TrieNode* node, char* prefix){
    struct TrieNode* node2 = NULL;
    
    while(*prefix){
        if((node->children[*prefix - '0'] != NULL)){
            node2 = node;
            node = node->children[*prefix - '0'];
        }
        else
            return NULL;
        
        prefix++;
    }
    
    return node2;
}

//funkcja zwracajaca, ktorym numerem dziecka jest
//dana historia dla ojca tzn. gdy istnieje historia
//zwraca ostatnia jej cyfre
int number_of_child(struct TrieNode* node, char* prefix){
    int seek = 0;
    
    while(*prefix){
        if((node->children[*prefix - '0'] != NULL)){
            node = node->children[*prefix - '0'];
        }
        else
            return -1;
        seek = *prefix - '0';
        prefix++;
    }
    
    return seek;
}

//funkcja rekurencyjnie usuwajaca cale poddrzewo o korzeniu
//w danym wierzcholku oraz odpowiadajace elementy listy
void deletion_helper(struct TrieNode* curr){
    for(int i=0;i<4;i++){
        if(curr->children[i]){
            struct TrieNode* node = curr->children[i];
            curr->children[i] = NULL;
            deletion_helper(node);
        }
    }
    struct Element* needed = curr->listequivalent;
    curr->listequivalent = NULL;
    delete_element(needed);
    free(curr);
}

//funkcja usuwajaca wskaznik ojca na usuwany korzen poddrzewa
//oraz wywolujaca deletion_helper w celu usuniecia calego poddrzewa
void deletion(struct TrieNode* head, char* prefix){
    struct TrieNode* curr = prefix_node(head, prefix);
    struct TrieNode* parent = prefix_node_parent(head, prefix);
    int numb = number_of_child(head, prefix);
    
    if(parent != NULL)
        parent->children[numb] = NULL;
    if (curr == NULL)
        return;
    else
        deletion_helper(curr);
    
    return;
}
