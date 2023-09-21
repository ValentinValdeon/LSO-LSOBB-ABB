#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <string.h>
#include <conio.h>
#include "envios.h"
#include <malloc.h>
typedef struct Nodo{
    envio env;
    struct Nodo *der;
    struct Nodo *izq;
}nodo;
typedef struct{
    nodo *raiz;
    nodo *pos;
    nodo *padre;
}arbol;
void initABB(arbol *a){
    (*a).pos=NULL;
    (*a).padre=NULL;
    (*a).raiz=NULL;
}

int localizarABB(char cod[],arbol *a){
    a->pos=a->raiz;
    a->padre=a->raiz;
    while(a->pos != NULL && strcmp(a->pos->env.codigo,cod) != 0){
        if(strcmp(a->pos->env.codigo,cod) < 0){
            a->padre = a->pos;
            a->pos = a->pos->der;
        }else{
            a->padre = a->pos;
            a->pos = a->pos->izq;
        }
    }
    if(a->pos != NULL){
        return 1;
    }else{
        return 0;
    }
}

int altaABB(arbol *a,envio env){
    if(!localizarABB(env.codigo,a)){
        nodo *nuevo_nodo;
        nuevo_nodo=(nodo*)malloc(sizeof(nodo));
        if(nuevo_nodo == NULL){
            return 2; //Sin espacio
        }else{
            nuevo_nodo->env=env;
            nuevo_nodo->der=NULL;
            nuevo_nodo->izq=NULL;
            if(a->raiz == NULL){
                a->raiz=nuevo_nodo;
                return 1;//arbol sin elementos
            }else if (strcmp(a->padre->env.codigo,env.codigo) < 0){
                a->padre->der = nuevo_nodo;
                return 1;//arbol con padre menor al nuevo elemento
            }else{
                a->padre->izq = nuevo_nodo;
                return 1;//arbol con padre mayor al nuevo elemento
            }

        }
    }else{
        return 0;//El envio se encontro en el arbol
    }
}

int bajaABB(arbol *a,envio env){
    if(!localizarABB(env.codigo,a)){
        return 2;
    }else{
        nodo *aux;
        if(strcmp(a->pos->env.codigo,env.codigo)==0 && strcmp(a->pos->env.nomyapeRemi,env.nomyapeRemi)==0 && strcmp(a->pos->env.nomyapeRece,env.nomyapeRece)==0 &&
           strcmp(a->pos->env.domicilioRece,env.domicilioRece)==0 && strcmp(a->pos->env.fechaEnv,env.fechaEnv)==0 && strcmp(a->pos->env.fechaRece,env.fechaRece)==0 &&
           a->pos->env.documentoRece == env.documentoRece && a->pos->env.documentoRemi == env.documentoRemi){
            if(a->pos->der == NULL && a->pos->izq == NULL){ //NODO SIN HIJOS
                if(a->pos == a->raiz){
                    a->raiz = NULL;
                    free((void*)(a->pos));
                    return 1; //Nodo raiz
                }else{
                    if(a->padre->izq == a->pos){
                        a->padre->izq == NULL;
                        free((void*)(a->pos));
                        return 1; //hijo izq
                    }else{
                        a->padre->der == NULL;
                        free((void*)(a->pos));
                        return 1; //hijo der
                    }
                }
            }
            if(a->pos->der != NULL && a->pos->izq == NULL){//NODO CON HIJO DERECHO
                if(a->pos == a->raiz){
                    a->raiz = a->pos->der;
                    free((void*)(a->pos));
                    return 1; //nodo raiz
                }else{
                    if(a->padre->izq == a->pos){
                        a->padre->izq == a->pos->der;
                        free((void*)(a->pos));
                        return 1; //hijo izq
                    }else{
                        a->padre->der == a->pos->der;
                        free((void*)(a->pos));
                        return 1; //hijo der
                    }
                }
            }
            if(a->pos->der == NULL && a->pos->izq != NULL){//NODO CON HIJO IZQUIERDO
                if(a->pos == a->raiz){
                    a->raiz = a->pos->izq;
                    free((void*)(a->pos));
                    return 1; //nodo raiz
                }else{
                    if(a->padre->izq == a->pos){
                        a->padre->izq == a->pos->izq;
                        free((void*)(a->pos));
                        return 1; //hijo izq
                    }else{
                        a->padre->der == a->pos->izq;
                        free((void*)(a->pos));
                        return 1; //hijo der
                    }
                }
            }
            if(a->pos->der != NULL && a->pos->izq != NULL){ //DOS HIJOS
                a->padre = a->pos;
                a->pos = a->pos->der;
                while(a->pos->izq != NULL){
                    aux = a->pos;
                    a->pos = a->pos->izq;
                }
                a->padre->env = a->pos->env;
                if(a->padre->der != a->pos){
                    a->padre = aux;
                    a->padre->izq = a->pos->der; //pos con hijo derecho
                }else{
                    a->padre->der = a->pos->der; //pos sin hijo izquierdo
                }
                free((void*)(a->pos));
                return 1;
            }
        }
    }
}


envio evocacionABB(arbol a,char cod[],int *exito){
    *exito=localizarABB(&a,cod);
    if(*exito){
        return a.pos->env;
    }
}

void preOrden(nodo *a){
if( a == NULL){
    }else{
        printf("%s \n", a->env.codigo);
        printf("%d \n",a->env.documentoRece);
        printf("%s \n",a->env.nomyapeRece);
        printf("%s \n",a->env.domicilioRece);
        printf("%d \n",a->env.documentoRemi);
        printf("%s \n",a->env.nomyapeRemi);
        printf("%s \n",a->env.fechaEnv);
        printf("%s \n",a->env.fechaRece);
        if( a->izq != NULL ){
            printf("\n---------------------------------------------------------------");
            printf("\nEl Codigo de su hijo izquierdo es: %s",a->izq->env.codigo);
        }else{
            printf("\n---------------------------------------------------------------");
            printf("\nNo tiene hijo izquierdo.");
        }

        if(a->der != NULL){
            printf("\n---------------------------------------------------------------");
            printf("\nEl Codigo de su hijo derecho es: %s",a->der->env.codigo);
        }else{
            printf("\n---------------------------------------------------------------");
            printf("\nNo tiene hijo derecho.");
        }
        printf("\n---------------------------------------------------------------");
        getchar();
        preOrden(a->izq);
        preOrden(a->der);
    }
}

#endif // ABB_H_INCLUDED
