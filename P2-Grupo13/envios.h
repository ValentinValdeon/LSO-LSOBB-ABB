#ifndef ENVIOS_H_INCLUDED
#define ENVIOS_H_INCLUDED
typedef struct {
    char codigo[8];
    long documentoRece;
    char nomyapeRece[81];
    char domicilioRece[81];
    long documentoRemi;
    char nomyapeRemi[81];
    char fechaEnv[11];
    char fechaRece[11];
}envio;
void initEnvio (envio *env){
    strcpy((*env).codigo,"0");
    (*env).documentoRece = 0;
    strcpy((*env).nomyapeRece,"0");
    strcpy((*env).domicilioRece,"0");
    (*env).documentoRemi = 0;
    strcpy((*env).nomyapeRemi,"0");
    strcpy((*env).fechaEnv,"0");
    strcpy((*env).fechaRece,"0");
}


#endif // ENVIOS_H_INCLUDED
