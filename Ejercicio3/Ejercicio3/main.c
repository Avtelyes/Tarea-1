//
//  main.c
//  Ejercicio3
//
//  Created by Josué Carlos García Puig on 26/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FALSE,
    TRUE
} bool;

typedef struct {
    char * nombre;
    char * apellidos;
    int edad;
    int telefono;
} Persona;

typedef struct {
    int id;
    bool ocupado;
    Persona * persona;
} Cama;

typedef struct {
    char * nombre;
    Cama * camas;
} Hospital;

void CreacionHotel(Hospital *);
void IncorporarPaciente(Hospital *);

int main(int argc, const char * argv[]) {
    
    Hospital * hospital = (Hospital *) malloc(sizeof(Hospital));
    
    free(hospital);
    return 0;
}

void CreacionHotel(Hospital * hospital)
{
    hospital->camas = (Cama *) malloc(5 * sizeof(Cama));
}

void IncorporarPaciente(Hospital * hospital)
{
    Persona * aux;
    
    aux->nombre = malloc(sizeof(char) * 50);
    aux->apellidos = malloc(sizeof(char) * 50);
    
    printf("Dame el nombre: ");
    scanf(" %[^\n]s", aux->nombre);
    
    printf("Dame los apellidos: ");
    scanf(" %[^\n]s", aux->apellidos);
    
    printf("Dame la edad: ");
    scanf("%d", &aux->edad);
    
    printf("Dame el telefono de contacto: ");
    scanf("%d", &aux->telefono);
}
