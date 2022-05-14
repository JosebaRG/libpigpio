#include "libpigpio.h"

int main()
{
    /* LIBRARY TEST */
    char gpio[LIBPIGPIO_GPIO_LENGTH];
    char result[2];

    strcpy(gpio, "8");
    strcpy(result, "3");

    libpigpio_init(gpio,"OUT");

    libpigpio_write_value(gpio,"1");

    libpigpio_read_value (gpio, result);
    printf("El resultado es: %s", &result);

    libpigpio_close(gpio);
}

/*********************************************************************
* NAME :            int libpigpio_open (char gpio [LIBPIGPIO_GPIO_LENGTH]))
*
* DESCRIPTION :     Opens the GPIO connection in the export file
*
* INPUTS :
*       PARAMETERS:
*           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
* RETURN :
*           -1      for failure at the opening
*********************************************************************/

int libpigpio_open (char gpio [LIBPIGPIO_GPIO_LENGTH])
{
    FILE* File;
    char path [LIBPIGPIO_PATH_LENGTH];

    strcpy(path, "/sys/class/gpio/export");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error opening the GPIO");
        return -1;
    }        

    fprintf(File, gpio);

    fclose(File);

    return 0;
}

/*********************************************************************
* NAME :            int libpigpio_close (char gpio [LIBPIGPIO_GPIO_LENGTH])
*
* DESCRIPTION :     Closes the GPIO connection in the unexport file
*
* INPUTS :
*       PARAMETERS:
*           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
* RETURN :
*           -3      for failure at the closing
*********************************************************************/
int libpigpio_close  (char gpio [LIBPIGPIO_GPIO_LENGTH])
{
    FILE* File;
    char path [LIBPIGPIO_PATH_LENGTH];

    strcpy(path, "/sys/class/gpio/unexport");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error closing the GPIO");
        return -2;
    }

    fprintf(File, gpio);

    fclose(File);

    //TODO: checkear que el directorio de la GPIO ha desaparecido

    return 0;
}

int libpigpio_write_direction (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH])
{
    FILE* File;
    char path[50];
    int dir_len;

/*
    TODO: No consigo tratar el puntero como array para poner las letras en mayusculas
    dir_len = strlen(direction);

    for (int i = 0; i < dir_len; i++)
    {
        *(direction+i) = toupper(*(direction+i)); 
    }
*/

    if ( ! ( strcmp(direction,"IN") || strcmp(direction,"OUT") ) )
        return -3;

    strcpy(path, GPIO_PATH);
    strcat(path, gpio);
    strcat(path, "/direction");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error writing the GPIO direction");
        return -3;
    }

    if ( strcmp(direction,"IN") == 0 )
        fprintf(File, "in");
    else
        fprintf(File, "out");

    fclose(File);

    return 0;
}

int libpigpio_read_direction (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH])
{
    FILE* File;
    char path[50];
    int dir_len;

    strcpy(path, GPIO_PATH);
    strcat(path, gpio);
    strcat(path, "/direction");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error reading the GPIO direction");
        return -4;
    }

    fscanf(File, "%s", direction);

    //printf("La direccion leida es: %s", value);

    fclose(File);

    return 0;
}

int libpigpio_init (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH])
{   
    libpigpio_open(gpio);
    libpigpio_write_direction(gpio, direction);
}

int libpigpio_write_value (char gpio [LIBPIGPIO_GPIO_LENGTH], char value [LIBPIGPIO_DIR_LENGTH])
{
    FILE* File;
    char path[50];

    strcpy(path, GPIO_PATH);
    strcat(path, gpio);
    strcat(path, "/value");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error writing the GPIO value");
        return -5;
    }

    if ( strcmp(value,"0") == 0 )
        fprintf(File, "0");
    else
        fprintf(File, "1");

    fclose(File);

    return 0;
}

int libpigpio_read_value (char gpio [LIBPIGPIO_GPIO_LENGTH], char value [LIBPIGPIO_DIR_LENGTH])
{
    FILE* File;
    char path[50];

    strcpy(path, GPIO_PATH);
    strcat(path, gpio);
    strcat(path, "/value");

    File = fopen(path, "wr");

    if(File==NULL)
    {        
        if(GPIO_DEBUG==1)
            printf("\nlibpigpio: error reading the GPIO value");
        return -6;
    }

    fscanf(File, "%s", value);

    if(GPIO_DEBUG==1)
        printf("El valor leido es: %s", value);

    fclose(File);

    return 0;
}

