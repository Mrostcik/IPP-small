#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

//funkcja alokujaca nowy element listy odpowiadajacy
//jakiemus wierzcholkowi drzewa 
struct Element* get_new_element(struct TrieNode* x) {
    struct Element* newElement 
                = (struct Element*)malloc(sizeof(struct Element));
    //alokacja nieudana
    if(newElement == NULL)
        exit(1);
    
    //ustawiamy wskaznik na odpowiadacy wierzcholek
    //energy i length maja znaczenie tylko w stalej glowie listy
    newElement->node = x;
    newElement->prev = NULL;
    newElement->next = NULL;
    newElement->energy = 0;
    newElement->length = 1;
    
    return newElement;
}

//funkcja przechodzaca liste i dopinajaca ja do innej listy 
void through_list(struct Element* head2, unsigned long long energ, struct Element* head){
    struct Element* helper = head2->next;
    struct Element* helper2 = head->next;
    
    //przepinamy glowe dluzszej listy na glowe krotszej listy
    head->next = helper;
    //zmieniamy dlugosc listy i energie
    head->length += head2->length;
    head->energy = energ;
    //pierwszy element krotszej listy przepinamy na glowe dluzszej listy
    helper->prev = head;
    
    //przechodzimy krotsza liste
    do{
        //ustawiamy glowe na glowe dluzszej listy
        set_list_head(helper->node, head);
           
        if(helper->next != NULL)       
            helper = helper->next;
        else
            break;
    }while(helper != NULL);
    
    //przepinamy, aby ostatni element krotszej listy i
    //pierwszy dluzszej wskazywaly na siebie
    helper->next = helper2;
    helper2->prev = helper;
    free(head2);
}

//funkcja usuwajaca element listy;
void delete_element(struct Element* element){
    //odpinamy i przepinamy wskazniki
    if(element->prev != NULL){
        if(element->next != NULL)
            element->prev->next = element->next;
        else
            element->prev->next = NULL;
        
    }
    if(element->next != NULL){
        if(element->prev != NULL)
            element->next->prev = element->prev;
        else
            element->next->prev = NULL;
    }
    
    //dlugosc listy zmniejsza sie o 1
    element->node->listhead->length -= 1;
    
    //jezeli lista ma dlugosc 0 to znaczy ze ostala sie tylko
    //stala glowa, wiec ja usuwamy
    if(element->node->listhead->length == 0){
        free(element->node->listhead);
    }
    free(element);
}