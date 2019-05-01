// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.
// Version 1.1.0: Moved destroy_pokedex function to correct location.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.
//
// But note you are not permitted to use functions from string.h
// so do not #include <string.h>

#include "pokedex.h"


// Add your own #defines here.


// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *select;
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;
    struct pokenode *evolution;
    Pokemon         pokemon;
    int             found;    
};

// Add any other structs you define here.


// Add prototypes for any extra functions you create here.
static int strLength (char *name);
static void unknownName(int strLength);
static void destroy_node(struct pokenode *n);
static void print_evolution(struct pokenode *curr);
static void print_unknown_evolution(struct pokenode *curr);


// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);    
    // add your own code here
    new_pokedex->head = NULL;
    new_pokedex->select = NULL;
    return new_pokedex;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *curr = pokedex->head;
    if (pokedex->head == NULL) {
        curr = malloc(sizeof(struct pokenode));
        pokedex->head = curr;
        curr->pokemon = pokemon;
        curr->next = NULL;
        curr->prev = NULL;
        curr->evolution = NULL;
        pokedex->select = pokedex->head;
        //initializes the field found
        curr->found = 0;       
    }
    else { 
        while (curr->next != NULL) {
            curr = curr->next;
        }
        struct pokenode *latest = curr->next;
        latest = malloc(sizeof(struct pokenode));
        curr->next = latest;
        latest->next = NULL;
        latest->prev = curr;
        latest->evolution = NULL;
        latest->pokemon = pokemon;
        latest->found = 0;
    }
}    
    


void detail_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        return;
    }      
    if (curr->found != 1) {
        printf("Id: %03d\n", pokemon_id(curr->pokemon));
        printf("Name: ");
        unknownName(strLength(pokemon_name(curr->pokemon)));
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: --\n");
    }
    else {
        printf("Id: %03d\n", pokemon_id(curr->pokemon));
        printf("Name: %s\n", pokemon_name(curr->pokemon));
        printf("Height: %.1lfm\n", pokemon_height(curr->pokemon));
        printf("Weight: %.1lfkg\n", pokemon_weight(curr->pokemon));
        printf("Type: %s ", pokemon_type_to_string(pokemon_first_type(curr->pokemon)));
        if (pokemon_second_type(curr->pokemon) != NONE_TYPE) {
            printf("%s", pokemon_type_to_string(pokemon_second_type(curr->pokemon)));
        }
        printf("\n");
    }   
}

Pokemon get_current_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        fprintf(stderr, "Pokedex is empty\n");
        exit(1);
    }
    
    return curr->pokemon;
    
}
//changes the field found to 1 to mark it is found
void find_current_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        return;
    }
    curr->found =  1;
}

void print_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    if (curr == NULL) {
        return;
    }
    
    while (curr != NULL) {
        
        if (curr == pokedex->select) {
            printf("--> ");
            printf("#%03d: ", pokemon_id(curr->pokemon));
        }
        else {
            printf("    #%03d: ", pokemon_id(curr->pokemon));
        }
        if (curr->found != 1) {
            unknownName(strLength(pokemon_name(curr->pokemon)));        
        }
        else if (curr->found == 1) {
            printf("%s\n", pokemon_name(curr->pokemon));
        }
        curr = curr->next;
    }            
}
 
////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void next_pokemon(Pokedex pokedex) {
    //struct pokenode *curr = pokedex->select;
    //why does curr = curr->next not work??
    if (pokedex->select != NULL && pokedex->select->next != NULL) {
        pokedex->select = pokedex->select->next; 
    }
}

void prev_pokemon(Pokedex pokedex) {
    if (pokedex->select != NULL && pokedex->select->prev != NULL) {
        pokedex->select = pokedex->select->prev; 
    }
}

//changes currently selected pokemon to desginated id
void change_current_pokemon(Pokedex pokedex, int id) {
    struct pokenode *curr = pokedex->head;
    while (curr != NULL) {
        if (id == pokemon_id(curr->pokemon)) {
            pokedex->select = curr;
        }
        curr = curr->next;
    }
}


void remove_pokemon(Pokedex pokedex) {
    struct pokenode *oldSelect = pokedex->select;
    if (oldSelect == NULL){
        return;
    }
    //only one thing on the list
    if (pokedex->select->prev == NULL && pokedex->select->next == NULL) {
        pokedex->select = NULL;
        pokedex->head = NULL;
        //destroy_node(oldSelect);
    }
    //last on list
    else if (pokedex->select->next == NULL) { 
        pokedex->select = pokedex->select->prev;
        pokedex->select->next = NULL;
        //destroy_node(oldSelect);
    }
    //first on list
    else if (pokedex->select->prev == NULL) {
        pokedex->select = pokedex->select->next;
        pokedex->select->prev = NULL;
        //destroy_node(oldSelect);
        pokedex->head = pokedex->select;
    }    
    //middle on list
    else {
        pokedex->select = pokedex->select->next;
        pokedex->select->prev = oldSelect->prev;
        oldSelect->prev->next = pokedex->select;
        //destroy_node(oldSelect);
    }
    destroy_node(oldSelect);
}

