#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "envios.h"
#include "LSO.h"
#include "LSOBB.h"
#include "ABB.h"
//GRUPO13
//MARIANO ARBELOA GUGLIELMINO
//VALENTIN VALDEON

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
        |   Max. Alta  |   Med. Alta   |  Max. Baja   |   Med. Baja   | Max. Evocar Exito | Med. Evocar Exito | Max Evocar Fracaso | Med Evocar Fracaso|
 ----------------------------------------------------------------------------------------------------------------------------------------------------------
  LSO   |    58.00     |     15.07     |     47.00    |     16.77     |       60.00       |       23.97       |       42.00        |       16.70       |
 ----------------------------------------------------------------------------------------------------------------------------------------------------------
 LSOBB  |     58.00    |     15.07     |     47.00    |     16.77     |       6.00        |       5.57        |        6.00        |       4.87        |
 ----------------------------------------------------------------------------------------------------------------------------------------------------------
  ABB   |     0.50     |     0.50      |     1.50     |     0.98      |       12.00       |       5.71        |        10.00       |       5.27        |
 ----------------------------------------------------------------------------------------------------------------------------------------------------------

Considerando las estructuras de datos seleccionadas para abordar el problema y las funciones de costos, se
distingue que, en el caso de la Lista Secuencial Ordenada (LSO), la Lista Secuencial Ordenada con Búsqueda Binaria (LSOBB) y el Árbol
Binario de Búsqueda (ABB), los costos asociados a las evocaciones se miden en "celdas consultadas", para las operaciones de
altas y bajas, la LSO y la LSOBB se evalúan en función de la "cantidad de corrimientos", mientras que el ABB, siendo una estructura basada
en punteros, utiliza la "modificación de punteros y copia de datos".

Analizando los esfuerzos máximos y mínimos en cada situación, se observa que:

LSO: Se destaca por ser la estructura más costosa en términos de altas, bajas y evocaciones. Aunque su rendimiento es menos eficiente en
comparación con otras estructuras, su simplicidad de implementación la convierte en una opción viable para programas básicos, donde los
tiempos de ejecución no son críticos.

LSOBB: Esta estructura, que incorpora búsqueda binaria (Biseccion), mejora significativamente en costos de evocación en comparación
a la LSO y el ABB. Sin embargo, sus costos de altas y bajas no difieren de la LSO, lo que la hace menos favorable para operaciones de
ese tipo.

ABB: El Árbol Binario de Búsqueda surge como la elección preferida para el problema en este práctico. Presenta costos muy bajos
en altas y bajas, lo que lo posiciona como la estructura óptima para dichas operaciones. Aunque la LSOBB supera ligeramente al ABB
en evocaciones, la diferencia no es significativa, asegurando al ABB como la estructura preferida para el contexto del problema
planteado.
*/


void comparacion(lista lso, listabb lsobb, arbol a);
void mostrarEstructura(lista lso);
void mostrarEstructuraLSOBB(listabb lsobb);
void memorizacionPrevia(lista *lso, listabb *lsobb, arbol *a);
//void memorizacionPreviaLSO(lista *lso);
//void memorizacionPreviaLSOBB(listabb *lsobb);
//void memorizacionPreviaABB(arbol *a);

int main(){
    int opcMenuOp;
    lista lso;
    listabb lsobb;
    arbol arbolito;
    envio env;
    do{
            system("cls");
            printf("Seleccione la operacion a realizar\n");
            printf("--------------------------------------------------------------- \n");
            printf("<1> Comparacion de estructuras\n");
            printf("<2> Mostrar todos los envios (LSO)\n");
            printf("<3> Mostrar todos los envios (LSOBB)\n");
            printf("<4> Mostrar todos los envios (ABB)\n");
            printf("<5> Salir\n");
            printf("--------------------------------------------------------------- \n");
            printf("Ingrese una opcion\n");
            scanf("%d",&opcMenuOp);
            fflush(stdin);
            switch(opcMenuOp){
                case 1:
                    system("cls");
                    initLSO(&lso);
                    initLSOBB(&lsobb);
                    initABB(&arbolito);
                    memorizacionPrevia(&lso,&lsobb,&arbolito);
                    comparacion(lso,lsobb,arbolito);
                    getchar();
                    break;
                case 2:
                    system("cls");
                    mostrarEstructura(lso);
                    getchar();
                    break;
                case 3:
                    system("cls");
                    mostrarEstructuraLSOBB(lsobb);
                    getchar();
                    break;
                case 4:
                    system("cls");
                    preOrden(arbolito.raiz);
                    getchar();
                    break;
                case 5:
                    system("cls");
                    printf("Gracias por utilizar nuestro sistema");
                    exit(1);
                default:
                    system("cls");
                    printf("-------------------Opcion Incorrecta--------------------\n");
                    printf("------Presione cualquier tecla para volver al menu------");
                    getchar();
                    break;
        }
    }while(opcMenuOp !=5);
    return 0;
}

