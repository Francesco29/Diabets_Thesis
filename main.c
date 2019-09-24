//
// Created by Francesco_D'Ambrosio on 20/09/2019.
//

#include "File_Manager.h"

int Delta_t_prevision = 12;

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

    //int numData = sizeof(column0) / sizeof(column0[0]);
    //printf("\nnumData: %d\n",numData);
    int last_training = NUM_DATA - Delta_t_prevision;

    // Data_Train[NUM_DATA][2] contain all value of column0
    // Data_Test[Delta_t_prevision][2] contain value of column0 between NUM_DATA-Delta_t_prevision to NUM_DATA
    float Data_Train[NUM_DATA][2];
    float Data_Test[Delta_t_prevision][2];

    // Data_Train
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 2; j++) {
            if (j == 0)
                Data_Train[i][j] = i;
            else
                Data_Train[i][j] = Initial_Conditions[i][0];
        }
    }
    //Print - DATA_TRAIN
   /* for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 2; j++)
            printf ("%f", Data_Train[i][j]);
            printf("\n");
    }*/

    // Data_Test
    for (i = last_training; i < NUM_DATA; i++) {
        for (j = 0; j < 2; j++) {
            if (j == 0)
                Data_Test[i][j] = i;
            else
                Data_Test[i][j] = Initial_Conditions[i][0];
        }
    }

    // IC_Train[NUM_DATA][2] contain value of column0 - column1 - column3 - column4.
    // IC_Test[NUM_DATA-Delta_t_prevision][2] contain value of column0 - column1 - column3 - column4.
    // IC_Train == Initial_conditions.
    // IC_Test == The last Delta_t_prevision row of Initial_conditions.
    float IC_train[NUM_DATA][4];
    float IC_test[Delta_t_prevision][4];

    // IC_train
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 4; j++) {
            IC_train[i][j] = Initial_Conditions[i][j];
        }
    }

    //IC_test
    for (i = last_training; i < NUM_DATA; i++) {
        for (j = 0; j < 4; j++) {
            IC_test[i][j] = IC_train[i][j];
        }
    }


    // F_VTR "Value To Reach" (stop when ofunc < F_VTR)
    float F_VTR = 0.0001;
    // I_D		number of parameters of the objective function
    int I_D = 18;
    // BOUND SIZE
    int SIZE = 5; // %50


    // FVr_minbound,FVr_maxbound -> vector of lower and bounds of initial population
    // the algorithm seems to work especially well if [FVr_minbound,FVr_maxbound]
    // covers the region where the global minimum is expected
    // *** note: these are no bound constraints!! ***

    // FVr_minbound
    int FVr_minbound[0][I_D];
    for (i = 0; i < 1; i++) {
        for (j = 0; j < I_D; j++)
            FVr_minbound[i][j] = 0;
    }

    // FVr_maxbound
    int FVr_maxbound[0][I_D];
    for (i = 0; i < 1; i++) {
        for (j = 0; j < I_D; j++)
            FVr_maxbound[i][j] = SIZE;
    }

    // 2: min bounds only
    // 1: use bounds as bound constraints
    // 0: no bound constraints
    int I_bnd_constr = 2;
    // I_NP -> number of population members
    int I_NP = 50;
    //I_itermax -> maximum number of iterations (generations)
    int I_itermax = 2000;
    // F_weight -> DE-stepsize F_weight ex [0, 2]
    float F_weight = 0.3;
    // F_CR -> crossover probabililty constant ex [0, 1]
    float F_CR = 0.9;

    // I_strategy:
    // 1 --> DE/rand/1: the classical version of DE.
    // 2 --> DE/local-to-best/1: a version which has been used by quite a number of scientists.
    //                           Attempts a balance between robustness and fast convergence.
    // 3 --> DE/best/1 with jitter: taylored for small population sizes and fast convergence.
    //                              Dimensionality should not be too high.
    // 4 --> DE/rand/1 with per-vector-dither: Classical DE with dither to become even more robust.
    // 5 --> DE/rand/1 with per-generation-dither: Classical DE with dither to become even more robust.
    //                                             Choosing F_weight = 0.3 is a good start here.
    // 6 --> DE/rand/1 either-or-algorithm: Alternates between differential mutation and three-point-recombination.
    int I_strategy = 4;

    //I_refresh -> intermediate output will be produced after "I_refresh" iterations.
    //             No intermediate output will be produced if I_refresh is < 1
    int I_refresh = 10;
    // I_plotting -> Will use plotting if set to 1. Will skip plotting otherwise.
    int I_plotting = 0;


    // Problem dependent but constant values. For speed reasons these values are
    // defined here. Otherwise we have to redefine them again and again in the
    // cost function or pass a large amount of parameters values.

    // bound at x-value +/- 1.2
    // FVr_bound
    int FVr_bound[1][I_D];
    for (j = 0; j < I_D; j++) {
        if ((j % 2) == 1)
            FVr_bound[1][j] = SIZE;
        else
            FVr_bound[1][j] = 0;
        }

    int I_lentol = NUM_DATA;

    printf ("data test 1: %f", Data_Test[280][0]);

    // ordinate running from -1 to +1
    // FVr_x
    int FVr_x[NUM_DATA][1];
    for (i = 0; i < NUM_DATA; i++) {
        FVr_x[i][0] = 0;//Data_Train[i][0];
    }

    printf ("\ndata test 2: %f", Data_Test[280][0]);

    // upper limit
    // max value of FVr_x
    int FVr_x_lim_up;
    int max = 0;
    for (i = 0; i < NUM_DATA; i++) {
        if (FVr_x[i][0] > max)
            max = FVr_x[i][0];
        }
    FVr_x_lim_up = max;

    // lower limit
    // min value of FVr_x
    int FVr_x_lim_lo;
    int min = NUM_DATA;
    for (i = 0; i < NUM_DATA; i++) {
            if (FVr_x[i][0] < min)
                min = FVr_x[i][0];
    }
    FVr_x_lim_lo = min;

    // ordinate running from -1 to +1
    float FVr_y[NUM_DATA][1];
    for (i = 0; i < NUM_DATA; i++) {
            FVr_y[i][0] = Initial_Conditions[i][0];
    }

    // upper limit
    // max value of FVr_y
    float FVr_y_lim_up;
    float max_y = 0.0;
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 1; j++) {
            if (FVr_y[i][j]  > max_y)
                max_y = FVr_y[i][j] ;
        }
    }
    FVr_y_lim_up = max_y;

    // lower limit
    // min value of FVr_y
    float FVr_y_lim_lo;
    float min_y = NUM_DATA;
    for (i = 0; i < NUM_DATA; i++) {
            if (FVr_y[i][0] < min_y)
                min_y = FVr_y[i][0];
    }
    FVr_y_lim_lo = min_y;


    // ordinate running from -1 to +1
    int FVr_xte[Delta_t_prevision][1];
    for (i = last_training; i < NUM_DATA; i++) {
        FVr_xte[i][0] = Data_Test[i][0];
    }

    /*for (i = last_training; i < NUM_DATA; i++) {
        printf ("%d\n", FVr_xte[i][0]);
    }*/














    return 0;
}