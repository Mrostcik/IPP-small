#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

//funkcja dodajaca historie do drzewa
void declare_hist(struct TrieNode* root, char* history){
    insert(root, history);
}

//funkcja usuwajaca wszystkie historie o danym prefiksie z drzewa
void remove_hist(struct TrieNode* root, char* history){
    deletion(root, history);
}

//funkcja sprawdzajaca czy dana historia jest w drzewie
int valid_hist(struct TrieNode* root, char* history){
    if(prefix_node(root, history) == NULL) return 0;
    else return 1;
}

//funkcja zwracajaca energie danej historii
unsigned long long energy1_hist(struct TrieNode* root, char* history){
    if(valid_hist(root, history) == 1){
        struct TrieNode* atom = prefix_node(root, history);
        
        return (atom->listhead->energy);
    }
    
    return 0;
}

//funkcja przypisujaca energie klasie abstrakcji odpowiadajacej danej historii
int energy2_hist(struct TrieNode* root, char* history, unsigned long long energ){
    if(valid_hist(root, history) == 1){
        struct TrieNode* atom = prefix_node(root, history);
        atom->listhead->energy = energ;
        return 1;
    }
    
    return 0;
}

//funkcja zrownujaca energie i domykajaca relacje rownowaznosci
//energia 0 odpowiada nieprzypisanej energii
int equal_hist(struct TrieNode* root, char* history_a, char* history_b){
    //obie historie musza istniec
    if(valid_hist(root, history_a) == 1 && valid_hist(root, history_b) == 1){
        struct TrieNode* atom1 = prefix_node(root, history_a);
        struct TrieNode* atom2 = prefix_node(root, history_b);
        
        //jedna z energii rozna od 0 oraz historie sa w roznych klasach abstrakcji
        if((((atom1->listhead->energy) != 0 || (atom2->listhead->energy) != 0))
        && (get_list_head(atom1) != get_list_head(atom2) )){
            unsigned long long mutualen = 0;
            
            //obie energie rozne od 0 - nowa energia rowna sredniej arytmetycznej
            if((atom1->listhead->energy) != 0 && (atom2->listhead->energy) != 0){
                //zapobiegamy przekroczeniu limitu unsigned long long najpierw dzielac
                mutualen = ((atom1->listhead->energy)/2 + (atom2->listhead->energy)/2);
                if(((atom1->listhead->energy))%2==1 && ((atom2->listhead->energy))%2==1)
                    mutualen++;
            }
            //jedna z energii rozna od 0 - nowa energia rowna tej niezerowej
            else
                mutualen = ((atom1->listhead->energy) + (atom2->listhead->energy));
            
            struct Element* head1 = get_list_head(atom1);
            struct Element* head2 = get_list_head(atom2);
            
            //dopinamy krotsza liste do dluzszej - amortyzujemy koszty czasowe
            if(atom1->listhead->length > atom2->listhead->length)
                through_list(head2, mutualen, head1);
            else
                through_list(head1, mutualen, head2);
        
            return 1;
        }
        //obie historie byly juz w tej samej klasie abstrakcji - nie zmieniamy nic
        else if(get_list_head(atom1) == get_list_head(atom2))
            return 1;
    }
    
    return 0;
}

