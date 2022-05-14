#include "libpigpio.h"

/*********************************
 * PRIVATE FUNCTIONS DECLARATION *
 *********************************/

int libpigpio_print_log (char text [255]);

/*********************************
 * MAIN IS JUST FOR LIBRARY TEST *
 *       WILL BE DELETED         *
**********************************/
int main()
{
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

/********************
 * PUBLIC FUNCTIONS *
 ********************/

/*********************************************************************
 * NAME :            libpigpio_open
 *
 * DESCRIPTION :     Opens the GPIO connection in the export file
 *
 * PARAMETERS :
 *       INPUTS : 
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *
 * RETURN :
 *           int     value for error code
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
 * NAME :            libpigpio_close
 *
 * DESCRIPTION :     Closes the GPIO connection in the unexport file
 *
 * PARAMETERS :
 *       INPUTS :
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *
 * RETURN :
 *           int     value for error code
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

/*********************************************************************
 * NAME :            libpigpio_write_direction
 *
 * DESCRIPTION :     Writes the usage of the GPIO as input or output
 *
 * PARAMETERS :
 *       INPUTS :
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *           char    direction [LIBPIGPIO_DIR_LENGTH] "IN" or "OUT"
 *
 * RETURN :
 *           int     value for error code
 *********************************************************************/
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

/*********************************************************************
 * NAME :            libpigpio_write_direction
 *
 * DESCRIPTION :     Writes the usage of the GPIO as input or output
 *
 * PARAMETERS :
 *       INPUTS :
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *       OUTPUTS :
 *           char  * direction               Returns "IN" or "OUT"
 *
 * RETURN :
 *           int     value for error code
 *********************************************************************/
int libpigpio_read_direction (char gpio [LIBPIGPIO_GPIO_LENGTH], char *direction)
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

/*********************************************************************
 * NAME :            libpigpio_init
 *
 * DESCRIPTION :     Initializes the GPIO, doing all the steps at once
 *
 * PARAMETERS :
 *       INPUTS :
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *           char    direction [LIBPIGPIO_DIR_LENGTH] "IN" or "OUT"
 *
 * RETURN :
 *           int     value for error code
 *********************************************************************/
int libpigpio_init (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH])
{
    // TODO: must check actual state of the GPIO 
    libpigpio_open(gpio);
    libpigpio_write_direction(gpio, direction);
    return 0;
}

/*********************************************************************
 * NAME :            libpigpio_write_value
 *
 * DESCRIPTION :     Initializes the GPIO, doing all the steps at once
 *
 * PARAMETERS :
 *       INPUTS :
 *           char    gpio  [GPIO_LENGTH]     Contains the GPIO number
 *           char    direction [LIBPIGPIO_DIR_LENGTH] "IN" or "OUT"
 *
 * RETURN :
 *           int     value for error code
 *********************************************************************/
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
        //if(GPIO_DEBUG==1)
        //    printf("\nlibpigpio: error writing the GPIO value");
        libpigpio_print_log("\nlibpigpio: error writing the GPIO value");
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
        //if(GPIO_DEBUG==1)
        //    printf("\nlibpigpio: error reading the GPIO value");
        libpigpio_print_log("\nlibpigpio: error reading the GPIO value");
        return -6;
    }

    fscanf(File, "%s", value);

    if(GPIO_DEBUG==1)
        printf("El valor leido es: %s", value);

    fclose(File);

    return 0;
}

/*********************
 * PRIVATE FUNCTIONS *
 *********************/

int libpigpio_print_log (char text [255])
{
    #ifdef GPIO_DEBUG
        printf("%s", text);
        return 0;
    #else
        return 1;       
    #endif //GPIO_DEBUG
}