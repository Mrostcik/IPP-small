#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "atom.h"
#include "trie.h"

//funkcja, wczytujaca 1 wiersz wejscia
char* input_line(char* str, bool *end){
    int character;
    size_t size = 0, length = 0;
    
    //wczytywanie napisu do konca linii, stopniowo relokujac pamiec
    while((character=getchar()) != EOF && character != '\n'){
        if (length+1 >= size)
        {
            size = size*2+1;
            
            str = realloc(str, sizeof(char)*size);
            //relokacja nieudana
            if(str == NULL)
                exit(1);
        }
        str[length++] = character;
    }
    
    //ew. relokacja pamieci i dodanie znaku konca napisu
    if (length+1 >= size){
        size++;
        
        str = realloc(str, sizeof(char)*size);
        //relokacja nieudana
        if(str == NULL)
            exit(1);
    }
    str[length] = '\0';
    
    //sprawdzamy, czy jest kolejny wiersz wejscia
    if(character == '\n')
        *end = 1;
    
    return str;
}

//funkcja, wywolujaca instrukcje odpowiadajaca danemu wierszowi wejscia
void input_distribution(struct TrieNode* root, char* str){
    char* word1 = NULL;
    char* word2 = NULL;
    char* word3 = NULL;
    size_t size1 = 0, size2 = 0, size3 = 0;
    int error = 0, ishistory = 1;
    
    //ignorujemy,jesli wiersz zaczyna sie # lub jest pusty
    if(*str == 35 || strlen(str) == 0 )
        return;
    
    //dzielimy wiersz na 3 slowa - instrukcje, parametr1, parametr2
    //przy okazji sprawdzamy poprawnosc wejscia 
    while(*str){
        //wiersz ma zaczynac sie wielka litera
        if(*str<'A' || *str>'Z'){
            error = 1;
            break;
        }
        
        //tworzymy pierwsze slowo - instrukcje
        while(*str >= 'A' && *str <= 'Z'){
            size1++;
            
            word1 = realloc(word1, sizeof(char)*size1);
            //relokacja nieudana
            if(word1 == NULL)
                exit(1);
            
            word1[size1-1] = *str;
            str++;
        }
        
        //konczymy pierwsze slowo znakiem konca napisu
        word1 = realloc(word1, sizeof(char)*(size1+1));
        if(word1 == NULL)
                exit(1);
        word1[size1] = '\0';
        
        //po instrukcji ma byc spacja
        if(*str == 32)str++;
        else{
            error = 1;
            break;
        }
        
        //historia musi sie zaczynac od cyfry z przedzialu 0-3
        if(*str < '0' || *str > '3'){
            error = 1;
            break;
        }
        
        //tworzymy drugie slowo - historie
        while(*str >= '0' && *str <= '3'){
            size2++;
            
            word2 = realloc(word2, sizeof(char)*size2);
            //relokacja nieudana
            if(word2 == NULL)
                exit(1);
            
            word2[size2-1] = *str;
            str++;
        }
        
        //konczymy drugie slowo znakiem konca napisu
        word2 = realloc(word2, sizeof(char)*(size2+1));
        if(word2 == NULL)
                exit(1);
        word2[size2] = '\0';
       
        //czy instrukcja jednoparametrowa
        if(strlen(str) == 0)break;
        
        //po slowie ma byc spacja
        if(*str == 32)str++;
        else{
            error = 1;
            break;
        }
        
        //historia lub energia - musi sie zaczynac od cyfry
        if(*str<'0' || *str>'9'){
            error = 1;
            break;
        }
        
        //jesli instrukcja to dwuparametrowe ENERGY to
        //ignorujemy wiodace zera
        if(strcmp(word1, "ENERGY") == 0){
            while(*str == '0' )
                str++;
        }
        
        //tworzymy trzecie slowo - historie lub energie
        while(*str >= '0' && *str <= '9'){
            //czy istnieje mozliwosc ze slowo jest historia
            if(*str >= '4')
                ishistory = 0;
            
            size3++;
            
            word3 = realloc(word3, sizeof(char)*size3);
            //relokacja nieudana
            if(word3 == NULL)
                exit(1);
            
            word3[size3-1] = *str;
            str++;
        }
        
        //konczymy trzecie slowo znakiem konca napisu
        word3 = realloc(word3, sizeof(char)*(size3+1));
        if(word3 == NULL)
                exit(1);
        word3[size3] = '\0';
        
        //musielismy przejsc juz caly wiersz
        if(strlen(str) == 0)break;
        else {
            error = 1;
            break;
        }
    }
    
    unsigned long long e = 0;
    
    //jesli instrukcja to dwuparametrowe ENERGY to
    //zamieniamy 3 slowo na energie
    if(word3 != NULL){
        if(strcmp(word1, "ENERGY") == 0){
            //energia musi byc z przedzialu 1 - 2^64-1
            if(strlen(word3) <= 19 )
                e = strtoull(word3, NULL, 10);
            else if(strlen(word3) == 20){
                char* word4 = "18446744073709551615";
                int i = 0;
                while(word3[i] >= word4[i] && i < 20){
                    if(word3[i] > word4[i])
                        error = 1;
                i++;
                }
                
            //nie wykroczylismy poza przedzial
            //konwertujemy do unsigned long long
            if(error == 0){
                e = strtoull(word3, NULL, 10);  
            }
            }
            else
                error = 1;
        }
    }
    
    //wiersz przeszedl wstepna kontrole poprawnosci
    if(error == 0) {
        //instrukcje jednoparametrowe
        if(word2 != NULL && word3 == NULL){
            if(strlen(word2) != 0){
                if(strcmp(word1, "DECLARE") == 0){
                    declare_hist(root, word2);   
                    printf("%s\n", "OK");
                }
                else if(strcmp(word1, "REMOVE") == 0){
                    remove_hist(root, word2);    
                    printf("%s\n", "OK");
                }
                else if(strcmp(word1, "VALID") == 0){
                    if(valid_hist(root, word2) == 0)
                        printf("%s\n", "NO");
                    else
                        printf("%s\n", "YES");
                }
                else if(strcmp(word1, "ENERGY") == 0){
                    unsigned long long i = energy1_hist(root, word2);
                    if(i == 0)
                        error = 1;
                    else
                        printf("%llu\n", i );
                }
                else
                    error = 1;
            }
            else
                error = 1;
        }
        //instrukcje dwuparametrowe
        else if(word2 != NULL && word3 != NULL){
            if(strlen(word2) != 0 && strlen(word3) != 0){
                if(strcmp(word1, "ENERGY") == 0){
                    if(energy2_hist(root, word2, e) == 0)
                        error = 1;
                    else
                        printf("%s\n", "OK");
                }
                else if(strcmp(word1, "EQUAL") == 0 && ishistory == 1 ){
                    if(equal_hist(root, word2, word3) == 0)
                        error = 1;
                    else
                        printf("%s\n", "OK");
                }
                else
                    error = 1;
        }
            else
                error = 1;
        }
        else
            error = 1;
    }
    
    free(word1);
    free(word2);
    free(word3);
    
    //niepoprawny wiersz wejscia
    if(error == 1)
        fprintf(stderr, "%s\n", "ERROR");
}

