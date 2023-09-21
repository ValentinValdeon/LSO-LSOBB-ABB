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


int localizarLSO(char cod[],lista *lso,int *pos){
    int i=0;
    while(i<(*lso).cant && (strcmp((*lso).arr[i].codigo,cod)<0)){
        i++;
    }
    (*pos)=i;
    if (i<(*lso).cant && (strcmp((*lso).arr[i].codigo,cod)==0)){
        return 1;
    }else {
        return 0;
    }
}

int altaLSO(lista *lso,envio env){
    int pos,exito,i;
    exito = localizarLSO(env.codigo,lso,&pos);
    if(exito == 0){
            if((*lso).cant<MAX){
                for(i=(*lso).cant-1;i>=pos;i--){
                    (*lso).arr[i+1]=(*lso).arr[i];
                }
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
    int pos,exito,i,confirmar=0;
    exito=localizarLSO(env.codigo,lso,&pos);
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
            }
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
    *exito = localizarLSO(cod,&lso,&pos);
    if(*exito == 1)
        return lso.arr[pos];
}

int modificarLSO(int codigo,lista *lso){
    int pos=0,fin=0;
    long documentoRece;
    char nomyapeRece[81];
    char domicilioRece[81];
    long documentoRemi;
    char nomyapeRemi[81];
    char fechaEnv[11];
    char fechaRece[11];
    if (localizarLSO(codigo,lso,&pos)){
        do{
            printf("Envio N: %d \n",pos+1);
            printf("Codigo: %s \n",(*lso).arr[pos].codigo);
            printf("<1>Documento del receptor: %ld \n",(*lso).arr[pos].documentoRece);
            printf("<2>Nombre y Apellido del receptor: %s \n",(*lso).arr[pos].nomyapeRece);
            printf("<3>Domicilio del receptor: %s \n",(*lso).arr[pos].domicilioRece);
            printf("<4>Documento del remitente: %ld \n",(*lso).arr[pos].documentoRemi);
            printf("<5>Nombre y Apellido del remitente: %s \n",(*lso).arr[pos].nomyapeRemi);
            printf("<6>Fecha de envio: %s \n",(*lso).arr[pos].fechaEnv);
            printf("<7>Fecha de recepcion: %s \n",(*lso).arr[pos].fechaRece);
            printf("<8>Terminar modificaciones \n");
            printf("Que desea modificar <1-8> \n");
            scanf("%d",&fin);
            fflush(stdin);
            switch(fin){
                case 1:
                    system("cls");
                    printf("Ingrese el nuevo Documento del Receptor\n");
                    scanf("%ld",&documentoRece);
                    (*lso).arr[pos].documentoRece = documentoRece;
                    break;
                case 2:
                    system("cls");
                    printf("Ingrese el nuevo Nombre y Apellido del Receptor\n");
                    scanf("%[^\n]s",nomyapeRece);
                    strcpy((*lso).arr[pos].nomyapeRece,nomyapeRece);
                    break;
                case 3:
                    system("cls");
                    printf("Ingrese el nuevo Domicilio del Receptor\n");
                    scanf("%[^\n]s",domicilioRece);
                    strcpy((*lso).arr[pos].domicilioRece,domicilioRece);
                    break;
                case 4:
                    system("cls");
                    printf("Ingrese el nuevo Documento del Remitente\n");
                    scanf("%ld",&documentoRemi);
                    (*lso).arr[pos].documentoRemi= documentoRemi;
                    break;
                case 5:
                    system("cls");
                    printf("Ingrese el nuevo Nombre y Apellido del Remitente\n");
                    scanf("%[^\n]s",nomyapeRemi);
                    strcpy((*lso).arr[pos].nomyapeRemi,nomyapeRemi);
                    break;
                case 6:
                    system("cls");
                    printf("Ingrese la nueva Fecha de Envio\n");
                    scanf("%[^\n]s",fechaEnv);
                    strcpy((*lso).arr[pos].fechaEnv,fechaEnv);
                    break;
                case 7:
                    system("cls");
                    printf("Ingrese la nueva Fecha de Recepcion \n");
                    scanf("%[^\n]s",fechaRece);
                    strcpy((*lso).arr[pos].fechaRece,fechaRece);
                    break;
                case 8:
                    system("cls");
                    break;
                default:
                    system("cls");
                    printf("-------------------Opcion Incorrecta--------------------\n");
                    printf("------Presione cualquier tecla para volver al menu------");
                    getchar();
                    break;
            }
        }while(fin !=8);
        return 1;
    }else{
        return 0;
    }

}

#endif // LSO_H_INCLUDED