void destroy_pokedex(Pokedex pokedex) {
    while(pokedex->select != NULL){
        remove_pokemon(pokedex);
    }
    free(pokedex);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    srand(seed);
    struct pokenode *curr = pokedex->head;
    int pokedexContains = 0;
    while (curr != NULL) {
        if (pokemon_id(curr->pokemon) <= factor - 1) {
            pokedexContains = 1;
        }
        curr = curr->next;
    }
    if (pokedexContains == 0) {
        fprintf(stderr, "exiting because \n");
        exit(1);
    }
    struct pokenode *current = pokedex->head;    
    int pokemonFound = 0;
    while (pokemonFound <= how_many) {
        int to_find = rand()%factor;
        current = pokedex->head;
        printf("%d\n",to_find);
        while (current != NULL) {
            if (pokemon_id(current->pokemon) == to_find) {
                pokemonFound = pokemonFound + 1;
                current->found = 1;
                printf("%d",current->found); 
                  
            }
            current = current->next;
        }
    }    
}

int count_found_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    int pokemonFound = 0;
    while (curr != NULL) {
        if (curr->found == 1) {
            pokemonFound = pokemonFound + 1;
        }
        curr = curr->next;    
    }
    return pokemonFound;
}

int count_total_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    int totalPokemon = 0;
    while (curr != NULL) {
        totalPokemon = totalPokemon + 1;
        curr = curr->next;    
    }
    return totalPokemon;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

//sets pointers that point to a pokemon's evolved form
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    struct pokenode *curr = pokedex->head;
    if(curr == NULL){
        fprintf(stderr, " Invalid Pokemon Evolution!\n");
        exit(1);
    }
    int pokedexContains = 0;
    while (curr != NULL) {
        if (pokemon_id(curr->pokemon) == from_id) {
            pokedexContains = pokedexContains + 1;
        }
        if (pokemon_id(curr->pokemon) == to_id) {
            pokedexContains = pokedexContains + 1;
        }
        curr = curr->next;
    }
    if (from_id == to_id || pokedexContains != 2) {
        fprintf(stderr, " Invalid Pokemon Evolution!\n");
        exit(1); 
    }
    curr = pokedex->head;
    //assigns pointers to correct pokemon
    struct pokenode *PokemonA = NULL;
    struct pokenode *PokemonB = NULL;
    while (curr != NULL) {
        if (pokemon_id(curr->pokemon) == from_id) {
            PokemonA = curr;
        }
        if (pokemon_id(curr->pokemon) == to_id) {
            PokemonB = curr;
        }
        curr = curr->next;
    } 
    PokemonA->evolution = PokemonB;       
               
}

//prints a pokemon's evolved form depending on whether it is found
void show_evolutions(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        return;
    }
    if (curr->found != 1) {
        print_unknown_evolution(curr);
    }
    else if (curr->found == 1) {
        print_evolution(curr);
    }
    while (curr != NULL && curr->evolution != NULL) {
        if (curr->evolution->found != 1) {
            printf(" --> ");
            print_unknown_evolution(curr->evolution);
        }
        else if (curr->evolution->found == 1) {
            printf(" --> ");
            print_evolution(curr->evolution);  
        }
        curr = curr->evolution;
    }    

    printf("\n");
                    
    
}

int get_next_evolution(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        fprintf(stderr, "Pokedex is empty\n");
        exit(1);
    }
    if (curr->evolution == NULL) {
        return DOES_NOT_EVOLVE;
    }
    else {
        int evolved_id = pokemon_id(curr->evolution->pokemon);
        return evolved_id;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    if (type == NONE_TYPE || type == INVALID_TYPE || type == MAX_TYPE) {
        fprintf(stderr, "Invalid Type\n");
        exit(1);
    }    
    Pokedex type_pokedex = new_pokedex();
    struct pokenode *curr = pokedex->head;
    while (curr != NULL) {
        if (curr->found == 1) {
            if (pokemon_first_type(curr->pokemon) == type || pokemon_second_type(curr->pokemon) ==type) {
                Pokemon clone = clone_pokemon(curr->pokemon);
                add_pokemon(type_pokedex, clone);
                
            }
        }
        curr = curr->next;
    }
    curr = type_pokedex->head;
    while (curr != NULL) {
        curr->found = 1;
        curr = curr->next;
    }
    return type_pokedex;
                     
}