void comparacion(lista lso,listabb lsobb,arbol a){
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("        |   Max. Alta  |   Med. Alta   |  Max. Baja   |   Med. Baja   | Max. Evocar Exito | Med. Evocar Exito | Max Evocar Fracaso | Med Evocar Fracaso|\n");
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  LSO   |    %.2f     |     %.2f     |     %.2f    |     %.2f     |       %.2f       |       %.2f       |       %.2f        |       %.2f       | \n",maxLsoAlta,(costLsoAlta/cantLsoAlta),maxLsoBaja,(costLsoBaja/cantLsoBaja),maxLsoEvocEx,(costLsoEvocEx/cantLsoEvocEx),maxLsoEvocFr,(costLsoEvocFr/cantLsoEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf(" LSOBB  |     %.2f    |     %.2f     |     %.2f    |     %.2f     |       %.2f        |       %.2f        |        %.2f        |       %.2f        |\n",maxLsobbAlta,(costLsobbAlta/cantLsobbAlta),maxLsobbBaja,(costLsobbBaja/cantLsobbBaja),maxLsobbEvocEx,(costLsobbEvocEx/cantLsobbEvocEx),maxLsobbEvocFr,(costLsobbEvocFr/cantLsobbEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  ABB   |     %.2f     |     %.2f      |     %.2f     |     %.2f      |       %.2f       |       %.2f        |        %.2f       |       %.2f        |\n",maxAbbAlta,(costAbbAlta/cantAbbAlta),maxAbbBaja,(costAbbBaja/cantAbbBaja),maxAbbEvocEx,(costAbbEvocEx/cantAbbEvocEx),maxAbbEvocFr,(costAbbEvocFr/cantAbbEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("Presione ENTER para volver");
}

void mostrarEstructura(lista lso){
    int i;
    if(lso.cant==0){
        printf("No hay envios en el registro \n");
        printf("Presione ENTER para continuar");
        getchar();
    }else{
        for(i=0;i<=lso.cant-1;i++){
            printf("\n---------------------------------------------------------------");
            printf("\nCodigo del envio: %s", lso.arr[i].codigo);
            printf("\n--------DATOS DEL RECEPTOR--------");
            printf("\nNombre y Apellido: %s", lso.arr[i].nomyapeRece);
            printf("\nDNI: %ld", lso.arr[i].documentoRece);
            printf("\nDomicilio: %s", lso.arr[i].domicilioRece);
            printf("\n--------DATOS DEL REMITENTE--------");
            printf("\nNombre y Apellido: %s", lso.arr[i].nomyapeRemi);
            printf("\nDNI: %ld", lso.arr[i].documentoRemi);
            printf("\n--------DATOS DEL ENVIO--------");
            printf("\nFecha de Envio: %s", lso.arr[i].fechaEnv);
            printf("\nFecha de Llegada: %s", lso.arr[i].fechaRece);
            printf("\nPresione ENTER para continuar");
            getchar();
        }
    }
}

void mostrarEstructuraLSOBB(listabb lsobb){
    int i;
    if(lsobb.cant==0){
        printf("No hay envios en el registro \n");
        printf("Presione ENTER para continuar");
        getchar();
    }else{
        for(i=0;i<=lsobb.cant-1;i++){
            printf("\n---------------------------------------------------------------");
            printf("\nCodigo del envio: %s", lsobb.arr[i].codigo);
            printf("\n--------DATOS DEL RECEPTOR--------");
            printf("\nNombre y Apellido: %s", lsobb.arr[i].nomyapeRece);
            printf("\nDNI: %ld", lsobb.arr[i].documentoRece);
            printf("\nDomicilio: %s", lsobb.arr[i].domicilioRece);
            printf("\n--------DATOS DEL REMITENTE--------");
            printf("\nNombre y Apellido: %s", lsobb.arr[i].nomyapeRemi);
            printf("\nDNI: %ld", lsobb.arr[i].documentoRemi);
            printf("\n--------DATOS DEL ENVIO--------");
            printf("\nFecha de Envio: %s", lsobb.arr[i].fechaEnv);
            printf("\nFecha de Llegada: %s", lsobb.arr[i].fechaRece);
            printf("\nPresione ENTER para continuar");
            getchar();
        }
    }
}
void memorizacionPrevia(lista *lso, listabb *lsobb, arbol *a){
    FILE *fp;
    envio env;
    int accion;
    int i=0;
    char codigo[8];
    int exito;

    if((fp = fopen("Operaciones-Envios.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else{
        while (!(feof(fp))){
            fscanf(fp,"%d",&accion);
            fscanf(fp," %[^\n]s",env.codigo);
            if(accion==1 || accion==2){
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                if(accion==1){
                    if((*lsobb).cant < MAX)
                        altaLSOBB(lsobb,env);
                    if((*lso).cant < MAX)
                        altaLSO(lso,env);
                    altaABB(a,env);

                }else{
                    bajaABB(a,env);
                    if((*lso).cant != 0)
                        bajaLSO(lso,env);
                    if((*lsobb).cant != 0)
                        bajaLSOBB(lsobb,env);
                }
            }else if (accion==3){
                evocacionABB(*a,env.codigo,&exito);
                evocacionLSO(env.codigo,*lso,&exito);
                evocacionLSOBB(env.codigo,*lsobb,&exito);
            }else{
                printf("Codigo de operacion no valido.\n");
            }
        }
    }
    if (!(feof(fp)))
        {
            printf("Se llego al limite de Envios, quedaron vendedores sin cargar del archivo.\n");
        }
        fflush(stdin);
        system("cls");
        fclose(fp);
}


/*void memorizacionPreviaLSO(lista *lso){
    FILE *fp;
    envio env;
    int accion;
    int i=0;
    char codigo[8];
    int exito;

    if((fp = fopen("Operaciones-Envios.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else {
        while (!(feof(fp)) && ((*lso).cant) < MAX){
            fscanf(fp,"%d",&accion);
            if(accion==1){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                altaLSO(lso,env);
            }else if(accion==2){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                bajaLSO(lso,env);
            }else{
                do{
                    fscanf(fp," %[^\n]s",codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    codigo[i] = toupper(codigo[i]);
                evocacionLSO(codigo,*lso,&exito);
            }
        }

        if (!(feof(fp)))
        {
            printf("Se llego al limite de Envios, quedaron vendedores sin cargar del archivo.\n");
        }
        fflush(stdin);
        system("cls");
    }
    fclose(fp);
}*/


/*void memorizacionPreviaLSOBB(listabb *lsobb){
    FILE *fp;
    envio env;
    int accion;
    int i=0;
    char codigo[8];
    int exito;

    if((fp = fopen("Operaciones-Envios.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else {
        while (!(feof(fp)) && ((*lsobb).cant) < MAX){
            fscanf(fp,"%d",&accion);
            if(accion==1){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                altaLSOBB(lsobb,env);
            }else if(accion==2){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                bajaLSOBB(lsobb,env);
            }else{
                do{
                    fscanf(fp," %[^\n]s",codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    codigo[i] = toupper(codigo[i]);
                evocacionLSOBB(codigo,*lsobb,&exito);
            }
        }
        if (!(feof(fp)))
        {
            printf("Se llego al limite de Envios, quedaron vendedores sin cargar del archivo.\n");
        }
        fflush(stdin);
        system("cls");
    }
    fclose(fp);
}

void memorizacionPreviaABB(arbol *a){
    FILE *fp;
    envio env;
    int accion;
    int i=0;
    char codigo[8];
    int exito;

    if((fp = fopen("Operaciones-Envios.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else {
        while (!(feof(fp))){
            fscanf(fp,"%d",&accion);
            if(accion==1){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                altaABB(a,env);
            }else if(accion==2){
                do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(env.codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                bajaABB(a,env);
            }else if(accion==3) {
                do{
                    fscanf(fp," %[^\n]s",codigo); //El control obliga que el codigo sea de 7 digitos
                }while(strlen(codigo)!= 7);
                for (i=0;i<=8 ; i++)
                    codigo[i] = toupper(codigo[i]);
                evocacionABB(*a,codigo,&exito);
            }
        }

        if (!(feof(fp)))
        {
            printf("Se llego al limite de Envios, quedaron vendedores sin cargar del archivo.\n");
        }
        fflush(stdin);
        system("cls");
    }
    fclose(fp);
}*/
