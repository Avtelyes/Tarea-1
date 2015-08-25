//
//  main.c
//  Ejercicio2
//
//  Created by Josué Carlos García Puig on 25/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * nombre;
    int edad;
} Persona;

typedef struct {
    char * descripcion;
    char ** respuestas;
} Pregunta;

void AgregarPersona(Persona *, int *);
void AgregarPreguntas(Pregunta *, int *);

void InformacionPersona(Persona *);
Persona * RedimensionPersonas(Persona *, int *);
void LiberaMemoria(Persona *, Pregunta *, int *, int *);

int main(int argc, const char * argv[]) {
    
    int sizeP = 1, sizePre = 10;
    
    Persona * personas = (Persona *) malloc(1 * sizeof(Persona));
    Pregunta * preguntas = (Pregunta *) malloc(10 * sizeof(Pregunta));
    
    AgregarPreguntas(preguntas, &sizePre);
    
    LiberaMemoria(personas, preguntas, &sizeP, &sizePre);
    
    free(personas);
    free(preguntas);
    
    return 0;
}

void AgregarPersona(Persona * personasA, int * tam)
{
    Persona * aux;
    Persona * fin = (personasA+*tam);
    
    for(aux=personasA; aux<fin; ++aux)
    {
        if(aux->nombre == NULL)
        {
            InformacionPersona(aux);
        }
    }
}

void AgregarPreguntas(Pregunta * preguntasA, int * tam)
{
    preguntasA->descripcion = malloc(sizeof(Pregunta) * 152);
    preguntasA->respuestas = (char **) malloc(sizeof(char) * 6);
    
    char ** aux = preguntasA->respuestas;
    char ** fin = (aux + 6);
    
    int cont = 1;
    
    printf("Dame la descripción de la pregunta: ");
    scanf(" %[^\n]s", preguntasA->descripcion);
    
    for(; aux<fin; ++aux)
    {
        printf("Dame la respuesta no. %d: ", cont);
        *aux = (char *) malloc(sizeof(char) * 100);
        scanf(" %[^\n]s", *aux);
        cont++;
    }
}

void InformacionPersona(Persona * persona)
{
    persona->nombre = malloc(sizeof(char) * 102);
    
    printf("Dame el nombre de la persona: ");
    scanf(" %[^\n]s", persona->nombre);
    
    printf("Dame la edad de la persona: ");
    scanf("%d", &persona->edad);
}

Persona * RedimensionPersona(Persona * personasA, int * tam)
{
    *personasA = *(Persona *) realloc(personasA, (*tam+1) * sizeof(Persona));
    
    *tam = *tam+1;
    
    Persona * aux = (personasA+*tam-1);
    
    return aux;
}

void LiberaMemoria(Persona * personasA, Pregunta * preguntasA, int * tamP, int * tamPre)
{
    Persona * aux = personasA;
    Persona * fin = (aux+*tamP);
    
    Pregunta * auxP = preguntasA;
    Pregunta * finP = (preguntasA+*tamPre);
    
    char ** auxC = preguntasA->respuestas;
    char ** finC = (auxC+6);
    
    for(; aux<fin; ++aux)
    {
        free(aux->nombre);
    }
    
    for(; auxP<finP; ++auxP)
    {
        for(; auxC<finC; ++auxC)
        {
            free(*auxC);
        }
        free(preguntasA->respuestas);
        free(auxP->descripcion);
    }
}
