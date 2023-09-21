#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#include "envios.h"
#include "math.h"
#define MAX 300
typedef struct{
    int cant;
    envio arr[MAX];
}listabb;
void initLSOBB(listabb *lsobb){
    int i;
    (*lsobb).cant=0;
}


int localizarLSOBB(char cod[],listabb *lsobb,int *pos){
    float li = -1, ls = (*lsobb).cant-1;
    int testigo;
    while(li<ls){
        testigo = ceil((li+ls)/2);
        if((strcmp((*lsobb).arr[testigo].codigo,cod)<0)){
            li = testigo;
        }else{
            ls = testigo-1;
        }
    }
    if (strcmp((*lsobb).arr[(int)li + 1].codigo,cod)==0){
        (*pos)=li + 1;
        return 1;
    }else{
        if (ls == (*lsobb).cant-1 && strcmp((*lsobb).arr[(int)ls].codigo,cod)>0){
            (*pos)=ls;
        }else{
            (*pos)=ls + 1;
        }
        return 0;
    }
}

int altaLSOBB(listabb *lsobb,envio env){
    int pos,exito,i;
    exito = localizarLSOBB(env.codigo,lsobb,&pos);
    if(exito == 0){
            if((*lsobb).cant<MAX){
                for(i=(*lsobb).cant-1;i>=pos;i--){
                    (*lsobb).arr[i+1]=(*lsobb).arr[i];
                }
                (*lsobb).arr[pos] = env;
                (*lsobb).cant++;
                //printf("%d \n",(*lsobb).cant);
                return 1;//exito alta
            }else{
                return 2;//Si esta llena
            }
    }else{
        return 0;//si el elemento esta en la lista
    }
}

int bajaLSOBB(listabb *lsobb,envio env){
    int pos,exito,i,confirmar=0;
    exito=localizarLSOBB(env.codigo,lsobb,&pos);
    if(exito == 1){
        /*printf("Envio N: %d \n",pos+1);
        printf("Codigo: %s \n",(*lsobb).arr[pos].codigo);
        printf("Documento del receptor: %ld \n",(*lsobb).arr[pos].documentoRece);
        printf("Nombre y Apellido del receptor: %s \n",(*lsobb).arr[pos].nomyapeRece);
        printf("Domicilio del receptor: %s \n",(*lsobb).arr[pos].domicilioRece);
        printf("Documento del remitente: %ld \n",(*lsobb).arr[pos].documentoRemi);
        printf("Nombre y Apellido del remitente: %s \n",(*lsobb).arr[pos].nomyapeRemi);
        printf("Fecha de envio: %s \n",(*lsobb).arr[pos].fechaEnv);
        printf("Fecha de recepcion: %s \n",(*lsobb).arr[pos].fechaRece);
        printf("Desea eliminar este envio? <1>Si <2>No \n");
        scanf("%d",&confirmar);
        while(confirmar < 1 || confirmar > 2){
            printf("Ingrese una opcion correcta <1>SI <2>NO");
            scanf("%d",&confirmar);
        }*/
        if(strcmp((*lsobb).arr[pos].codigo,env.codigo)==0 && strcmp((*lsobb).arr[pos].nomyapeRemi,env.nomyapeRemi)==0 && strcmp((*lsobb).arr[pos].nomyapeRece,env.nomyapeRece)==0 &&
           strcmp((*lsobb).arr[pos].domicilioRece,env.domicilioRece)==0 && strcmp((*lsobb).arr[pos].fechaEnv,env.fechaEnv)==0 && strcmp((*lsobb).arr[pos].fechaRece,env.fechaRece)==0 &&
           (*lsobb).arr[pos].documentoRece == env.documentoRece && (*lsobb).arr[pos].documentoRemi == env.documentoRemi){
            for(i=pos;i<(*lsobb).cant-1;i++){
                (*lsobb).arr[i]=(*lsobb).arr[i+1];
            }
            (*lsobb).cant--;
            return 1; //Baja exitosa
        }else{
            return 2;
        }
    }else{
        return 0; //el elemento no se encuentra en la lista
    }
}

envio evocacionLSOBB(char cod[], listabb lsobb,int *exito){
    int pos;
    *exito = localizarLSOBB(cod,&lsobb,&pos);
    if(*exito == 1)
        return lsobb.arr[pos];
}

#endif // LSOBB_H_INCLUDED
