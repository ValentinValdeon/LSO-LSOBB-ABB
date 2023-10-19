#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "envios.h"
#define MAX 300
typedef struct{
    int cant;
    envio arr[MAX];
}lista;
void initLSO(lista *lso){
    int i;
    (*lso).cant=0;
}
float maxLsoAlta= 0.00, costLsoAlta= 0.00, cantLsoAlta= 0.00, maxLsoBaja= 0.00, costLsoBaja= 0.00, cantLsoBaja= 0.00, maxLsoEvocEx= 0.00;
float costLsoEvocEx= 0.00, cantLsoEvocEx= 0.00, maxLsoEvocFr= 0.00, costLsoEvocFr= 0.00, cantLsoEvocFr= 0.00;

int localizarLSO(char cod[],lista *lso,int *pos,int accion){
    int i=0, auxcost=0;
    while(i<(*lso).cant && (strcmpi((*lso).arr[i].codigo,cod)<0)){
        i++;
        if(accion==1){
            auxcost+=1;
        }
    }
    (*pos)=i;
    if (i<(*lso).cant){
        if((strcmpi((*lso).arr[i].codigo,cod)==0)){
            auxcost++;
            if(maxLsoEvocEx < auxcost){
            maxLsoEvocEx = auxcost;
            }
            if(accion==1){
                cantLsoEvocEx+=1;
                costLsoEvocEx += auxcost;
            }
            return 1;
        }else {
            auxcost++;
            if(maxLsoEvocFr < auxcost){
                maxLsoEvocFr = auxcost;
            }
            if(accion==1){
                cantLsoEvocFr +=1;
                costLsoEvocFr += auxcost;
            }
            return 0;
        }
    }else{
        if(maxLsoEvocFr < auxcost){
            maxLsoEvocFr = auxcost;
        }
        if(accion==1){
            cantLsoEvocFr +=1;
            costLsoEvocFr += auxcost;
        }
        return 0;
    }
}

int altaLSO(lista *lso,envio env){
    int pos,exito,i, auxcost=0;
    exito = localizarLSO(env.codigo,lso,&pos,0);
    if(exito == 0){
            if((*lso).cant<MAX){
                for(i=(*lso).cant-1;i>=pos;i--){
                    (*lso).arr[i+1]=(*lso).arr[i];
                    costLsoAlta += 1;
                    auxcost += 1;
                }
                if(maxLsoAlta<auxcost){
                    maxLsoAlta = auxcost;
                }
                cantLsoAlta++;
                (*lso).arr[pos] = env;
                (*lso).cant++;
                return 1;//exito alta
            }else{
                return 2;//Si esta llena
            }
    }else{
        return 0;//si el elemento esta en la lista
    }
}

int bajaLSO(lista *lso,envio env){
    int pos,exito,i,confirmar=0, auxcost=0;
    exito=localizarLSO(env.codigo,lso,&pos,0);
    if(exito == 1){
        if(strcmpi((*lso).arr[pos].codigo,env.codigo)==0 && strcmpi((*lso).arr[pos].nomyapeRemi,env.nomyapeRemi)==0 && strcmpi((*lso).arr[pos].nomyapeRece,env.nomyapeRece)==0 &&
           strcmpi((*lso).arr[pos].domicilioRece,env.domicilioRece)==0 && strcmpi((*lso).arr[pos].fechaEnv,env.fechaEnv)==0 && strcmpi((*lso).arr[pos].fechaRece,env.fechaRece)==0 &&
           (*lso).arr[pos].documentoRece == env.documentoRece && (*lso).arr[pos].documentoRemi == env.documentoRemi){
            for(i=pos;i<(*lso).cant-1;i++){
                (*lso).arr[i]=(*lso).arr[i+1];
                costLsoBaja += 1;
                auxcost +=1;
            }
            if(maxLsoBaja<auxcost){
                maxLsoBaja=auxcost;
            }
            cantLsoBaja+=1;
            (*lso).cant--;
            return 1; //Baja exitosa
        }else{
            return 2;
        }
    }else{
        return 0; //el elemento no se encuentra en la lista
    }
}

envio evocacionLSO(char cod[], lista lso,int *exito){
    int pos;
    *exito = localizarLSO(cod,&lso,&pos,1);
    if(*exito == 1)
        return lso.arr[pos];
}

#endif // LSO_H_INCLUDED
