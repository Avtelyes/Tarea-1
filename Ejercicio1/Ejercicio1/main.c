//
//  main.c
//  Ejercicio1
//
//  Created by Josué Carlos García Puig on 25/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef enum {
    FALSE,
    TRUE
} bool;

typedef struct {
    char * nombre;
    char * apellidos;
    int edad;
    char * rol;
} Persona;

typedef struct {
    char * nombre;
    char * propietario;
    int eslora;
    int manga;
    int no_tripulantes;
    int tripulantes_actuales;
    Persona * tripulantes;
} Embarcacion;

typedef void (* opcion_b) (Embarcacion *, int *);

void AdicionBarco(Embarcacion *, int *);
void InformacionBarco(Embarcacion *);
void AdicionTripulantes(Embarcacion *, int *);
void InformacionTripulante(Persona *);
void ImpresionTripulantes(Embarcacion *, int *);
void ImpresionBarcos(Embarcacion *, int *);

Embarcacion * RedimensionEmbarcacion(Embarcacion *, int *);
void LiberaMemoria(Embarcacion *, int *);

//Persona tripulante;
//Embarcacion barco;

int main(int argc, const char * argv[]) {
    
    opcion_b * menu = (opcion_b *) malloc(N * sizeof(opcion_b));
    
    *menu = AdicionBarco;
    *(menu+1) = AdicionTripulantes;
    *(menu+2) = ImpresionTripulantes;
    *(menu+3) = ImpresionBarcos;
    
    int tam = 10, opcion = 0;
    
    Embarcacion * barcos = (Embarcacion *) malloc(10 * sizeof(Embarcacion));
    
    while(opcion != 5)
    {
        printf("--- Opciones --- \n1-Agregar Barco\n2-Agregar Tripulante\n3-Listar Tripulacion de un Barco\n4-Listar Barcos\n5-Salir\nEscoge tu opción: ");
        scanf("%d", &opcion);
        
        if(opcion != 5)
            (*(menu+opcion-1))(barcos, &tam);
    }
    
    LiberaMemoria(barcos, &tam);
    free(barcos);
    free(menu);
    
    return 0;
}

void AdicionBarco(Embarcacion * barcosA, int *tam)
{
    Embarcacion * aux = barcosA;
    Embarcacion * fin = (barcosA+*tam);
    
    bool cupo = FALSE;
    
    for(; aux<fin; ++aux)
    {
        if((aux)->nombre == NULL)
        {
            InformacionBarco(aux);
            cupo = TRUE;
            break;
        }
    }
    
    if (cupo == FALSE) {
        aux = RedimensionEmbarcacion(barcosA, tam);
        InformacionBarco(aux);
        cupo = TRUE;
    }
}

void InformacionBarco(Embarcacion * barco)
{
    barco->propietario = malloc(sizeof(char) * 52);
    barco->nombre = malloc(sizeof(char) * 102);
    
    printf("Dame el nombre completo del propietario: ");
    scanf(" %[^\n]s", barco->propietario);
    
    printf("Dame el nombre del Barco: ");
    scanf(" %[^\n]s", barco->nombre);
    
    printf("Dame el tamaño de eslora: ");
    scanf("%d", &barco->eslora);
    
    printf("Dame el tamaño de la manga: ");
    scanf("%d", &barco->manga);
    
    printf("Dame el No. tripulantes: ");
    scanf("%d", &barco->no_tripulantes);
    
    barco->tripulantes = (Persona *) malloc(barco->no_tripulantes * sizeof(Persona));
}

void AdicionTripulantes(Embarcacion * barcosA, int *tam)
{
    int no_barco = 0, max, actual;
    Embarcacion * aux;
    Persona * auxP;
    
    printf("Dame el numero de barco para agregar al tripulante: ");
    scanf("%d", &no_barco);
    
    aux = (barcosA+no_barco-1);
    auxP = aux->tripulantes;
    max = aux->no_tripulantes;
    actual = aux->tripulantes_actuales;
    
    if(max == actual)
        printf("Ya no hay plazas disponibles \n");
    else
    {
        InformacionTripulante((auxP+actual));
        aux->tripulantes_actuales = actual+1;
    }
}

