//
//  main.c
//  Ejercicio2
//
//  Created by Josué Carlos García Puig on 25/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define NO_PREGUNTAS 2

typedef struct {
    char * res1;
    char * res2;
    char * res3;
    char * res4;
    char * res5;
    char * res6;
} Frecuencia;

typedef struct {
    char * ran18_25;
    char * ran26_35;
    char * ran36_45;
    char * ran46_65;
    char * ran66_120;
} Rango;

typedef struct {
    char * nombre;
    int edad;
    char ** respuestas;
} Persona;

typedef struct {
    char * descripcion;
    char ** respuestas;
    Frecuencia * frecuencia_respuestas;
    Rango * rangos_respuestas;
} Pregunta;

void AgregarPersona(Persona *, int *);
void AgregarPreguntas(Pregunta *, int *);
void ImpresionPersonas(Persona *, int *);
void HistogramaFrecuencias(Pregunta *, int *);
void HistogramaRangos(Pregunta *, int *);

void InformacionPersona(Persona *);
Persona * RedimensionPersonas(Persona *, int *);
void RespuestasAleatorias(Persona *, Pregunta *, int *, int *);
void RegistroRespuestas(Pregunta *, Frecuencia *, Rango *, int, int, int);
void InicializacionCeros(Frecuencia *, Rango *);
void LiberaMemoria(Persona *, Pregunta *, int *, int *);
void copy_string(char *d, char *s);

int main(int argc, const char * argv[]) {
    
    int sizeP = 2, sizePre = NO_PREGUNTAS;
    
    /*printf("Dame el numero de personas: ");
    scanf("%d",&sizeP);*/
    
    Persona * personas = (Persona *) malloc(sizeP * sizeof(Persona));
    Pregunta * preguntas = (Pregunta *) malloc(sizePre * sizeof(Pregunta));
    
    AgregarPersona(personas, &sizeP);
    AgregarPreguntas(preguntas, &sizePre);
    RespuestasAleatorias(personas, preguntas, &sizeP, &sizePre);
    ImpresionPersonas(personas, &sizeP);
    HistogramaFrecuencias(preguntas, &sizePre);
    HistogramaRangos(preguntas, &sizePre);
    
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
        InformacionPersona(aux);
    }
}

void AgregarPreguntas(Pregunta * preguntasA, int * tam)
{
    Pregunta * auxP = preguntasA;
    Pregunta * finP = (auxP+*tam);
    
    int no_pregunta = 1;
    
    for(; auxP<finP; ++auxP)
    {
        auxP->descripcion = malloc(sizeof(char) * 152);
        auxP->respuestas = (char **) malloc(sizeof(char*) * 6);
        auxP->frecuencia_respuestas = (Frecuencia *)malloc(sizeof(Frecuencia) * 1);
        auxP->rangos_respuestas = (Rango *)malloc(sizeof(Rango) * 6);
        
        InicializacionCeros(auxP->frecuencia_respuestas, auxP->rangos_respuestas);
        
        char ** aux = auxP->respuestas;
        char ** fin = (aux + 6);
        
        int cont = 1;
        
        printf("Dame la descripción de la pregunta %d: ", no_pregunta);
        scanf(" %[^\n]s", auxP->descripcion);
        
        for(; aux<fin; ++aux)
        {
            printf("Dame la respuesta no. %d: ", cont);
            *aux = (char *) malloc(sizeof(char) * 100);
            scanf(" %[^\n]s", *aux);
            cont++;
        }
        no_pregunta++;
    }
}

void ImpresionPersonas(Persona * personasA, int * tam)
{
    Persona * aux = personasA;
    Persona * fin = (personasA+*tam);
    
    char ** auxC;
    char ** finC;
    
    int cont = 1;
    
    for(; aux<fin; ++aux)
    {
        printf("\n%s\n", aux->nombre);
        
        auxC = aux->respuestas;
        finC = (auxC+NO_PREGUNTAS);
        
        for(; auxC<finC; ++auxC)
        {
            printf("Pregunta %d:\n", cont);
            printf("Respuesta: %s\n\n", *(auxC));
            cont++;
        }
        
        cont = 1;
    }
}

