//
// Created by Francesco_D'Ambrosio on 21/09/2019.
//

#include "File_Manager.h"

void load_data(FILE *fp, float Matrix_loaded[NUM_DATA][8]) {
    float c0;
    float c1;
    float c2;
    float c3;
    float c4;
    float c5;
    float c6;
    float c7;
    float column0[NUM_DATA];
    float column1[NUM_DATA];
    float column2[NUM_DATA];
    float column3[NUM_DATA];
    float column4[NUM_DATA];
    float column5[NUM_DATA];
    float column6[NUM_DATA];
    float column7[NUM_DATA];
    int i = 0;

    while ((fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f", &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7)) > 0 || i <= 284) {
        column0[i] = c0; // glucose
        column1[i] = c1; // ins basal
        column2[i] = c2; // bg
        column3[i] = c3; // ins
        column4[i] = c4; // cho
        column5[i] = c5;
        column6[i] = c6;
        column7[i] = c7;

        i++;
        if (i >= 285)
            break;
    }

    for (i = 0; i < NUM_DATA; i++) {
        Matrix_loaded[i][0] = column0[i];
        Matrix_loaded[i][1] = column1[i];
        Matrix_loaded[i][2] = column2[i];
        Matrix_loaded[i][3] = column3[i];
        Matrix_loaded[i][4] = column4[i];
        Matrix_loaded[i][5] = column5[i];
        Matrix_loaded[i][6] = column6[i];
        Matrix_loaded[i][7] = column7[i];
    }
}


void column_of_interest(float Matrix_loaded[NUM_DATA][8], float Initial_Conditions[NUM_DATA][4]){
    int i = 0;
    int j = 0;

    int *idx;
    float diff[NUM_DATA];
    float value;
    int count = 0;

    // Creation diff
    for (i = 0; i < NUM_DATA - 1; i++) {
        diff[i] = Matrix_loaded[i + 1][1] - Matrix_loaded[i][1];
        if (diff[i] != 0) {
            count = count + 1;
        }
    }

    // Creation idx
    idx = (float *) malloc((count + 1) * sizeof(int));
    //int numel_ins_basal = sizeof(column1) / sizeof(column1[0]);
    int numel_ins_basal = NUM_DATA;

    for (i = 0; i < NUM_DATA - 1; i++) {
        if (diff[i] != 0) {
            *(idx + j) = i + 1;
            j++;
        }
    }

    *(idx + j) = numel_ins_basal;
    value = Matrix_loaded[0][1]  / *idx;

    // Changing the values of the ins basal column
    int ii = 0;
    int jj = 0;
    while (ii < numel_ins_basal) {
        if (ii < *(idx + jj))
            Matrix_loaded[ii][1] = value;
        else {
            {
                jj = jj + 1;
                value = Matrix_loaded[ii][1] / idx[jj];
            }
            if (ii <= *(idx + jj))
                Matrix_loaded[ii][1] =  value;
        }
        ii = ii + 1;
    }


    // Only 4 columns of interest.
    int column_index = 0;
    int row_index = 0;

    for (row_index = 0; row_index<NUM_DATA; row_index++){
        for (column_index = 0; column_index<8; column_index++) {
            if (column_index == 0)
                Initial_Conditions[row_index][0] = Matrix_loaded[row_index][0];
            if (column_index == 1)
                Initial_Conditions[row_index][1] = Matrix_loaded[row_index][1]; //basal_insulin
            if (column_index == 3)
                Initial_Conditions[row_index][2] = Matrix_loaded[row_index][3]; //insulin_dosage
            if (column_index == 4)
                Initial_Conditions[row_index][3] = Matrix_loaded[row_index][4]; //cho_intake
        }
    }

    // Print - Initial_Conditions
   /* int row;
    int column;
    for (row=0; row<NUM_DATA; row++){

        for (column=0; column<4; column++)
            printf ("%0.4f  ",Initial_Conditions[row][column]);

        printf ( "\n");
    }*/
}


void matrices_of_interest(float Initial_Conditions[NUM_DATA][4], float Data_Train[NUM_DATA][2], float Data_Test[Delta_t_prevision][2], float IC_train[NUM_DATA][4], float IC_test[Delta_t_prevision][4]){
    int i = 0;
    int j = 0;
    int ii = 0;
    int jj = 0;
    int last_training = NUM_DATA - Delta_t_prevision;


    // Data_Train[NUM_DATA][2] contain all value of column0
    // Data_Test[Delta_t_prevision][2] contain value of column0 between NUM_DATA-Delta_t_prevision to NUM_DATA

    // Data_Train
    for (i = 0; i < NUM_DATA; i++) {
        Data_Train[i][0] = i;
        Data_Train[i][1] = Initial_Conditions[i][0];
    }

    // Data_Test
    for (i = last_training; i < NUM_DATA; i++) {
        Data_Test[jj][0] = i;
        Data_Test[jj][1] = Data_Train[i][1];
        jj++;
    }


    // IC_Train[NUM_DATA][2] contain value of column0 - column1 - column3 - column4.
    // IC_Test[NUM_DATA-Delta_t_prevision][2] contain value of column0 - column1 - column3 - column4.
    // IC_Train == Initial_conditions.
    // IC_Test == The last Delta_t_prevision row of Initial_conditions.

    // IC_train
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 4; j++) {
            IC_train[i][j] = Initial_Conditions[i][j];
        }
    }

    //IC_test
    for (i = last_training; i < NUM_DATA; i++) {
        for (j = 0; j < 4; j++) {
            IC_test[ii][j] = IC_train[i][j];
        }
        ii++;
    }
}