void InformacionTripulante(Persona * tripulante)
{
    tripulante->nombre = malloc(sizeof(char) * 52);
    tripulante->apellidos = malloc(sizeof(char) * 72);
    tripulante->rol = malloc(sizeof(char) * 52);
    
    printf("Dame el nombre: ");
    scanf(" %[^\n]s", tripulante->nombre);
    
    printf("Dame los apellidos: ");
    scanf(" %[^\n]s", tripulante->apellidos);
    
    printf("Dame la edad: ");
    scanf("%d", &tripulante->edad);
    
    printf("Dame el rol: ");
    scanf(" %[^\n]s", tripulante->rol);
}

void ImpresionTripulantes(Embarcacion * barcosA, int *tam)
{
    int no_barco = 0, actual;
    Embarcacion * aux;
    Persona * auxP;
    Persona * fin;
    
    printf("Dame el numero del barco del cual quieres conocer la tripulación: ");
    scanf("%d", &no_barco);
    
    aux = (barcosA+no_barco-1);
    
    if(aux->tripulantes_actuales == 0)
        printf("Actualmente no hay tripulación\n");
    else
    {
        auxP = aux->tripulantes;
        actual = aux->tripulantes_actuales;
        fin = (auxP+actual);
        
        printf("Nombre del Barco: %s\n", aux->nombre);
        printf("Propietario: %s\n", aux->propietario);
        printf("Tripulacion: \n");
        
        for(; auxP<fin; ++auxP)
        {
            printf("Nombre: %s\nApellidos: %s\nEdad: %d\nRol: %s\n\n", auxP->nombre, auxP->apellidos, auxP->edad, auxP->rol);
        }
    }
    
}

void ImpresionBarcos(Embarcacion * barcosA, int *tam)
{
    int cont = 1, tamT = 0, rest = 0;
    Embarcacion * aux;
    Embarcacion * fin = (barcosA+*tam);
    Persona * auxP, * finP;
    
    for(aux=barcosA; aux<fin; ++aux)
    {
        if(aux->propietario != NULL)
        {
            tamT = aux->tripulantes_actuales;
            rest = aux->no_tripulantes - tamT;
            printf("\nBarco No. %d\n", cont);
            printf("Nombre del Barco: %s\nPropietario: %s\nTamaño Eslora: %d\nTamaño Manga: %d\nNo. Tripulación Máxima: %d\nPlazas Disponibles: %d\nTripulación:\n\n", aux->nombre, aux->propietario, aux->eslora, aux->manga, aux->no_tripulantes, rest);
            auxP = aux->tripulantes;
            finP = (auxP+tamT);
            for(; auxP<finP; ++auxP)
            {
                printf("Nombre: %s\nApellidos: %s\nEdad: %d\nRol: %s\n\n", auxP->nombre, auxP->apellidos, auxP->edad, auxP->rol);
            }
            cont++;
        }
    }
}

Embarcacion * RedimensionEmbarcacion(Embarcacion * barcosA, int *tam)
{
    *barcosA = *(Embarcacion *) realloc(barcosA, (*tam+1) * sizeof(Embarcacion));
    
    *tam = *tam+1;
    
    Embarcacion * aux = (barcosA+*tam-1);
    
    return aux;
}

void LiberaMemoria(Embarcacion * barcosA, int *tam)
{
    int tamT = 0;
    Embarcacion * aux;
    Embarcacion * fin = (barcosA+*tam);
    Persona * auxP, * finP;
    
    for(aux=barcosA; aux<fin; ++aux)
    {
        tamT = aux->tripulantes_actuales;
        auxP = aux->tripulantes;
        finP = (auxP+tamT);
        for(; auxP<finP; ++auxP)
        {
            free(auxP->rol);
            free(auxP->apellidos);
            free(auxP->nombre);
        }
        
        free(aux->tripulantes);
        free(aux->propietario);
        free(aux->nombre);
        //free(aux);
    }
}