void HistogramaFrecuencias(Pregunta * preguntasA, int * tam)
{
    int no_pregunta = 1;
    
    Pregunta *aux = preguntasA;
    Pregunta *fin = (preguntasA+*tam);
    
    Frecuencia *auxF;
    
    for(; aux<fin; ++aux)
    {
        printf("Pregunta %d\n", no_pregunta);
        printf("No. Respuesta       Frecuencia\n");
        auxF = aux->frecuencia_respuestas;
        printf("      1                 %lu              %s\n", strlen(auxF->res1), auxF->res1);
        printf("      2                 %lu              %s\n", strlen(auxF->res2), auxF->res2);
        printf("      3                 %lu              %s\n", strlen(auxF->res3), auxF->res3);
        printf("      4                 %lu              %s\n", strlen(auxF->res4), auxF->res4);
        printf("      5                 %lu              %s\n", strlen(auxF->res5), auxF->res5);
        printf("      6                 %lu              %s\n\n", strlen(auxF->res6), auxF->res6);
        no_pregunta++;
    }
}

void HistogramaRangos(Pregunta * preguntasA, int *tam)
{
    int no_pregunta = 1, no_rango = 1;
    
    Pregunta *aux = preguntasA;
    Pregunta *fin = (preguntasA+*tam);
    
    Rango *auxR;
    Rango *finR;
    
    for(; aux<fin; ++aux)
    {
        printf("Pregunta %d\n", no_pregunta);
        auxR = aux->rangos_respuestas;
        finR = (auxR+6);
        for(; auxR<finR; ++auxR)
        {
            printf("No. Respuesta       Rangos\n");
            printf("      %d            18-25           %s\n", no_rango, auxR->ran18_25);
            printf("                    26-35           %s\n", auxR->ran26_35);
            printf("                    36-45           %s\n", auxR->ran36_45);
            printf("                    46-65           %s\n", auxR->ran46_65);
            printf("                    66-120          %s\n\n", auxR->ran66_120);
            no_rango++;
        }
        no_rango = 1;
        no_pregunta++;
    }
}

