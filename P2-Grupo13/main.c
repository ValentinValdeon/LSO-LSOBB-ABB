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


void mostrarEstructura(lista lso);
void mostrarEstructuraLSOBB(listabb lsobb);
void memorizacionPrevia(lista *lso);
void memorizacionPreviaLSOBB(listabb *lsobb);
void memorizacionPreviaABB(arbol *a);

int main(){
    int opcMenuOp;
    lista lso;
    listabb lsobb;
    arbol arbolito;
    initLSO(&lso);
    initLSOBB(&lsobb);
    initABB(&arbolito);
    envio env;
    memorizacionPrevia(&lso);
    memorizacionPreviaLSOBB(&lsobb);
    memorizacionPreviaABB(&arbolito);
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

void memorizacionPrevia(lista *lso){
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
        printf("Presione ENTER para continuar");
        fflush(stdin);
        getchar();
        system("cls");
    }
    fclose(fp);
}

void memorizacionPreviaLSOBB(listabb *lsobb){
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
        printf("Presione ENTER para continuar");
        fflush(stdin);
        getchar();
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

    if((fp = fopen("PruebaABB.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else {
        while (!(feof(fp))){
            fscanf(fp,"%d",&accion);
            if(accion==1){
                //do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                //}while(strlen(env.codigo)!= 7);
                //for (i=0;i<=8 ; i++)
                //    env.codigo[i] = toupper(env.codigo[i]);
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                altaABB(a,env);
            }else if(accion==2){
                //do{
                    fscanf(fp," %[^\n]s",env.codigo); //El control obliga que el codigo sea de 7 digitos
                //}while(strlen(env.codigo)!= 7);
                //for (i=0;i<=8 ; i++)
                //    env.codigo[i] = toupper(env.codigo[i]);
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
        printf("Presione ENTER para continuar");
        fflush(stdin);
        getchar();
        system("cls");
    }
    fclose(fp);
}
