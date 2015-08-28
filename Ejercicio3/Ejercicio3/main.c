//
//  main.c
//  Ejercicio3
//
//  Created by Josué Carlos García Puig on 26/08/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef enum {
    FALSE,
    TRUE
} bool;

typedef struct {
    char * nombre;
    char * apellidos;
    int edad;
    char * telefono;
} Persona;

typedef struct {
    int id;
    bool ocupado;
    Persona * persona;
} Cama;

typedef struct {
    char * nombre;
    Cama * camas;
    int ultimo_id;
} Hospital;

typedef void (* opcion_h) (Hospital *, int *);

void CreacionHospital(Hospital *, int *);
void IncorporarPaciente(Hospital *, int *);
void ConsultaCama(Hospital *, int *);
void AltaPaciente(Hospital *, int *);
void ListaPacientes(Hospital *, int *);
void BalanceCamas(Hospital *, int *);

Cama * RedimensionHospital(Cama **, int *);

void LiberaMemoria(Hospital *, int *);

int main(int argc, const char * argv[]) {
    
    opcion_h * menu = (opcion_h *) malloc(N * sizeof(opcion_h));
    
    *menu = IncorporarPaciente;
    *(menu+1) = ConsultaCama;
    *(menu+2) = AltaPaciente;
    *(menu+3) = ListaPacientes;
    *(menu+4) = BalanceCamas;
    
    int no_camas = 5, opcion = 0;
    
    Hospital * hospital = (Hospital *) malloc(300 * sizeof(Hospital *));
    
    CreacionHospital(hospital, &no_camas);
    
    while(opcion != 6)
    {
        printf("--- Opciones --- \n1-Agregar Paciente\n2-Información de Cama\n3-Dar de Alta a Paciente\n4-Listar Pacientes\n5-Balance de Camas\n6-Salir\nEscoge tu opción: ");
        scanf("%d", &opcion);
        
        if(opcion != 6)
            (*(menu+opcion-1))(hospital, &no_camas);
    }
    
    LiberaMemoria(hospital, &no_camas);
    
    free(hospital);
    free(menu);
    return 0;
}

void CreacionHospital(Hospital * hospital, int * tam)
{
    hospital->nombre = malloc(sizeof(char) * 50);
    strcpy(hospital->nombre, "El pingüino feliz");
    hospital->camas = (Cama *) malloc(*tam * 50 * sizeof(Cama));
    hospital->ultimo_id = 0;
    
    int id = hospital->ultimo_id;
    
    Cama * aux = hospital->camas;
    Cama * fin = (aux+*tam);
    
    for(; aux<fin; ++aux)
    {
        id++;
        aux->id = id;
        aux->ocupado = FALSE;
    }
}

void IncorporarPaciente(Hospital * hospital, int * tam)
{
    Persona * aux = malloc(sizeof(Persona) * 200);
    Cama * auxC = hospital->camas;
    Cama * finC = (auxC+*tam);
    
    bool llenado = FALSE;
    
    aux->nombre = malloc(sizeof(char) * 50);
    aux->apellidos = malloc(sizeof(char) * 50);
    aux->telefono = malloc(sizeof(char) * 50);
    
    printf("Dame el nombre: ");
    scanf(" %[^\n]s", aux->nombre);
    
    printf("Dame los apellidos: ");
    scanf(" %[^\n]s", aux->apellidos);
    
    printf("Dame la edad: ");
    scanf("%d", &aux->edad);
    
    printf("Dame el telefono de contacto: ");
    scanf(" %[^\n]s", aux->telefono);
    
    for(; auxC<finC; ++auxC)
    {
        if(auxC->ocupado != TRUE)
        {
            auxC->persona = aux;
            llenado = TRUE;
            auxC->ocupado = TRUE;
            break;
        }
    }
    
    if(llenado == FALSE)
    {
        auxC = RedimensionHospital(&(hospital->camas), tam);
        auxC->persona = aux;
        auxC->ocupado = TRUE;
        llenado = TRUE;
    }
        
}

void ConsultaCama(Hospital * hospital, int * tam)
{
    int no_cama = 0;
    
    printf("\nDame el numero de la cama: ");
    scanf("%d", &no_cama);
    
    Cama * aux = (hospital->camas + no_cama-1);
    
    printf("Numero de cama: %d\n", aux->id);
    if(aux->ocupado == TRUE)
    {
        printf("Disponibilidad: Ocupada\n");
        printf("Informacion del paciente: \n");
        printf("Nombre y Apellidos: %s %s\n", aux->persona->nombre, aux->persona->apellidos);
        printf("Edad: %d\n", aux->persona->edad);
        printf("Telefono: %s\n\n", aux->persona->telefono);
        
    }
    else
        printf("Disponibilidad: Libre\n\n");
}

void AltaPaciente(Hospital * hospital, int * tam)
{
    int no_cama;
    
    Cama * aux = hospital->camas;
    
    printf("Dame el número de la cama para el alta: ");
    scanf("%d", &no_cama);
    
    aux = (aux+no_cama-1);
    
    free(aux->persona->telefono);
    free(aux->persona->apellidos);
    free(aux->persona->nombre);
    free(aux->persona);
    
    aux->ocupado = FALSE;
    
    printf("La cama %d ha quedado disponible\n\n", aux->id);
}

void ListaPacientes(Hospital * hospital, int * tam)
{
    Cama * aux = hospital->camas;
    Cama * fin = (aux+*tam);
    
    for(; aux<fin; ++aux)
    {
        if(aux->ocupado == TRUE)
        {
            printf("\n\nNombre y Apellidos: %s %s\n", aux->persona->nombre, aux->persona->apellidos);
            printf("Telefono de contacto: %s\n", aux->persona->telefono);
            printf("Cama asignada: %d\n\n", aux->id);
        }
    }
}

void BalanceCamas(Hospital * hospital, int * tam)
{
    int ocupadas = 0, disponibles = 0;
    
    Cama * aux = hospital->camas;
    Cama * fin = (aux+*tam);
    
    for(; aux<fin; ++aux)
    {
        if(aux->ocupado == TRUE)
            ocupadas++;
        else
            disponibles++;
    }
    
    printf("\n\nCamas Disponibles: %d\n", disponibles);
    printf("Camas Ocupadas: %d\n\n", ocupadas);
}

Cama * RedimensionHospital(Cama ** cama, int * tam)
{
    
    *(cama) = (Cama *) realloc(*cama, (*tam+5) * 50 * sizeof(Cama));
    
    *tam = *tam+5;
    
    Cama *aux2 = ((*cama + *tam-5));
    Cama *fin2 = ((*cama+*tam));
    
    int id = (aux2-1)->id;
    
    for(; aux2<fin2; ++aux2)
    {
        id++;
        aux2->id = id;
        aux2->ocupado = FALSE;
    }
    
    Cama * auxR = ((*cama+*tam-5));
    
    return auxR;
}

void LiberaMemoria(Hospital * hospital, int * tam)
{
    Cama * auxC = hospital->camas;
    Cama * finC = (auxC+*tam);
    
    Persona * auxP;
    
    for(; auxC<finC; ++auxC)
    {
        if(auxC->ocupado == TRUE)
        {
            auxP = auxC->persona;
            free(auxP->telefono);
            free(auxP->apellidos);
            free(auxP->nombre);
            free(auxP);
        }
    }
    
    free(hospital->camas);
    free(hospital->nombre);
}