void InformacionPersona(Persona * persona)
{
    persona->nombre = malloc(sizeof(char) * 102);
    persona->respuestas = (char **) malloc(sizeof(char) * NO_PREGUNTAS);
    
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

void RespuestasAleatorias(Persona * personasA, Pregunta * preguntasA, int * tamP, int * tamPre)
{
    Persona * aux = personasA;
    Persona *fin = (personasA+*tamP);
    
    Pregunta * auxPre = preguntasA;
    Pregunta * finPre = (preguntasA+*tamPre);
    
    char ** auxC;
    char ** finC;
    
    int cont = 1, no_respuesta = 0, no_eleccion = 0;
    
    srand((int) time(NULL));
    
    for(; auxPre<finPre; ++auxPre)
    {
        auxC = auxPre->respuestas;
        finC = (auxC+6);
        
        /*for(; auxC<finC; ++auxC)
        {
            printf("Respuesta %d: %s\n", cont, *(auxC));
            cont++;
        }*/
        
        auxC = auxPre->respuestas;
        
        for(; aux<fin; ++aux)
        {
            no_respuesta = rand()% 6;
            *(aux->respuestas+no_eleccion) = (char *) malloc(sizeof(char) * 100);
            copy_string(*(aux->respuestas + no_eleccion), *(auxC + no_respuesta));
            //*(aux->respuestas + no_eleccion) = *(auxC + no_respuesta);
            RegistroRespuestas(auxPre, auxPre->frecuencia_respuestas, auxPre->rangos_respuestas, aux->edad, no_respuesta, no_eleccion);
        }
        no_eleccion++;
        aux = personasA;
    }
}

void RegistroRespuestas(Pregunta * pregunta, Frecuencia * listaF, Rango * listaR, int edad, int respuesta, int eleccion)
{
    Frecuencia * aux = listaF;
    int no_respuesta = respuesta+1;
    Rango * auxR = (listaR+eleccion);
    
    switch (no_respuesta) {
        case 1:
            strcat(aux->res1, "*");
            break;
        case 2:
            strcat(aux->res2, "*");
            break;
        case 3:
            strcat(aux->res3, "*");
            break;
        case 4:
            strcat(aux->res4, "*");
            break;
        case 5:
            strcat(aux->res5, "*");
            break;
        case 6:
            strcat(aux->res6, "*");
            break;
        default: printf("Respuesta incorrecta \n");
            break;
    }
    
    if(edad>=18 && edad<=25)
    {
        strcat(auxR->ran18_25, "*");
    } else if (edad>=26 && edad<=35) {
        strcat(auxR->ran26_35, "*");
    } else if (edad>=36 && edad<=45) {
        strcat(auxR->ran36_45, "*");
    } else if (edad>=46 && edad<=65) {
        strcat(auxR->ran46_65, "*");
    } else if (edad>=66 && edad<=120) {
        strcat(auxR->ran66_120, "*");
    }
}

void InicializacionCeros(Frecuencia * frecuencias, Rango * rangos)
{
    Frecuencia * auxF = frecuencias;
    
    Rango *auxR = rangos;
    Rango *finR = (auxR+6);
    
    auxF->res1 = malloc(sizeof(char) * 50);
    auxF->res2 = malloc(sizeof(char) * 50);
    auxF->res3 = malloc(sizeof(char) * 50);
    auxF->res4 = malloc(sizeof(char) * 50);
    auxF->res5 = malloc(sizeof(char) * 50);
    auxF->res6 = malloc(sizeof(char) * 50);
    
    for(; auxR<finR; ++auxR)
    {
        auxR->ran18_25=malloc(sizeof(char) * 50);
        auxR->ran26_35=malloc(sizeof(char) * 50);
        auxR->ran36_45=malloc(sizeof(char) * 50);
        auxR->ran46_65=malloc(sizeof(char) * 50);
        auxR->ran66_120=malloc(sizeof(char) * 50);
    }
}

void LiberaMemoria(Persona * personasA, Pregunta * preguntasA, int * tamP, int * tamPre)
{
    Persona * aux = personasA;
    Persona * fin = (aux+*tamP);
    
    char **auxCP = personasA->respuestas;
    char **finCP = (auxCP+NO_PREGUNTAS);
    
    Pregunta * auxP = preguntasA;
    Pregunta * finP = (preguntasA+*tamPre);
    
    Rango * auxR;
    Rango * finR;
    
    Frecuencia * auxF;
    
    char ** auxC = preguntasA->respuestas;
    char ** finC = (auxC+6);
    
    for(; aux<fin; ++aux)
    {
        auxCP = aux->respuestas;
        finCP = (auxCP+NO_PREGUNTAS);
        for(; auxCP<finCP; ++auxCP)
        {
            free(*auxCP);
        }
        free(aux->respuestas);
        free(aux->nombre);
    }
    
    for(; auxP<finP; ++auxP)
    {
        auxR = auxP->rangos_respuestas;
        finR = (auxR+6);
        
        for(; auxR<finR; ++auxR)
        {
            free(auxR->ran66_120);
            free(auxR->ran46_65);
            free(auxR->ran36_45);
            free(auxR->ran26_35);
            free(auxR->ran18_25);
        }
        
        free(auxR);
        
        auxF = auxP->frecuencia_respuestas;
        free(auxF->res6);
        free(auxF->res5);
        free(auxF->res4);
        free(auxF->res3);
        free(auxF->res2);
        
        free(auxF);
        
        auxC = auxP->respuestas;
        finC = (auxC+6);
        for(; auxC<finC; ++auxC)
        {
            free(*auxC);
        }
        free(auxP->respuestas);
        free(auxP->descripcion);
    }
}

void copy_string(char *d, char *s) {
    int c = 0;
    
    while (*(s+c) != '\0') {
        *(d+c) = *(s+c);
        c++;
    }
    *(d+c) = '\0';
}
