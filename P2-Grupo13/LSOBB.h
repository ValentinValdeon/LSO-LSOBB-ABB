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
float maxLsobbAlta = 0.00, costLsobbAlta= 0.00, cantLsobbAlta= 0.00, maxLsobbBaja= 0.00, costLsobbBaja= 0.00, cantLsobbBaja= 0.00;
float maxLsobbEvocEx= 0.00, costLsobbEvocEx= 0.00, cantLsobbEvocEx= 0.00, maxLsobbEvocFr= 0.00, costLsobbEvocFr= 0.00, cantLsobbEvocFr= 0.00;

int localizarLSOBB(char cod[],listabb *lsobb,int *pos, int accion){
    float li = -1, ls = (*lsobb).cant-1;
    int testigo,i;
    int auxcost=0;
    int arr[(*lsobb).cant];
    for(i=0;i<(*lsobb).cant;i++){
        arr[i]=0;
    }
    if((*lsobb).cant == 0){
        *pos=0;
        if(maxLsobbEvocFr < auxcost){
                maxLsobbEvocFr = auxcost;
            }
            if(accion==1){
                cantLsobbEvocFr+=1;
                costLsobbEvocFr += auxcost;
            }
        return 0;
    }else{
        while(li+1<ls){
            testigo = ceil(((li+ls+1)/2.0));
            if((strcmpi((*lsobb).arr[testigo].codigo,cod)>0)){
                ls = testigo-1;
            }else{
                li = testigo-1;
            }
            if(arr[testigo]==0&&accion==1){
                arr[testigo]=1;
                auxcost+=1;
            }
        }
        if (strcmpi((*lsobb).arr[(int)ls].codigo,cod)==0){ //consultar si el == cuenta como consulta
            if(arr[(int)ls]==0){
                auxcost++;
            }
            if(maxLsobbEvocEx < auxcost){
                maxLsobbEvocEx = auxcost;
            }
            if(accion==1){
                cantLsobbEvocEx+=1;
                costLsobbEvocEx += auxcost;
            }
            (*pos)=ls;
            return 1;
        }else{
            if((*lsobb).cant > 0 && arr[(int)ls]==0){
                auxcost++;
            }
            if (strcmpi((*lsobb).arr[(int)ls].codigo,cod)>0){
                (*pos)=ls;
            }else{
                (*pos)=ls+1;
            }
            if(maxLsobbEvocFr < auxcost){
                maxLsobbEvocFr = auxcost;
            }
            if(accion==1){
                cantLsobbEvocFr +=1;
                costLsobbEvocFr += auxcost;
            }
            return 0;
        }
    }
}

int altaLSOBB(listabb *lsobb,envio env){
    int pos,exito,i,auxcost=0;
    exito = localizarLSOBB(env.codigo,lsobb,&pos,0);
    if(exito == 0){
            if((*lsobb).cant<MAX){
                for(i=(*lsobb).cant-1;i>=pos;i--){
                    (*lsobb).arr[i+1]=(*lsobb).arr[i];
                    costLsobbAlta += 1;
                    auxcost += 1;
                }
                if(maxLsobbAlta<auxcost){
                    maxLsobbAlta = auxcost;
                }
                cantLsobbAlta++;
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
    int pos,exito,i,confirmar=0,auxcost=0;
    exito=localizarLSOBB(env.codigo,lsobb,&pos,0);
    if(exito == 1){
        if(strcmpi((*lsobb).arr[pos].codigo,env.codigo)==0 && strcmpi((*lsobb).arr[pos].nomyapeRemi,env.nomyapeRemi)==0 && strcmpi((*lsobb).arr[pos].nomyapeRece,env.nomyapeRece)==0 &&
           strcmpi((*lsobb).arr[pos].domicilioRece,env.domicilioRece)==0 && strcmpi((*lsobb).arr[pos].fechaEnv,env.fechaEnv)==0 && strcmpi((*lsobb).arr[pos].fechaRece,env.fechaRece)==0 &&
           (*lsobb).arr[pos].documentoRece == env.documentoRece && (*lsobb).arr[pos].documentoRemi == env.documentoRemi){
            for(i=pos;i<(*lsobb).cant-1;i++){
                (*lsobb).arr[i]=(*lsobb).arr[i+1];
                costLsobbBaja += 1;
                auxcost +=1;

            }
            if(maxLsobbBaja<auxcost){
                maxLsobbBaja=auxcost;
            }
            cantLsobbBaja+=1;
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
    *exito = localizarLSOBB(cod,&lsobb,&pos,1);
    if(*exito == 1)
        return lsobb.arr[pos];
}

#endif // LSOBB_H_INCLUDED
