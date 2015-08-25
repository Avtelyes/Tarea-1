//
//  main.c
//  Ejercicio1
//
//  Created by Josué Carlos García Puig on 25/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRUE,
    FALSE
} bool;

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
} Embarcacion;

typedef void (* opcion_b) (Embarcacion *, int *);

void AdicionBarco(Embarcacion *, int *);
void InformacionBarco(Embarcacion *);
void AdicionTripulantes(Embarcacion *, int *);

Embarcacion * RedimensionEmbarcacion(Embarcacion *, int *);
void LiberaMemoria(Embarcacion *, int *);

//Persona tripulante;
//Embarcacion barco;

int main(int argc, const char * argv[]) {
    
    int tam = 0;
    
    Embarcacion * barcos = (Embarcacion *) malloc(1 * sizeof(Embarcacion));
    
    LiberaMemoria(barcos, &tam);
    
    return 0;
}

void AdicionBarco(Embarcacion barcosA[], int *tam)
{
    Embarcacion * aux = barcosA;
    Embarcacion * fin = (barcosA+*tam);
    
    bool cupo = FALSE;
    
    if((fin-1)->eslora == 0)
    {
        aux = (fin-1);
        InformacionBarco(aux);
    } else {
        
    }
}

void InformacionBarco(Embarcacion * barco)
{
    printf("Dame el nombre: ");
    scanf(" %[^\n]s", barco->nombre);
    
    printf("Dame el tamaño de eslora: ");
    scanf("%d", &barco->eslora);
    
    printf("Dame el tamaño de la manga: ");
    scanf("%d", &barco->manga);
    
    printf("Dame el No. tripulantes: ");
    scanf("%d", &barco->no_tripulantes);
    
    barco->tripulantes = (Persona *) malloc(barco->no_tripulantes * sizeof(Persona));
}

void AdicionTripulantes(Embarcacion barcosA[], int *tam)
{
    
}

Embarcacion * RedimensionEmbarcacion(Embarcacion barcosA[], int *tam)
{
    *barcosA = *(Embarcacion *) realloc(barcosA, (*tam+1) * sizeof(Embarcacion));
    
    *tam = *tam+1;
    
    Embarcacion * aux = (barcosA+*tam-1);
    
    return aux;
}

void LiberaMemoria(Embarcacion barcosA[], int *tam)
{
    Embarcacion * aux;
    Embarcacion * fin = (barcosA+*tam);
    
    for(aux=barcosA; aux<fin; ++aux)
    {
        free(aux->tripulantes);
    }
    
    free(aux);
}
