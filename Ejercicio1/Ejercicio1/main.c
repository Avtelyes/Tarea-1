//
//  main.c
//  Ejercicio1
//
//  Created by Josué Carlos García Puig on 25/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    char apellidos[70];
    int edad;
    char rol[50];
} Persona;

typedef struct {
    char nombre[50];
    int eslora;
    int manga;
    int no_tripulantes;
    Persona * tripulantes;
} Barco;

Persona tripulante;
Barco barco;

int main(int argc, const char * argv[]) {
    
    return 0;
}
