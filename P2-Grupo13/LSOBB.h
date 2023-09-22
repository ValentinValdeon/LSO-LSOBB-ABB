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
    int testigo;
    int auxcost=0;
    while(li<ls){
        auxcost+=1;
        testigo = ceil((li+ls)/2);
        if((strcmp((*lsobb).arr[testigo].codigo,cod)<0)){
            li = testigo;
        }else{
            ls = testigo-1;
        }
    }
    if (strcmp((*lsobb).arr[(int)li + 1].codigo,cod)==0){ //consultar si el == cuenta como consulta
        auxcost++;
        if(maxLsobbEvocEx < auxcost){
            maxLsobbEvocEx = auxcost;
        }
        if(accion==1){
            cantLsobbEvocEx+=1;
            costLsobbEvocEx += auxcost;
        }
        (*pos)=li + 1;
        return 1;
    }else{
        auxcost++;
        if (ls == (*lsobb).cant-1){
            if (strcmp((*lsobb).arr[(int)ls].codigo,cod)>0){
                (*pos)=ls;
            }else{
                (*pos)=ls + 1;
            }
            auxcost++;
            if(maxLsobbEvocFr < auxcost){
                maxLsobbEvocFr = auxcost;
            }
            if(accion==1){
                cantLsobbEvocFr +=1;
                costLsobbEvocFr += auxcost;
            }
        }else{
            (*pos)=ls + 1;
            if(maxLsobbEvocFr < auxcost){
                maxLsobbEvocFr = auxcost;
            }
            if(accion==1){
                    cantLsobbEvocFr +=1;
                    costLsobbEvocFr += auxcost;
            }
        }
        return 0;
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
