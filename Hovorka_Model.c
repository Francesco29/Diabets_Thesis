//
// Created by Francesco_D'Ambrosio on 26/09/2019.
//

#include "Hovorka_Model.h"
#include "Constant.h"
#include "Info.h"
#include <math.h>

void meal_disturbance2(float Initial_Conditions[NUM_DATA][4], float t_max_G, float A_G) {
    int i = 0;
    int j = 0;
    int z = 0;
    int count = 0;
    int n = 300;
    int *idx_cho_intake;
    int t[n][1];
    float cho_intake[NUM_DATA][1];
    float meal_abs[n][1];

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
    /*for (i=0; i<count; i++)
       printf ("\n%d", *(idx_cho_intake+i));*/

    int m = count;
    float c[n][m];

    for (i = 0; i < n; i++) {
        t[i][0] = i + 1;
    }

    //printf("%d ", *(idx_cho_intake+0));
    //printf("%f ",t_max_G*t_max_G);

    int D_G[m];
    int initial[m];

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            D_G[j] = cho_intake[*(idx_cho_intake + j) - 1][0];
            c[i][j] = (D_G[j] * A_G * exp(-t[i][j] / t_max_G)) / (t_max_G * t_max_G);
            initial[j] = *(idx_cho_intake + j);
            for (z = 0; z < n; z++) {
                if ((z + initial[j]) <= (sizeof(cho_intake) / sizeof(cho_intake[0]))) {
                    meal_abs[z + initial[j]][0] = meal_abs[z + initial[j]][0] + c[z][0];
                }


            }


        }
    }
    int ii=0;
    while(ii<300){
        for (j = 0; j < m; j++)
            printf("%f\n", meal_abs[i + initial[j]][0]);
        ii++;
    }

   // printf("%f\n", meal_abs[284][0]);



}







void hovorka_IGDynamics_prev(float FVr_temp[I_D], float Initial_Conditions[NUM_DATA][4], int fin){
    int i = 0;
    int j = 0;

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
    float EGP     = FVr_temp[2];
    float s       = FVr_temp[3];
    float a       = FVr_temp[4];
    float b       = FVr_temp[5];
    float F_01    = FVr_temp[6];
    float K       = FVr_temp[7];
    float A_G     = FVr_temp[8];
    float V_G     = FVr_temp[9];
    float V_I     = FVr_temp[10];
    float k_a1    = FVr_temp[11];
    float k_a2    = FVr_temp[12];
    float k_a3    = FVr_temp[13];
    float k_b1    = FVr_temp[14];
    float k_b2    = FVr_temp[15];
    float k_b3    = FVr_temp[16];
    float K_I     = FVr_temp[17];

    int n = Info.FVr_n;

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //  Glucose Absorption SubSystem
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    meal_disturbance2(Initial_Conditions, t_max_G, A_G);





}



