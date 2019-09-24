//
// Created by Francesco_D'Ambrosio on 20/09/2019.
//

#include <stdio.h>
#include "File_Manager.h"

//int Delta_t_prevision = 12;

int main() {
    int i = 0;
    int j = 0;

    //char filename[NCAR];
    //printf("Inserisci nome file dati: ");
    //scanf("%s", filename);
    //FILE *fp = fopen(filename, "r");
    FILE *fp = fopen(("C:\\Users\\franc\\Desktop\\Tesi\\db_04_05.dat"), "r");

    float Matrix_loaded[NUM_DATA][8];
    float Initial_Conditions[NUM_DATA][4];

    load_data(fp, Matrix_loaded);
    column_of_interest(Matrix_loaded, Initial_Conditions);



    return 0;
}






    /*
    int numData = sizeof(column0) / sizeof(column0[0]);
    //printf("\nnumData: %d\n",numData);

    int last_training = numData - Delta_t_prevision;
    //printf("\nlast_training: %d\n", last_training);

    // Data_Train[NUM_DATA][2] and Data_Test[NUM_DATA-Delta_t_prevision][2] are two matrices that contain value of column0
    float Data_Train[NUM_DATA][2];
    float Data_Test[Delta_t_prevision][2];
    int j = 0;

    // Data_Train
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 2; j++) {
            if (j == 0)
                Data_Train[i][j] = i;
            else
                Data_Train[i][j] = column0[i];
        }
    }
    //test print - DATA_TRAIN
    */
/* int row;
     int column;
     for (row = 0; row < NUM_DATA; row++) {
         for (column = 0; column < 2; column++)
             printf("%f", Data_Train[row][column]);
         printf("\n");
     }*//*


    // Data_Test
    for (i = NUM_DATA - Delta_t_prevision; i < NUM_DATA; i++) {
        for (j = 0; j < 2; j++) {
            if (j == 0)
                Data_Test[i][j] = i;
            else
                Data_Test[i][j] = column0[i];
        }
    }
    //test print - DATA_TEST
    */
/*int row;
    int column;
    for (row = NUM_DATA - Delta_t_prevision; row < NUM_DATA; row++) {
        for (column = 0; column < 2; column++)
            printf("%f", Data_Test[row][column]);
        printf("\n");
    }*//*







*/








   /* numData = sizeof(colonna0) / sizeof(colonna0[0]);
    printf("%d\n", numData);

    int last_training = numData - Delta_t_prevision;
    printf("%d\n", last_training);*/


    // Ic_train
    // Ic_test



