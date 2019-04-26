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
    Pokemon         pokemon;
    int             found;
    
};

// Add any other structs you define here.


// Add prototypes for any extra functions you create here.


// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    return new_pokedex;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

//print name
//general code
//pokemon type print
//fields in struct

void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *curr = pokedex->head;
    if (pokedex->head == NULL) {
        curr = malloc(sizeof(struct pokenode));
        pokedex->head = curr;
        curr->pokemon = pokemon;
        curr->next = NULL;
        pokedex->select = curr;
        
    }
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        struct pokenode *latest = curr->next;
        latest = malloc(sizeof(struct pokenode));
    
        latest->next = NULL;
        latest->pokemon = pokemon;
    }
}    
    
    //fprintf(stderr, "exiting because you have not implemented the add_pokemon function in pokedex.c\n");
    //exit(1);


void detail_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select
    struct pokenode *currPokemon = curr->pokemon            
    if (curr->found != 1) {
        printf("Id: %03d\n", pokemon_id(currPokemon));
        printf("Name: *********\n");
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: --\n");
        break;
    }
    else {
        printf("Id: %03d\n", currPokemon->pokemon_id);
        printf("Name:%s\n", char *pokemon_name(currPokemon));
        printf("Height: %lf\n", double pokemon_height(currPokemon));
        printf("Weight: %lf\n", double pokemon_weight(currPokemon));
        printf("Type: %s ", const char *pokemon_type_to_string(pokemon_first_type(curr->pokemon)));
        if (pokemon_second_type(currPokemon->type2) != NONE_TYPE) {
            printf("%s", const char *pokemon_type_to_string(pokemon_first_type(curr->pokemon)));
        }    
        break; 
    }   
}

Pokemon get_current_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    if (curr == NULL) {
        fprintf(stderr, "Pokedex is empty\n");
        exit(1);
    }
    else if () {
        return pokemon ;
    }
}

void find_current_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->select;
    curr->found =  1;
}

void print_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    while (curr->next != NULL) {
        if (curr == pokedex->select) {
            printf("-->");
        }
        printf("#%03d: ", currPokemon->pokemon_id);
        if (curr->found != 1) {
        
        }
        else {
            printf("Name:%c\n", currPokemon->*name);
        }
        curr = curr->next;
    }            
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void next_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    curr = pokedex->head;  
    while (curr->next != NULL) {
         curr->current = 1; 
}

void prev_pokemon(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the prev_pokemon function in pokedex.c\n");
    exit(1);
}

void change_current_pokemon(Pokedex pokedex, int pokemon_id) {
    fprintf(stderr, "exiting because you have not implemented the change_current_pokemon function in pokedex.c\n");
    exit(1);
}

void remove_pokemon(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the remove_pokemon function in pokedex.c\n");
    exit(1);
}

void destroy_pokedex(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the destroy_pokedex function in pokedex.c\n");
    exit(1);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    fprintf(stderr, "exiting because you have not implemented the go_exploring function in pokedex.c\n");
    exit(1);
}

int count_found_pokemon(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the count_found_pokemon function in pokedex.c\n");
    exit(1);
}

int count_total_pokemon(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the count_total_pokemon function in pokedex.c\n");
    exit(1);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    fprintf(stderr, "exiting because you have not implemented the add_pokemon_evolution function in pokedex.c\n");
    exit(1);
}

void show_evolutions(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the show_evolutions function in pokedex.c\n");
    exit(1);
}

int get_next_evolution(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the get_next_evolution function in pokedex.c\n");
    exit(1);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    fprintf(stderr, "exiting because you have not implemented the get_pokemon_of_type function in pokedex.c\n");
    exit(1);
}

Pokedex get_found_pokemon(Pokedex pokedex) {
    fprintf(stderr, "exiting because you have not implemented the get_found_pokemon function in pokedex.c\n");
    exit(1);
}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
    fprintf(stderr, "exiting because you have not implemented the search_pokemon function in pokedex.c\n");
    exit(1);
}

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.