Pokedex get_found_pokemon(Pokedex pokedex) {
    Pokedex found_pokedex = new_pokedex();
    struct pokenode *current = pokedex->head;
    while (current != NULL) {
        if (current->found == 1) {
            Pokemon clone = clone_pokemon(current->pokemon); 
            
            struct pokenode *curr = found_pokedex->head;
            //inserts the first element in new list
            if (found_pokedex->head == NULL) {
                curr = malloc(sizeof(struct pokenode));
                found_pokedex->head = curr;
                curr->pokemon = clone;
                curr->next = NULL;
                curr->prev = NULL;
                curr->evolution = NULL;
                found_pokedex->select = found_pokedex->head;     
            }
        
            else {
                //inserts element with ID greater than first element
                if (pokemon_id(clone) > pokemon_id(curr->pokemon)) {
                    while (curr->next != NULL) {
                        curr = curr->next;
                    } 
                    if (curr->next == NULL && pokemon_id(clone) > pokemon_id(curr->pokemon)) {
                        curr->next = malloc(sizeof(struct pokenode));
                        curr->next->pokemon = clone;
                        curr->next->prev = curr;
                        curr->next->next = NULL;
                        curr->next->evolution = NULL;
                    }
                    else {
                        curr = found_pokedex->head;
                        while (curr->next != NULL && pokemon_id(clone) > pokemon_id(curr->pokemon)) {
                            struct pokenode *tmp = curr->next;
                            curr->next = malloc(sizeof(struct pokenode));
                            curr->next->pokemon = clone;
                            curr->next->prev = curr;
                            curr->next->next = tmp;
                            tmp->prev = curr->next;
                            curr->next->evolution = NULL;
                            curr = tmp;
                        }
                    }
                }
                //inserts element with ID less than first element
                curr = found_pokedex->head;
                if (pokemon_id(clone) < pokemon_id(curr->pokemon)) {
                    printf("working %s\n", pokemon_name(clone));
                    curr->prev = malloc(sizeof(struct pokenode));
                    curr->prev->pokemon = clone;
                    curr->prev->next = curr;
                    curr->prev->prev = NULL;
                    found_pokedex->head = curr->prev;
                    found_pokedex->select = found_pokedex->head;
 
                }
            }
        } 
        current = current->next;       
    }
    struct pokenode *pointer = found_pokedex->head;
    while (pointer != NULL) {
        pointer->found = 1;
        pointer = pointer->next;
    }
    return found_pokedex;   
}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
    /*Pokedex search_pokedex = new_pokedex();
    struct pokenode *curr = pokedex->head;
    while (curr != NULL) {
        if (curr->found == 1) {
            if (pokemon_first_type(curr->pokemon) == type || pokemon_second_type(curr->pokemon) ==type) {
                Pokemon clone = clone_pokemon(curr->pokemon);
                add_pokemon(search_pokedex, clone);
            }
        }
        curr = curr->next;
    }
    curr = search_pokedex->head;
    while (curr != NULL) {
        curr->found = 1;
        curr = curr->next;
    }
    return search_pokedex;
    */
    exit(1);    
}

// Add definitions for your own functions below.

//finds pokemon name length to print asterisk
static int strLength (char *name) {
    int i = 0;
    while (name[i] != '\0') {
        i++;
    }
    return i; 
}

//prints asterisk based on name length
static void unknownName(int strLength) {
    int i = 0;
    while (i < strLength) {
        printf("*");
        i++;
    }
    printf("\n");
}

//prints evolved form of pokemon that is found
static void print_evolution(struct pokenode *curr) {
    printf("#%03d ", pokemon_id(curr->pokemon));
    printf("Name: %s ", pokemon_name(curr->pokemon));
    printf("[");
    printf("%s", pokemon_type_to_string(pokemon_first_type(curr->pokemon)));
    if (pokemon_second_type(curr->pokemon) != NONE_TYPE) {
        printf(" %s", pokemon_type_to_string(pokemon_second_type(curr->pokemon)));
    }
    printf("]");
}

//prints out ID and question marks of unfound evolved pokemon form
static void print_unknown_evolution(struct pokenode *curr) {
    printf("#%03d ", pokemon_id(curr->pokemon));
    printf("???? [????]");
}

//frees pokemon nodes and the pokemon itself
static void destroy_node(struct pokenode *n) {
    destroy_pokemon(n->pokemon);
    free(n);
}
/*static int strings_equal(char *string1, char *string2, int strLength) {
    int search = 0
    int i = 0;
    int x = 0;
    while (string1[i] != '\0') {
        if (string1[i] == string2[x]) {
            x = x + 1;
        }
        if (x == strLength) {
            search = 1;
        }
        if (string1[i] != string2[x]) {
            x = 0;
        }
        i = i + 1;
        
    }            
    return search;
}*/
// Make them static to limit their scope to this file.
