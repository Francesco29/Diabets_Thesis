//
// Created by Francesco_D'Ambrosio on 26/09/2019.
//

#include "Hovorka_Model.h"
#include "Constant.h"
#include "Info.h"
#include <math.h>

void meal_disturbance2(float meal_abs[NUM_DATA][1], float Initial_Conditions[NUM_DATA][4], float t_max_G, float A_G) {
    int i = 0;
    int j = 0;
    int z = 0;
    int count = 0;
    int n = 300;
    int *idx_cho_intake;
    int t[n][1];
    float cho_intake[NUM_DATA][1];

    // cho_intake is the 4 column of Initial_Conditions
    for (i = 0; i < NUM_DATA; i++) {
        cho_intake[i][0] = Initial_Conditions[i][3];
    }

    // count is used in malloc
    for (i = 0; i < NUM_DATA - 1; i++) {
        if (cho_intake[i][0] != 0) {
            count = count + 1;
        }
    }

    // Creation idx_cho_intake
    idx_cho_intake = (float *) malloc((count) * sizeof(int));

    for (i = 0; i < NUM_DATA; i++) {
        if (cho_intake[i][0] != 0) {
            *(idx_cho_intake + j) = i + 1;
            j++;
        }
    }

    int m = count;
    float c[n][m];
    float D_G[m];
    int initial[m];

    // t is a column that contains value from 0 to n
    for (i = 0; i < n; i++) {
        t[i][0] = i + 1;
    }

    // meal_abs initialization
    for (i=0; i<NUM_DATA; i++){
        for (j=0; j<m; j++){
            meal_abs[i][j] = 0;
        }
    }


    // meal_abs
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            D_G[j] = cho_intake[*(idx_cho_intake + j) - 1][0];
            c[i][j] = (D_G[j] * A_G * exp(-t[i][0] / t_max_G)) / (t_max_G * t_max_G);
            initial[j] = *(idx_cho_intake + j);
        }
    }

    for (z = 0; z < n; z++) {
        for (j = 0; j < m; j++) {
                if ((z + initial[j] - 1) <= NUM_DATA)
                    meal_abs[z + initial[j] - 1][0] = meal_abs[z + initial[j]-1][0] + c[z][j];
        }
    }
    /*for (i = 0; i < NUM_DATA; i++){
        printf ("%0.4f     ", meal_abs[i][0]);
        printf("\n");
    }*/
}


void hovorka_IGDynamics_prev(float FVr_temp[I_D], float Initial_Conditions[NUM_DATA][4], int fin) {
    int i = 0;
    int j = 0;
    int t = 0;
    float meal_abs[NUM_DATA][1];

    FVr_temp[0] = 4.4157;
    FVr_temp[1] = 2.8841;
    FVr_temp[2] = 2.8196;
    FVr_temp[3] = 3.7195;
    FVr_temp[4] = 0.7835;
    FVr_temp[5] = 1.2375;
    FVr_temp[6] = 4.7224;
    FVr_temp[7] = 0.8762;
    FVr_temp[8] = 1.8590;
    FVr_temp[9] = 1.2893;
    FVr_temp[10] = 3.2215;
    FVr_temp[11] = 0.4280;
    FVr_temp[12] = 0.8591;
    FVr_temp[13] = 0.8845;
    FVr_temp[14] = 0.4108;
    FVr_temp[15] = 3.6305;
    FVr_temp[16] = 0.9822;
    FVr_temp[17] = 1.2392;

    float t_max_I = FVr_temp[0];
    float t_max_G = FVr_temp[1];
    float EGP = FVr_temp[2];
    float s = FVr_temp[3];
    float a = FVr_temp[4];
    float b = FVr_temp[5];
    float F_01 = FVr_temp[6];
    float K = FVr_temp[7];
    float A_G = FVr_temp[8];
    float V_G = FVr_temp[9];
    float V_I = FVr_temp[10];
    float k_a1 = FVr_temp[11];
    float k_a2 = FVr_temp[12];
    float k_a3 = FVr_temp[13];
    float k_b1 = FVr_temp[14];
    float k_b2 = FVr_temp[15];
    float k_b3 = FVr_temp[16];
    float K_I = FVr_temp[17];

    int n = Info.FVr_n;

    float S_1[n][1];
    float S_2[n][1];
    float I[n][1];
    float F[n][1];
    float Ra[n][1];
    float x_1[n][1];
    float x_2[n][1];
    float x_3[n][1];
    float Q_1[n][1];
    float Q_2[n][1];
    float G[n][1];
    float U_G[n][1];
    float U_I[n][1];


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //  Glucose Absorption SubSystem
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    meal_disturbance2(meal_abs, Initial_Conditions, t_max_G, A_G);

    // U_G
    for (i = 0; i < n; i++) {
        U_G[i][0] = meal_abs[i][0];
    }

    //F
    F[0][0] = U_G[0][0];
    for (t = 0; t < n - 1; t++) {
        F[t + 1][0] = -(1 / t_max_G) * F[t][0] + (A_G / t_max_G) * U_G[t][0] + F[t][0];
    }

    //Ra
    Ra[0][0] = (1 / t_max_G) * F[0][0];
    for (t = 0; t < n - 1; t++) {
        Ra[t + 1][0] = (1 / t_max_G) * (F[t][0] - Ra[t][0]) + Ra[t][0];
    }

    // U_I = exogenous_ins_rate (insulin_dosage, basal_insulin, a, b, s) + Initial_Conditions(:,2);
    for (i = 0; i < n; i++) {
        U_I[i][0] = Initial_Conditions[i][2] + Initial_Conditions[i][1];//insulin_dosage[i][0] + basal_insulin[i][0];
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // % Insulin Absorption SybSystem
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%









}

/* // Print - Differential Equation
printf ("%0.4f   \n", F[0][0]);
for (t=0; t<n-1; t++){
    printf ("%0.4f   ", F[t+1][0]);
    printf("\n");
}*/