#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "atom.h"
#include "trie.h"

int main(){
    //korzen drzewa historii
    struct TrieNode* root = get_new_trie_node();
    
    while(1){
        //wczytujemy po linii wejscia, dopoki plik sie nie skonczy
        char* input = NULL;
        bool end = 0;
        input = input_line(input, &end);
        
        //plik sie skonczyl - koniec wejscia
        if(strlen(input) == 0 && end == 0) {
            free(input);
            break;
        }
        
        //wywolujemy funkcje odpowiadajaca instrukcji z wejscia
        input_distribution(root, input);
        
        free(input);
            
    }
    
    //usuwamy cale drzewo z pamieci
    deletion(root, "");
    
    return 0;
}
