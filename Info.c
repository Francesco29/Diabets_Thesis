//
// Created by franc on 25/09/2019.
//

// #include "Constant.h"

#include "Info.h"
#include "File_Manager.h"


void structure_data(float Data_Train[NUM_DATA][2], float Data_Test[Delta_t_prevision][2]){
    int i = 0;
    int j = 0;

    Info.FVr_n = NUM_DATA;
    Info.FVr_nte = Delta_t_prevision;

    // F_VTR "Value To Reach" (stop when ofunc < F_VTR)
    Info.F_VTR = 0.0001;

    // I_D		number of parameters of the objective function
    Info.ID = I_D;


    // FVr_minbound,FVr_maxbound -> vector of lower and bounds of initial population
    // the algorithm seems to work especially well if [FVr_minbound,FVr_maxbound]
    // covers the region where the global minimum is expected
    // *** note: these are no bound constraints!! ***

    // FVr_minbound
    for (i = 0; i < 1; i++) {
        for (j = 0; j < I_D; j++)
            Info.FVr_minbound[i][j] = 0;
    }

    // FVr_maxbound
    // BOUND SIZE 5
    int SIZE = 5; // 50
    for (i = 0; i < 1; i++) {
        for (j = 0; j < I_D; j++)
            Info.FVr_maxbound[i][j] = SIZE;
    }


    // 2: min bounds only
    // 1: use bounds as bound constraints
    // 0: no bound constraints
    Info.I_bnd_constr = 2;
    // I_NP -> number of population members
    Info.I_NP = 50;
    //I_itermax -> maximum number of iterations (generations)
    Info.I_itermax = 2000;
    // F_weight -> DE-stepsize F_weight ex [0, 2]
    Info.F_weight = 0.3;
    // F_CR -> crossover probabililty constant ex [0, 1]
    Info.F_CR = 0.9;

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
    Info.I_strategy = 4;

    //I_refresh -> intermediate output will be produced after "I_refresh" iterations.
    //             No intermediate output will be produced if I_refresh is < 1
    Info.I_refresh = 10;
    // I_plotting -> Will use plotting if set to 1. Will skip plotting otherwise.
    Info.I_plotting = 0;


    // Problem dependent but constant values. For speed reasons these values are
    // defined here. Otherwise we have to redefine them again and again in the
    // cost function or pass a large amount of parameters values.

    // bound at x-value +/- 1.2
    // FVr_bound
    for (j = 0; j < I_D; j++) {
        if ((j % 2) == 1)
            Info.FVr_bound[1][j] = SIZE;
        else
            Info.FVr_bound[1][j] = 0;
    }

    Info.I_lentol = NUM_DATA;

    // ordinate running from -1 to +1
    // FVr_x
    for (i = 0; i < NUM_DATA; i++) {
        Info.FVr_x[i][0] = Data_Train[i][0];
    }

    // upper limit
    // max value of FVr_x
    int max_x = 0;
    for (i = 0; i < NUM_DATA; i++) {
        if (Info.FVr_x[i][0] > max_x)
            max_x = Info.FVr_x[i][0];
    }
    Info.FVr_x_lim_up = max_x;


    // lower limit
    // min value of FVr_x
    int min_x = NUM_DATA;
    for (i = 0; i < NUM_DATA; i++) {
        if (Info.FVr_x[i][0] < min_x)
            min_x = Info.FVr_x[i][0];
    }
    Info.FVr_x_lim_lo = min_x;

    // ordinate running from -1 to +1
    // FVr_y
    for (i = 0; i < NUM_DATA; i++) {
        Info.FVr_y[i][0] = Data_Train[i][0];
    }

    // upper limit
    // max value of FVr_y
    float max_y = 0.0;
    for (i = 0; i < NUM_DATA; i++) {
        for (j = 0; j < 1; j++) {
            if (Info.FVr_y[i][j]  > max_y)
                max_y = Info.FVr_y[i][j] ;
        }
    }
    Info.FVr_y_lim_up = max_y;

    // lower limit
    // min value of FVr_y
    float min_y = NUM_DATA;
    for (i = 0; i < NUM_DATA; i++) {
        if (Info.FVr_y[i][0] < min_y)
            min_y = Info.FVr_y[i][0];
    }
    Info.FVr_y_lim_lo = min_y;

    // ordinate running from -1 to +1
    // FVr_xte
    for (i = 0; i < Delta_t_prevision; i++) {
        Info.FVr_xte[i][0] = Data_Test[i][0];
    }

    // upper limit
    // max value of FVr_xte
    int max_xte = 0;
    for (i = 0; i < Delta_t_prevision; i++) {
        if (Info.FVr_xte[i][0] > max_x)
            max_x = Info.FVr_xte[i][0];
    }
    Info.FVr_xte_lim_up = max_x;

    // lower limit
    // min value of FVr_xte
    int min_xte = NUM_DATA;
    for (i = 0; i < Delta_t_prevision; i++) {
        if (Info.FVr_xte[i][0] < min_xte)
            min_xte = Info.FVr_xte[i][0];
    }
    Info.FVr_xte_lim_lo = min_xte;

    // ordinate running from -1 to +1
    // FVr_yte
    for (i = 0; i < Delta_t_prevision; i++) {
        Info.FVr_yte[i][0] = Data_Test[i][1];
    }

    // upper limit
    // max value of FVr_yte
    float max_yte = 0.0;
    for (i = 0; i < Delta_t_prevision; i++) {
        for (j = 0; j < 1; j++) {
            if (Info.FVr_yte[i][j]  > max_yte)
                max_yte = Info.FVr_yte[i][j] ;
        }
    }
    Info.FVr_yte_lim_up = max_yte;

    // lower limit
    // min value of FVr_y
    float min_yte = NUM_DATA;
    for (i = 0; i < Delta_t_prevision; i++) {
        if (Info.FVr_yte[i][0] < min_yte)
            min_yte = Info.FVr_yte[i][0];
    }
    Info.FVr_yte_lim_lo = min_yte;
}















