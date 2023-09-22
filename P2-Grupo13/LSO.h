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
    while(i<(*lso).cant && (strcmp((*lso).arr[i].codigo,cod)<0)){
        i++;
        if(accion==1){
            auxcost+=1;
        }
    }
    (*pos)=i;
    if (i<(*lso).cant){
        if((strcmp((*lso).arr[i].codigo,cod)==0)){
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
        /*printf("Envio N: %d \n",pos+1);
        printf("Codigo: %s \n",(*lso).arr[pos].codigo);
        printf("Documento del receptor: %ld \n",(*lso).arr[pos].documentoRece);
        printf("Nombre y Apellido del receptor: %s \n",(*lso).arr[pos].nomyapeRece);
        printf("Domicilio del receptor: %s \n",(*lso).arr[pos].domicilioRece);
        printf("Documento del remitente: %ld \n",(*lso).arr[pos].documentoRemi);
        printf("Nombre y Apellido del remitente: %s \n",(*lso).arr[pos].nomyapeRemi);
        printf("Fecha de envio: %s \n",(*lso).arr[pos].fechaEnv);
        printf("Fecha de recepcion: %s \n",(*lso).arr[pos].fechaRece);
        printf("Desea eliminar este envio? <1>Si <2>No \n");
        scanf("%d",&confirmar);
        while(confirmar < 1 || confirmar > 2){
            printf("Ingrese una opcion correcta <1>SI <2>NO");
            scanf("%d",&confirmar);
        }*/
        if(strcmp((*lso).arr[pos].codigo,env.codigo)==0 && strcmp((*lso).arr[pos].nomyapeRemi,env.nomyapeRemi)==0 && strcmp((*lso).arr[pos].nomyapeRece,env.nomyapeRece)==0 &&
           strcmp((*lso).arr[pos].domicilioRece,env.domicilioRece)==0 && strcmp((*lso).arr[pos].fechaEnv,env.fechaEnv)==0 && strcmp((*lso).arr[pos].fechaRece,env.fechaRece)==0 &&
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
